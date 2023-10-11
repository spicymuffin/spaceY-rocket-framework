#include <iostream>

using namespace std;

void pointer_test(int *referenced)
{
    *referenced += 1;
    cout << *referenced << endl;
}

int main(int argc, char *argv[])
{
    int a = 5;
    int b = 6;

    pointer_test(&a);

    cout << "test" << endl;
}
