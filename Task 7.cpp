#include <iostream>
#include <thread>

using namespace std;

void worker_multiply_row(
    int row,
    int matrix[3][3],
    int vector[3],
    int result[3])
{
    int sum = 0;

    for (int col = 0; col < 3; col++)
    {
        sum += matrix[row][col] * vector[col];
    }

    result[row] = sum;
}

int main()
{
    int matrix[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int vector[3] =
    {
        1, 2, 3
    };

    int result[3] =
    {
        0, 0, 0
    };

    thread t1(
        worker_multiply_row,
        0,
        matrix,
        vector,
        result
    );

    thread t2(
        worker_multiply_row,
        1,
        matrix,
        vector,
        result
    );

    thread t3(
        worker_multiply_row,
        2,
        matrix,
        vector,
        result
    );

    t1.join();
    t2.join();
    t3.join();

    cout << "Result Vector: ["
         << result[0] << ", "
         << result[1] << ", "
         << result[2] << "]"
         << endl;

    return 0;
}