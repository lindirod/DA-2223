/**
 * @file mostTrainsAt.h
 * @brief This file defines and implements a function to calculate the maximum number of trains that can simultaneously arrive at a station.
 * 
 * @date 2023
 * 
 */
#ifndef MOST_TRAINS_AT_H
#define MOST_TRAINS_AT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "segment.h"
#include "stations.h"
/**
 * @brief Calculate the maximum number of trains that can simultaneously arrive at a station.
 *
 * This function calculates the maximum number of trains that can simultaneously arrive at a given station
 * based on the provided stations and segments information.
 *      Building the connections map takes O(M) time, where M is the number of segments.
    Checking if the input station exists in the connections map takes O(1) time on average.
    Calculating the maximum number of trains that can simultaneously arrive at the input station involves iterating over the connected stations and segments, and for each segment, finding the maximum capacity. This takes O(N * S) time, where N is the number of connected stations and S is the number of segments.
    Finally, iterating over the segment_max_trains map and summing up the maximum capacities takes O(N) time.

Therefore, the overall time complexity of the mostTrainsAt function is O(N * S), where N is the number of connected stations and S is the number of segments.
 *
 * @param stations A vector of Station objects representing the stations in the network.
 * @param segments A vector of Segment objects representing the segments connecting the stations in the network.
 * @param input_station A string representing the name of the input station for which the maximum number of trains
 *                      that can simultaneously arrive needs to be calculated.
 *
 * @return The maximum number of trains that can simultaneously arrive at the input station.
 */
int mostTrainsAt(const std::vector<Station>& stations, const std::vector<Segment>& segments, const std::string& input_station) {
      // Build a map of station -> set of connected stations
    std::unordered_map<std::string, std::vector<std::string>> connections;
    for (const auto& segment : segments) {
        connections[segment.stationA].push_back(segment.stationB);
        connections[segment.stationB].push_back(segment.stationA); 
    }

    // Check if input station exists in the connections map
    if (connections.find(input_station) == connections.end()) {
        std::cout << "Station not found in network." << std::endl;
        return 0;
    }

    // Calculate the maximum number of trains that can simultaneously arrive at the input station
    int station_max_trains = 0;
    std::unordered_map<std::string, int> segment_max_trains;
    for (const auto& connected_station : connections[input_station]) {
        for (const auto& segment : segments) {
            if ((segment.stationA == input_station && segment.stationB == connected_station)
                    || (segment.stationA == connected_station && segment.stationB == input_station)) {
                segment_max_trains[connected_station] = std::max(segment_max_trains[connected_station], segment.capacity);
            }
        }
    }
    for (const auto& pair : segment_max_trains) {
        station_max_trains += pair.second;
    }

    std::cout << "Maximum number of trains that can simultaneously arrive at station " << input_station << ": " << station_max_trains << std::endl;
    return 0;
}

#endif // MOST_TRAINS_AT_H