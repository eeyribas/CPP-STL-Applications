#include <QCoreApplication>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <stdint.h>
#include <sys/statvfs.h>
#include <errno.h>

uint64_t GetDiskUsage(const char *path)
{
    struct statvfs info = {};
    if (statvfs(path, &info)) {
        int err_num = errno;
        printf("Error in statvfs : %s", strerror(err_num));

        return 0;
    }

    uint64_t available = info.f_bavail * info.f_frsize / 1000000000;

    return available;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    printf("Available Disk Memory : %d", GetDiskUsage("/home"));

    return a.exec();
}
