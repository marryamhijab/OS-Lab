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
        cout << "Child executing task..." << endl;

        Sleep(2000);

        cout << "Child exiting with code 42" << endl;

        return 42;
    }

    char exePath[MAX_PATH];

    GetModuleFileNameA(
        NULL,
        exePath,
        MAX_PATH
    );

    string command =
        "\"" + string(exePath) + "\" child";

    char cmdLine[MAX_PATH + 20];

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

    cout << "Parent waiting for child..." << endl;

    WaitForSingleObject(
        pi.hProcess,
        INFINITE
    );

    DWORD exitCode = 0;

    GetExitCodeProcess(
        pi.hProcess,
        &exitCode
    );

    cout << "Parent: Child terminated with exit status "
         << exitCode
         << endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}