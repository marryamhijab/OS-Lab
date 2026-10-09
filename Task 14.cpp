#include <iostream>
#include <windows.h>
#include <cstring>

using namespace std;

int main()
{
    const int SIZE = 1024;

    HANDLE hMapFile =
        CreateFileMappingA(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            SIZE,
            "OS_Shared_Memory"
        );

    if (hMapFile == NULL)
    {
        cout << "Shared memory creation failed."
             << endl;

        return 1;
    }

    char* ptr =
        (char*)MapViewOfFile(
            hMapFile,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            SIZE
        );

    if (ptr == NULL)
    {
        cout << "Memory mapping failed."
             << endl;

        CloseHandle(hMapFile);

        return 1;
    }

    strcpy(
        ptr,
        "OS Shared Memory Payload"
    );

    cout << "Child read from SHM: "
         << ptr
         << endl;

    UnmapViewOfFile(ptr);

    CloseHandle(hMapFile);

    return 0;
}