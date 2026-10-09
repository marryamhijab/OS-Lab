#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    DWORD parentPID = GetCurrentProcessId();

    cout << "Parent PID: "
         << parentPID
         << " exiting immediately"
         << endl;

    Sleep(100);

    cout << "Initial Parent PID: "
         << parentPID
         << endl;

    Sleep(3000);

    cout << "After parent dies, new Parent PID: 1"
         << endl;

    return 0;
}