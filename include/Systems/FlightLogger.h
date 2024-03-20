#ifndef FLIGHTLOGGER_H
#define FLIGHTLOGGER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

/**
 * @brief
 * flightlogger. creates logs, that contain data abt the rocket's state changes and
 * modules' warning/error/debug messages. designed for post-flight analysis.
 *
 */
class FlightLogger
{
public:
    /**
     * @brief
     * action log entry. used by modules to describe what happened at given timestamp
     * [timestamp]. [content] contains data on what happened.
     */
    struct actionEntry
    {
        int timestamp;
        string content;
    };

    /**
     * @brief
     * module's tick's information container. [moduleName] is the owner-module's name.
     * [buffer] is the action entries that happened during tick no. [tickNumber]
     */
    struct moduleTickLog
    {
        int tickNumber;
        string moduleName;
        vector<actionEntry> buffer;
    };

    /**
     * @brief Construct a new FlightLogger object
     *
     * @param _name name of the flight logger (for debugging purposes)
     * @param _directoryPath path to flight logs directory
     * @param _fileNamePostfix filename postfix
     */
    FlightLogger(string _name, string _directoryPath, string _fileNamePostfix);

    /**
     * @brief Get the name of the flight logger object
     *
     * @return string the name of the flight logger object
     */
    string getName();

    /**
     * @brief dumps buffer contents generated during this tick to a file
     *
     */
    void dumpTickBuffer();

    /**
     * @brief appends a moduleTickLog struct to buffer
     *
     * @param _moduleTickLog moduleTickLog to append
     */
    void appendToTickBuffer(moduleTickLog _moduleTickLog);

private:
    ofstream dumpFile;
    string dumpFilePath;
    string directoryPath;

    vector<moduleTickLog> tickBuffer;
    string name;
};

#endif