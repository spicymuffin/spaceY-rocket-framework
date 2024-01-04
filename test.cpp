#include <iostream>

using namespace std;

void pointer_test(int *referenced)
{
    *referenced += 1;
    cout << *referenced << endl;
}

void cout2Darr(string **arr2D, int columns, int rows)
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            cout << *(*(arr2D + columns) + rows) << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    int a = 5;
    int b = 6;

    // create dynamically ig

    string **arr = new string*[2];
    for (int i = 0; i < 2; i++)
    {
        arr[i] = new string[2];
    }

    cout2Darr(arr, 2, 2);

    a = 10;

    pointer_test(&a);

    cout << "test" << endl;

    return 0;
}
