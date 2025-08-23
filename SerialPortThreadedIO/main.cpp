#include <QCoreApplication>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <netdb.h>

void *ThreadFunction(void *param);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pthread_t thread;
    if (pthread_create(&thread, nullptr,
                       *ThreadFunction, nullptr))
        perror("Not Create Thread.\n");
    pthread_join(thread, nullptr);

    return a.exec();
}

void *ThreadFunction(void *param)
{
    Q_UNUSED(param);

    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(2, &cpu);
    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        perror("Error selected core.\n");

    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
    struct termios tty;
    if (tcgetattr(fd, &tty) < 0)
        fd = -1;

    cfsetospeed(&tty, (speed_t)B3000000);
    cfsetispeed(&tty, (speed_t)B3000000);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1000;

    if ((tcsetattr(fd, TCSANOW, &tty)) != 0)
        fd = -1;
    tcflush(fd, TCIFLUSH);
    printf("Open State = %d\n", fd);

    char send_data[] = {'*', '*', '*', '*', '*', '\r'};

    for (;;) {
        tcflush(fd, TCIFLUSH);
        write(fd, send_data, 5);

        unsigned char buffer[4098];
        int num_to_read = 4098;
        int read_data_byte_lenght = 0;
        int total_read = 0;

        while (num_to_read > 0) {

            read_data_byte_lenght = read(fd, &buffer[total_read], num_to_read);
            printf("Read Data Byte Length = %d\n", read_data_byte_lenght);
            if (read_data_byte_lenght > 0) {
                total_read += read_data_byte_lenght;
                num_to_read -= read_data_byte_lenght;
            }
        }

        sleep(1);
    }

    close(fd);
    printf("Close State = %d\n", fd);

    return 0;
}
