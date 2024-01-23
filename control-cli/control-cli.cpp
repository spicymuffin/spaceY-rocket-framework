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

    cout << "type 'help' to get started." << endl;

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

// ROCKET COMMUNICATION PROTOCOL DEFINITION:

// SECTION 1: supported datatypes, encoding.

// datatypes are encoded by having a fixed length
// first the datatpe that has to de(en)coded is declared by
// a datatype signifier-byte

// x00 int (fixed, 4 bytes)
// x01 uint (fixed, 4 bytes)
// x02 short int (fixed, 2 bytes)
// x03 char (fixed, 1 byte)
// x04 float (fixed, 8 bytes)
// x05 double (fixed, 16 bytes)
// x06 bool (fixed, 1 byte)

// x11 container -> short int (encodes container lenghth)
// x12 rocketmodule reference (fixed, 2 bytes)

// SECTION 2: command decoding

// BYTE 0: action identfier-byte (0-255)
// x00 - establisComms (initializer handshake)
// x01 - ping
// x02 - data transfer complete ACK
// x03 - communicate with module

// x00
// cli sends a hanshake packet to the rocket (which is listening)
// rocket receives the handshake packet
// rocket ACKs by re-encoding the greetstring back

// x01
// cli sends ping packet
// rocket receives the ping packet
// rocket encodes the receival timestamp to a packet and replies with it
// to the cli

// x02
// initiate data transfer packet is sent by the transmitting endpoint
// transferred data SHA256

// x03 (ACK-enabled)
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

// x04
// ACK packet. next byte encodes completeion status code
// next bytes is a transmission control identificator

// completion status codes legend:
// x00 - success
// x01 - unknown error (don't use this)
// the rest of completion status codes should be defined in advance.

// transmission control identificator legend:
// x00 - transmission over
// x01 - await for data transfer initialization


// SECTION 3: examples

// IMU commands (IMU is component x00)
// x03x00:
// x01 - send IMU datapack

// cli sends x03x00x01 (cli uses a method designed to communicate with )
// rocket responds with ACK: x04x00x01
// cli receives ACK, awaits data transfer, knowing