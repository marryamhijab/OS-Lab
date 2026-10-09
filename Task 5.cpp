#include <iostream>

using namespace std;

int main()
{
    int parent_shared_counter = 100;

    // Simulate child's private copy
    int child_shared_counter =
        parent_shared_counter;

    child_shared_counter += 50;

    cout << "Child sees shared_counter = "
         << child_shared_counter
         << endl;

    cout << "Parent sees shared_counter = "
         << parent_shared_counter
         << endl;

    return 0;
}