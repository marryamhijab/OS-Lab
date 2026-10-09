#include <iostream>
#include <queue>

using namespace std;

struct Process
{
    string pid;
    int burst;
    int remaining;
    int arrival;
    int queueLevel;
};

int main()
{
    Process p1 = {"P1", 7, 7, 0, 1};
    Process p2 = {"P2", 1, 1, 2, 1};

    queue<Process*> q1;
    queue<Process*> q2;
    queue<Process*> q3;

    int currentTime = 0;

    // -------------------------
    // P1 enters Q1
    // -------------------------

    q1.push(&p1);

    cout << "Time 0: P1 enters Q1"
         << endl;

    // Q1 Quantum = 2
    Process* p = q1.front();
    q1.pop();

    p->remaining -= 2;
    currentTime += 2;
    p->queueLevel = 2;

    q2.push(p);

    cout << "Time 0: P1 runs 2 ms"
         << " -> Demoted to Q2"
         << endl;

    // -------------------------
    // P2 arrives at time 2
    // -------------------------

    q1.push(&p2);

    cout << "Time 2: P2 enters Q1"
         << endl;

    // P2 runs 1 ms
    p = q1.front();
    q1.pop();

    p->remaining -= 1;
    currentTime += 1;

    cout << "Time 2: P2 runs 1 ms"
         << " -> Finished"
         << endl;

    // -------------------------
    // P1 runs from Q2
    // -------------------------

    p = q2.front();
    q2.pop();

    p->remaining -= 4;
    currentTime += 4;
    p->queueLevel = 3;

    q3.push(p);

    cout << "Time 3: P1 from Q2 runs 4 ms"
         << " -> Demoted to Q3"
         << endl;

    // -------------------------
    // Aging
    // -------------------------

    cout << "Time 7: Aging trigger"
         << endl;

    // Promote P1 from Q3 to Q1
    p = q3.front();
    q3.pop();

    p->queueLevel = 1;

    q1.push(p);

    cout << "Time 7: P1 promoted back to Q1"
         << endl;

    // -------------------------
    // P1 runs in Q1
    // -------------------------

    p = q1.front();
    q1.pop();

    p->remaining--;

    currentTime++;

    cout << "Time 7: P1 runs 1 ms"
         << " -> Finished"
         << endl;

    cout << "\nAll jobs completed."
         << endl;

    return 0;
}