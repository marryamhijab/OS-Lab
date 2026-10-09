#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
    // Child process
    if (argc > 1)
    {
        cout << "Child Process: PID = "
             << GetCurrentProcessId()
             << ", Parent PID = "
             << argv[1] << endl;

        return 0;
    }

    char exePath[MAX_PATH];

    GetModuleFileNameA(
        NULL,
        exePath,
        MAX_PATH
    );

    DWORD parentPID = GetCurrentProcessId();

    string command =
        "\"" + string(exePath) + "\" "
        + to_string(parentPID);

    char cmdLine[MAX_PATH + 50];

    strcpy(cmdLine, command.c_str());

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};

    si.cb = sizeof(si);

    if (!CreateProcessA(
            NULL,
            cmdLine,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        cout << "Process creation failed" << endl;
        return 1;
    }

    cout << "Parent Process: PID = "
         << parentPID
         << ", Created Child PID = "
         << pi.dwProcessId
         << endl;

    WaitForSingleObject(
        pi.hProcess,
        INFINITE
    );

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}