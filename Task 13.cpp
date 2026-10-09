#include <iostream>
#include <windows.h>
#include <cstring>

using namespace std;

int main()
{
    HANDLE readPipe;
    HANDLE writePipe;

    SECURITY_ATTRIBUTES sa;

    sa.nLength =
        sizeof(SECURITY_ATTRIBUTES);

    sa.lpSecurityDescriptor =
        NULL;

    sa.bInheritHandle =
        TRUE;

    if (!CreatePipe(
            &readPipe,
            &writePipe,
            &sa,
            0))
    {
        cout << "Pipe creation failed."
             << endl;

        return 1;
    }

    const char* message =
        "Hello Child from Kernel Pipe";

    DWORD bytesWritten = 0;

    WriteFile(
        writePipe,
        message,
        (DWORD)strlen(message),
        &bytesWritten,
        NULL
    );

    char buffer[100];

    DWORD bytesRead = 0;

    ReadFile(
        readPipe,
        buffer,
        sizeof(buffer) - 1,
        &bytesRead,
        NULL
    );

    buffer[bytesRead] = '\0';

    cout << "Child read from pipe: "
         << buffer
         << endl;

    CloseHandle(readPipe);
    CloseHandle(writePipe);

    return 0;
}