#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process
{
    string pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int wait;
};

void calculateFCFS(vector<Process>& processes)
{
    // Sort processes according to Arrival Time
    sort(
        processes.begin(),
        processes.end(),
        [](const Process& a, const Process& b)
        {
            return a.arrival < b.arrival;
        }
    );

    int currentTime = 0;

    // Calculate scheduling values
    for (int i = 0; i < processes.size(); i++)
    {
        // CPU remains idle if process has not arrived yet
        if (currentTime < processes[i].arrival)
        {
            currentTime = processes[i].arrival;
        }

        // Completion Time
        processes[i].completion =
            currentTime + processes[i].burst;

        // Turnaround Time
        processes[i].turnaround =
            processes[i].completion -
            processes[i].arrival;

        // Waiting Time
        processes[i].wait =
            processes[i].turnaround -
            processes[i].burst;

        // Move CPU time forward
        currentTime = processes[i].completion;
    }
}

int main()
{
    vector<Process> processes =
    {
        {"P1", 0, 5, 0, 0, 0},
        {"P2", 1, 3, 0, 0, 0},
        {"P3", 2, 8, 0, 0, 0}
    };

    // Apply FCFS scheduling
    calculateFCFS(processes);

    // Display results
    cout << "FCFS Scheduling" << endl;
    cout << "=============================="
         << endl;

    cout << "PID | Arrival | Burst | Completion | "
         << "Turnaround | Wait"
         << endl;

    cout << "-----------------------------------------------"
         << endl;

    double totalWaitingTime = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].pid << "  | "
             << processes[i].arrival << "       | "
             << processes[i].burst << "     | "
             << processes[i].completion << "          | "
             << processes[i].turnaround << "          | "
             << processes[i].wait
             << endl;

        totalWaitingTime += processes[i].wait;
    }

    // Calculate Average Waiting Time
    double averageWaitingTime =
        totalWaitingTime / processes.size();

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time: "
         << averageWaitingTime
         << " ms"
         << endl;

    return 0;
}