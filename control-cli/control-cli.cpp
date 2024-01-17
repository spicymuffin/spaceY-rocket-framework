#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string version = "0.1";

class Command
{
public:
    Command(string _name, string _helpString, vector<vector<string>> _parameterList);
    virtual int exec() = 0;

protected:
    string name;
    string helpString;
    vector<vector<string>> parameterList;
};

Command::Command(string _name, string _helpString, vector<vector<string>> _parameterList)
{
    name = _name;
    helpString = _helpString;
    parameterList = _parameterList;
}

vector<vector<string>> exitCommandParameterList = {{}};
class ExitCommand : Command
{

public:
    ExitCommand() : Command("exit", "quits the cli", exitCommandParameterList) {}
    virtual int exec() override
    {
        string input;
        cout << "confirm (type 'y'): ";
        cin >> input;
        if (input == "y")
        {
            exit(0);
            return 0;
        }
        else
        {
            return -1;
        }
    }
};

vector<vector<string>> helpCommandParameterList = {{}};
class HelpCommand : Command
{
public:
    HelpCommand() : Command("help", "help for help??? lol", helpCommandParameterList){};
    virtual int exec() override
    {
        cout << "placeholder help message." << endl;
        return 0;
    }
};

vector<vector<string>> CommandParameterList = {{}};

int main(int argc, char *argv[])
{
    cout << "spaceY ground control cli ver. " << version << endl;

    cout << "type help to get started." << endl;

    while (true)
    {
        string input = "";
        cin >> input;
    }

    return 0;
}

// ping - displays latency between rocket's comms module and

// Rocket class
// comms module(s) (rocket system) - has interface to all RocketComponents
// every RocketModule has an interface that is accessible through comms component
//
// every communicationsystem assigns a byte to each rocketmodule to encode
// a number (0-255) which signifies which module is this command assigned to

// communication standard:
//
// BYTE 0: action identfier-byte (0-255)
// x00 - establisComms (initializer handshake)
// x01 - ping
// x02 - data transfer complete ACK
// x03 - communicate with module

// x00
// arguments encodes length of greetstring (?)

// x01
// encode timestamp

// x02
// something about the size of the transferred data.

// x03
// 1 byte command identifier
// encodes 256 commands
//
// 2-3 command argc bytes (0-65536)
// unsigned short int
//
// arguments encoded:
// datatype signifier byte -> data
// some datatypes dont have a fixed amount of bytes,
// must be ended manually within datatype.