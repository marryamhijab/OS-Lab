#include <iostream>
#include <windows.h>

int main() {
    HANDLE readPipe, writePipe;

    CreatePipe(&readPipe, &writePipe, nullptr, 0);
      
    const char message[] = "Hello through the pipe!";
    DWORD written = 0, read = 0;
    char buffer[100] = {};

    WriteFile(
        writePipe,
        message,
        sizeof(message),
        &written,
        nullptr
    );

    ReadFile(
        readPipe,
        buffer,
        sizeof(buffer),
        &read,
        nullptr
    );

    std::cout << buffer << "\n";

    CloseHandle(readPipe);
    CloseHandle(writePipe);

    return 0;
}