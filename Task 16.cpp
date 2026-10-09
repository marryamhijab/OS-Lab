#include <iostream>
#include <vector>
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
    bool completed;
};

void calculateSJF(vector<Process>& p)
{
    int n = p.size();
    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int index = -1;
        int shortestBurst = 999999;

        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed &&
                p[i].arrival <= currentTime &&
                p[i].burst < shortestBurst)
            {
                shortestBurst = p[i].burst;
                index = i;
            }
        }

        // No process is available
        if (index == -1)
        {
            currentTime++;
            continue;
        }

        // Execute selected process
        currentTime += p[index].burst;

        p[index].completion = currentTime;

        p[index].turnaround =
            p[index].completion - p[index].arrival;

        p[index].wait =
            p[index].turnaround - p[index].burst;

        p[index].completed = true;

        completed++;
    }
}

int main()
{
    vector<Process> processes =
    {
        {"P1", 0, 6, 0, 0, 0, false},
        {"P2", 0, 8, 0, 0, 0, false},
        {"P3", 2, 2, 0, 0, 0, false}
    };

    calculateSJF(processes);

    cout << "SJF Scheduling (Non-Preemptive)" << endl;
    cout << "==================================" << endl;

    cout << "PID | Arrival | Burst | Completion | "
         << "Turnaround | Wait" << endl;

    cout << "-----------------------------------------------"
         << endl;

    double totalWait = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].pid << "   | "
             << processes[i].arrival << "       | "
             << processes[i].burst << "     | "
             << processes[i].completion << "          | "
             << processes[i].turnaround << "          | "
             << processes[i].wait << endl;

        totalWait += processes[i].wait;
    }

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time: "
         << totalWait / processes.size()
         << " ms" << endl;

    return 0;
}