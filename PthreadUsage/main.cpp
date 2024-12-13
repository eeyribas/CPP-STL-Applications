#include <QCoreApplication>
#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

void *ThreadFunction(void *param)
{
    Q_UNUSED(param);
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    // Core = 2
    CPU_SET(2, &cpu);

    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        perror("Error selected core.\n");

    for (;;) {
        printf("Hello World!\n");
        sleep(1);
    }
}

int main()
{
    pthread_t thread;
    if (pthread_create(&thread, nullptr, ThreadFunction, nullptr))
        perror("Not create thread.\n");
    pthread_join(thread, nullptr);

    return 0;
}
