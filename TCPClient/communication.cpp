#include "communication.h"
#include <chrono>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/statvfs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <errno.h>

void Communication::Start(int core_index)
{
    th = std::thread(&Communication::Process,
                     this, core_index);
}

void Communication::Process(int core_index)
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(core_index, &cpu);
    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        std::cout << "Erroring core selection." << std::endl;

    bool start_conn_status = false;

    for (;;) {
        std::lock_guard<std::mutex> grd(mtx);

        if (CheckEthCable("eth0")) {
            if (!start_conn_status) {
                tcp_init.Init(selected_core_2);
                start_conn_status = true;
            }

            if (tcp_init.GetConnStatus()) {
                tcp_init.Stop();
                std::this_thread::sleep_for(std::chrono::microseconds(100));

                tcp_receiver.Receiver(selected_core_2);
                tcp_sender.Sender(selected_core_2);
            }

        } else {
            tcp_init.Stop();
            tcp_receiver.Stop();
            tcp_sender.Stop();
            start_conn_status = false;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int Communication::CheckEthCable(const char *if_name)
{
    struct ifreq if_req_def;

    int soc_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (soc_id < 0)
        return 0;

    (void) strncpy(if_req_def.ifr_name, if_name, sizeof(if_req_def.ifr_name));
    int rv= ioctl(soc_id, SIOCGIFFLAGS, &if_req_def);
    close(soc_id);

    if (rv == -1)
        return 0;

    return (if_req_def.ifr_flags & IFF_UP) && (if_req_def.ifr_flags & IFF_RUNNING);
}
