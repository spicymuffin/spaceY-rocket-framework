#include <iostream>
#include <string>

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

string to_hex_digit(int d)
{
    if (d < 10)
    {
        return to_string(d);
    }
    switch (d)
    {
    case 10:
    {
        return "a";
    }
    case 11:
    {
        return "b";
    }
    case 12:
    {
        return "c";
    }
    case 13:
    {
        return "d";
    }
    case 14:
    {
        return "e";
    }
    case 15:
    {
        return "f";
    }
    }
}

string charToByte(char c)
{
    int i = static_cast<int>(c);
    int d0 = i / 16 % 16;
    cout << d0 << endl;
    int d1 = i % 16;
    cout << d1 << endl;

    return "x" + to_hex_digit(d0) + to_hex_digit(d1);
}

int main(int argc, char *argv[])
{
    int a = 5;
    int b = 6;

    // create dynamically ig

    string **arr = new string *[2];
    for (int i = 0; i < 2; i++)
    {
        arr[i] = new string[2];
    }

    // cout2Darr(arr, 2, 2);

    // a = 10;

    // pointer_test(&a);

    byte bt;

    char cbt = static_cast<char>(200);
    cout << cbt << endl;
    cout << static_cast<int>(cbt) << endl;
    cout << to_hex_digit(12) << endl;
    cout << charToByte(cbt) << endl;
    return 0;
}
