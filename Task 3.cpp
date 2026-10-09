#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    DWORD childPID = GetCurrentProcessId();

    cout << "Child PID: "
         << childPID
         << " terminating now"
         << endl;

    cout << "Parent sleeping for 10s without wait(). "
         << "Inspect via 'ps -l'"
         << endl;

    // Simulation of parent's delay
    Sleep(10000);

    cout << "Parent cleaned up child. Exiting."
         << endl;

    return 0;
}