/**
 * @file csv.h
 * @brief This file contains the declarations and implementation of functions related to the reading and parsing of CSV files
 * 
 * @date 2023
 * 
 */
#ifndef CSV_H
#define CSV_H

#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "stations.h"
#include "segment.h"

using namespace std;
/**
 * @brief Reads station information from a file and returns a vector of stations. This function reads the station information from a specified file, skipping the header line and parsing each subsequent

line to extract the station name, district, municipality, township, and line information. The station name is then

modified to replace spaces with underscores before creating a new Station object and adding it to a vector of Station objects.
 * 
 * @param filename The name of the file containing the station information.
 * @return A vector of Station objects containing the parsed station information.
 */
vector<Station> readStationsFromFile(string filename) {
    vector<Station> stations;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        getline(inputFile, line); // skip the header line
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string name, district, municipality, township, lineString;
            getline(ss, name, ',');
            getline(ss, district, ',');
            getline(ss, municipality, ',');
            getline(ss, township, ',');
            getline(ss, lineString);

            // Replace spaces with underscores in station name
            for (char& c : name) {
                if (c == ' ') {
                    c = '_';
                }
            }

            stations.push_back({name, district, municipality, township, lineString});
        }
        inputFile.close();
    }
    return stations;
}

/**
 * @brief Reads segment information from a file and returns a vector of segments.

This function reads the segment information from a specified file, skipping the header line and parsing each subsequent

non-empty line to extract the station names, capacity, and service information. The station names are then modified to

replace spaces with underscores before creating a new Segment object and adding it to a vector of Segment objects.
 * 
 * @param filename The name of the file containing the segment information.
 * @return A vector of Segment objects containing the parsed segment information.
 */
vector<Segment> readSegmentsFromFile(string filename) {
    vector<Segment> segments;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        getline(inputFile, line); // skip the header line
        while (getline(inputFile, line)) {
            if (!line.empty()) {
                stringstream ss(line);
                string stationA, stationB, service;
                int capacity, flow = 0;
                getline(ss, stationA, ',');
                getline(ss, stationB, ',');
                ss >> capacity;
                ss.ignore();
                getline(ss, service);

                // Replace spaces in station names with underscores
                replace(stationA.begin(), stationA.end(), ' ', '_');
                replace(stationB.begin(), stationB.end(), ' ', '_');

                segments.push_back({stationA, stationB, capacity, flow, service});
            }
        }
        inputFile.close();
    }
    return segments;
}




#endif // CSV_H