#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    string pid;
    int priority;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
};

void PriorityScheduling(vector<Process>& p)
{
    int n = p.size();
    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int index = -1;
        int highestPriority = 999999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= currentTime &&
                p[i].remaining > 0 &&
                p[i].priority < highestPriority)
            {
                highestPriority = p[i].priority;
                index = i;
            }
        }

        if (index == -1)
        {
            currentTime++;
            continue;
        }

        p[index].remaining--;
        currentTime++;

        if (p[index].remaining == 0)
        {
            p[index].completion = currentTime;

            p[index].waiting =
                p[index].completion
                - p[index].arrival
                - p[index].burst;

            completed++;
        }
    }
}

int main()
{
    vector<Process> processes =
    {
        {"P1", 2, 0, 4, 4, 0, 0},
        {"P2", 1, 1, 3, 3, 0, 0},
        {"P3", 3, 2, 2, 2, 0, 0}
    };

    PriorityScheduling(processes);

    cout << "Preemptive Priority Scheduling"
         << endl;

    cout << "\nPID | Priority | Burst | Arrival | Waiting Time"
         << endl;

    cout << "------------------------------------------------"
         << endl;

    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].pid
             << "   | "
             << processes[i].priority
             << "        | "
             << processes[i].burst
             << "     | "
             << processes[i].arrival
             << "       | "
             << processes[i].waiting
             << endl;
    }

    return 0;
}