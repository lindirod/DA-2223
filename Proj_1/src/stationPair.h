/**
 * @file stationPair.h
 * @brief This file defines the StationPair struct that represents a pair of two stations with a maximum capacity.
 * 
 * @date 2023
 *
 */
#ifndef STATIONPAIR_H
#define STATIONPAIR_H

#include <string>
/**
 * Struct representing a pair of two stations with a maximum capacity.
 */
struct StationPair {
    /**
     * @param stationA - a string that represents the name of the source station
     * 
     */
    std::string stationA;
    /**
     * @param stationB - a string that represents the name of the destination station
     * 
     */
    std::string stationB;
    /**
     * @param maxCapacity - The maximum capacity of the station pair
     * 
     */
    int maxCapacity;
};
/**
 * @brief Compares two StationPairs based on their maximum capacity. The compareStationPairs function has a time complexity of O(1), which means it takes constant time to execute.

The reason for this is that the function performs a simple comparison of the maximum capacity values of two StationPair objects, and the comparison operation itself takes constant time. It does not involve any loops or other operations that depend on the size of the input, so the time complexity remains constant.
 * 
 * @param a The first StationPair to compare.
 * @param b The second StationPair to compare.
 * @return True if the maximum capacity of StationPair a is greater than that of StationPair b, false otherwise.
 */
bool compareStationPairs(const StationPair& a, const StationPair& b) {
    return a.maxCapacity > b.maxCapacity;
};
#endif // STATIONPAIR_H
