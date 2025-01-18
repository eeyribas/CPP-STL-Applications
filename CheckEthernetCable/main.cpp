#include <QCoreApplication>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

int CheckEthernetCable(char *if_name)
{
    int socket_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (socket_id < 0) {
        printf("Socket failed. Errno = %d\n", errno);
        return -1;
    }

    struct ifreq if_req;
    (void) strncpy(if_req.ifr_name, if_name, sizeof(if_req.ifr_name));
    int rv = ioctl(socket_id, SIOCGIFFLAGS, &if_req);
    close(socket_id);
    if (rv == -1) {
        printf("Ioctl failed. Errno = %d\n", errno);
        return -1;
    }

    return (if_req.ifr_flags & IFF_UP) && (if_req.ifr_flags & IFF_RUNNING);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int check_eth_cable = CheckEthernetCable("eth0");
    printf("Eth Cable (eth0) State : %d", check_eth_cable);

    return a.exec();
}
