#include <iostream>
#include <windows.h>

using namespace std;

// Windows exception handler
LONG WINAPI MemoryProtectionHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    if (ExceptionInfo->ExceptionRecord->ExceptionCode ==
        EXCEPTION_ACCESS_VIOLATION)
    {
        cout << "Hardware memory protection trap caught!" << endl;

        // Terminate the program after catching the exception
        ExitProcess(0);
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
    // Allocate one 4 KB virtual memory page
    // with READ-WRITE permission
    char* page = (char*)VirtualAlloc(
        NULL,
        4096,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    if (page == NULL)
    {
        cout << "Memory allocation failed!" << endl;
        return 1;
    }

    // Normal write
    page[0] = 'A';

    cout << "Normal write successful." << endl;

    // Change page permission from READ-WRITE to READ-ONLY
    DWORD oldProtect;

    if (!VirtualProtect(
            page,
            4096,
            PAGE_READONLY,
            &oldProtect))
    {
        cout << "VirtualProtect failed!" << endl;

        VirtualFree(page, 0, MEM_RELEASE);
        return 1;
    }

    cout << "Page permission changed to READ-ONLY." << endl;

    // Install Windows exception handler
    AddVectoredExceptionHandler(
        1,
        MemoryProtectionHandler
    );

    cout << "Attempting to write to READ-ONLY memory..." << endl;

    // Illegal write
    // CPU/MMU generates an access violation
    page[0] = 'B';

    // This line will not execute because the handler
    // terminates the program.
    VirtualFree(page, 0, MEM_RELEASE);

    return 0;
}

