#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

queue<int> buffer;

const int CAPACITY = 3;

mutex mtx;

condition_variable cv_producer;
condition_variable cv_consumer;

void producer()
{
    for (int item = 1; item <= 5; item++)
    {
        unique_lock<mutex> lock(mtx);

        cv_producer.wait(
            lock,
            []()
            {
                return buffer.size() < CAPACITY;
            }
        );

        buffer.push(item);

        cout << "Produced: "
             << item
             << endl;

        cv_consumer.notify_one();
    }
}

void consumer()
{
    for (int i = 1; i <= 5; i++)
    {
        unique_lock<mutex> lock(mtx);

        cv_consumer.wait(
            lock,
            []()
            {
                return !buffer.empty();
            }
        );

        int item = buffer.front();

        buffer.pop();

        cout << "Consumed: "
             << item
             << endl;

        cv_producer.notify_one();
    }
}

int main()
{

    producer();
    consumer();

    return 0;
}