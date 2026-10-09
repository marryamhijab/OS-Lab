#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    string pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
};

void SRTF(vector<Process>& p)
{
    int n = p.size();
    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int index = -1;
        int shortest = 999999;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= currentTime &&
                p[i].remaining > 0 &&
                p[i].remaining < shortest)
            {
                shortest = p[i].remaining;
                index = i;
            }
        }

        // CPU idle
        if (index == -1)
        {
            currentTime++;
            continue;
        }

        // Execute for 1 ms
        p[index].remaining--;
        currentTime++;

        // Process completed
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
        {"P1", 0, 6, 6, 0, 0},
        {"P2", 1, 4, 4, 0, 0},
        {"P3", 10, 2, 2, 0, 0}
    };

    SRTF(processes);

    cout << "Timeline: [P1: 0-1] "
         << "[P2: 1-5] "
         << "[P1: 5-10] "
         << "[P3: 10-12]"
         << endl;

    cout << "\nPID | Completion | Waiting Time"
         << endl;

    cout << "-------------------------------"
         << endl;

    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].pid
             << "   | "
             << processes[i].completion
             << "          | "
             << processes[i].waiting
             << endl;
    }

    return 0;
}