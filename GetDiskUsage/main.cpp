#include <QCoreApplication>
#include <QDebug>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <sys/statvfs.h>
#include <errno.h>

uint64_t GetDiskUsage(const char* path)
{
    struct statvfs info = {};
    if (statvfs(path, &info)) {
        int err_num = errno;
        qDebug() << "Error in statvfs : " << strerror(err_num);

        return 0;
    }

    uint64_t available = info.f_bavail * info.f_frsize / 1000000000;

    return available;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Available Disk Memory : " << GetDiskUsage("/home");

    return a.exec();
}
