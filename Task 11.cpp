#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int shared_data = 0;

mutex rw_lock;

void reader(int id)
{
    lock_guard<mutex> lock(rw_lock);

    cout << "Reader "
         << id
         << " read value: "
         << shared_data
         << endl;
}

void writer(int id, int value)
{
    lock_guard<mutex> lock(rw_lock);

    shared_data = value;

    cout << "Writer "
         << id
         << " updated value to: "
         << shared_data
         << endl;
}

int main()
{
    writer(1, 42);

    thread r1(reader, 1);
    thread r2(reader, 2);

    r1.join();
    r2.join();

    writer(2, 99);

    reader(3);

    return 0;
}