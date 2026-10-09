#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process
{
    string pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
};

void RoundRobin(vector<Process>& p, int quantum)
{
    queue<int> readyQueue;

    int n = p.size();
    int currentTime = 0;
    int completed = 0;

    // Initially available processes
    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival == 0)
        {
            readyQueue.push(i);
        }
    }

    while (completed < n)
    {
        if (readyQueue.empty())
        {
            currentTime++;

            for (int i = 0; i < n; i++)
            {
                if (p[i].arrival == currentTime &&
                    p[i].remaining > 0)
                {
                    readyQueue.push(i);
                }
            }

            continue;
        }

        int index = readyQueue.front();
        readyQueue.pop();

        int startTime = currentTime;

        int executionTime;

        if (p[index].remaining < quantum)
        {
            executionTime = p[index].remaining;
        }
        else
        {
            executionTime = quantum;
        }

        p[index].remaining -= executionTime;
        currentTime += executionTime;

        cout << p[index].pid
             << " (" << executionTime << " ms) -> ";

        // Add newly arrived processes
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival > startTime &&
                p[i].arrival <= currentTime &&
                p[i].remaining > 0)
            {
                readyQueue.push(i);
            }
        }

        if (p[index].remaining > 0)
        {
            readyQueue.push(index);
        }
        else
        {
            p[index].completion = currentTime;

            p[index].turnaround =
                p[index].completion -
                p[index].arrival;

            p[index].waiting =
                p[index].turnaround -
                p[index].burst;

            completed++;
        }
    }

    cout << "END" << endl;
}

int main()
{
    vector<Process> processes =
    {
        {"P1", 0, 3, 3, 0, 0, 0},
        {"P2", 0, 2, 2, 0, 0, 0},
        {"P3", 0, 4, 4, 0, 0, 0}
    };

    int quantum = 2;

    cout << "Quantum = "
         << quantum
         << " ms"
         << endl;

    cout << "Execution: ";

    RoundRobin(processes, quantum);

    cout << "\nPID | Turnaround | Wait"
         << endl;

    cout << "-----------------------"
         << endl;

    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].pid
             << "   | "
             << processes[i].turnaround
             << "          | "
             << processes[i].waiting
             << endl;
    }

    return 0;
}