/**
 * @file stations.h
 * @brief This file contains the definition of functions related to the Station struct 
 * 
 * @date 2023
 * 
 */
#ifndef STATIONS_H
#define STATIONS_H

#include <string>
#include <vector>

/**
 * Struct that contains the information about a station.
 */
struct Station {
    /**
     * @param name - a string that represents the name of a station
     * 
     */
std::string name;
/**
     * @param district - a string that represents the district of a station
     * 
     */
std::string district;
/**
     * @param municipality - a string that represents the municipality of a station
     * 
     */
std::string municipality;
/**
     * @param township - a string that represents the township of a station
     * 
     */
std::string township;
/**
     * @param line - a string that represents the line that passes at a station
     * 
     */
std::string line;
};

std::vector<Station> readStationsFromFile(std::string filename);

#endif