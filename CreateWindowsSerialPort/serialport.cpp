#include "serialport.h"
#include <QDebug>

HANDLE SerialPort::Open(const char *device, uint32_t baud_rate)
{
    HANDLE handle = CreateFileA(device, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        PrintError(device);

        return INVALID_HANDLE_VALUE;
    }

    BOOL success = FlushFileBuffers(handle);
    if (!success) {
        PrintError("Failed to flush serial port.");
        CloseHandle(handle);

        return INVALID_HANDLE_VALUE;
    }

    COMMTIMEOUTS comm_timeouts = { 0 };
    comm_timeouts.ReadIntervalTimeout = 0;
    comm_timeouts.ReadTotalTimeoutConstant = 100;
    comm_timeouts.ReadTotalTimeoutMultiplier = 0;
    comm_timeouts.WriteTotalTimeoutConstant = 100;
    comm_timeouts.WriteTotalTimeoutMultiplier = 0;

    success = SetCommTimeouts(handle, &comm_timeouts);
    if (!success) {
        PrintError("Failed to set serial timeouts.");
        CloseHandle(handle);

        return INVALID_HANDLE_VALUE;
    }

    DCB dcb;
    dcb.DCBlength = sizeof(DCB);
    success = GetCommState(handle, &dcb);
    if (!success) {
        PrintError("Failed to get serial settings.");
        CloseHandle(handle);

        return INVALID_HANDLE_VALUE;
    }

    dcb.BaudRate = baud_rate;
    success = SetCommState(handle, &dcb);
    if (!success) {
        PrintError("Failed to set serial settings.");
        CloseHandle(handle);

        return INVALID_HANDLE_VALUE;
    }

    return handle;
}

int SerialPort::Write(HANDLE handle, uint8_t *buffer, size_t size)
{
    DWORD written;
    BOOL success = WriteFile(handle, buffer, size, &written, NULL);
    if (!success) {
        PrintError("Failed to write to port.");
        return -1;
    }

    if (written != size) {
        PrintError("Failed to write all bytes to port.");
        return -1;
    }

    return 0;
}

SSIZE_T SerialPort::Read(HANDLE handle, uint8_t *buffer, size_t size)
{
    DWORD received;
    BOOL success = ReadFile(handle, buffer, size, &received, NULL);
    if (!success) {
        PrintError("Failed to read from port.");
        return -1;
    }

    return received;
}

int SerialPort::JRKSetTarget(HANDLE handle, uint16_t target)
{
    if (target > 4095)
        target = 4095;

    uint8_t command[2];
    command[0] = 0xC0 + (target & 0x1F);
    command[1] = (target >> 5) & 0x7F;

    return Write(handle, command, sizeof(command));
}

int SerialPort::JRKGetVariable(HANDLE handle, uint8_t offset,
                               uint8_t *buffer, uint8_t length)
{
    uint8_t command[] = { 0xE5, offset, length };
    int result = Write(handle, command, sizeof(command));
    if (result)
        return -1;

    SSIZE_T received = Read(handle, buffer, length);
    if (received < 0)
        return -1;

    if (received != length) {
        fprintf(stderr, "Read timeout: expected %u bytes, got %ld\n", length, received);
        return -1;
    }

    return 0;
}

int SerialPort::JRKGetTarget(HANDLE handle)
{
    uint8_t buffer[2];
    int result = JRKGetVariable(handle, 0x02, buffer, sizeof(buffer));
    if (result)
        return -1;

    return buffer[0] + 256 * buffer[1];
}

int SerialPort::JRKGetFeedback(HANDLE handle)
{
    uint8_t buffer[2];
    int result = JRKGetVariable(handle, 0x04, buffer, sizeof(buffer));
    if (result)
        return -1;

    return buffer[0] + 256 * buffer[1];
}

void SerialPort::PrintError(const char *context)
{
    DWORD error_code = GetLastError();
    char buffer[256];
    DWORD size = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                                NULL, error_code, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                                buffer, sizeof(buffer), NULL);
    if (size == 0)
        buffer[0] = 0;

    fprintf(stderr, "%s: %s\n", context, buffer);
}
