#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex rw_lock;
condition_variable cv;

int sharedData = 100;
int activeReaders = 0;
bool writerActive = false;

// Reader function
void reader(int id)
{
    // Reader waits while writer is active
    {
        unique_lock<mutex> lock(rw_lock);

        cv.wait(lock, [] {
            return !writerActive;
        });

        activeReaders++;
    }

    // Multiple readers can read together
    cout << "Reader " << id
         << " read value: " << sharedData << "\n";

    // Reader finished
    {
        unique_lock<mutex> lock(rw_lock);

        activeReaders--;

        if (activeReaders == 0)
            cv.notify_all();
    }
}

// Writer function
void writer(int val)
{
    // Wait until there are no readers
    unique_lock<mutex> lock(rw_lock);

    cv.wait(lock, [] {
        return activeReaders == 0 && !writerActive;
    });

    writerActive = true;

    // Update shared data
    sharedData = val;

    cout << "Writer updated value to: "
         << sharedData << "\n";

    writerActive = false;

    cv.notify_all();
}

int main()
{
    thread r1(reader, 1);
    thread r2(reader, 2);
    thread w1(writer, 200);
    thread r3(reader, 3);

    r1.join();
    r2.join();
    w1.join();
    r3.join();

    return 0;
}

