/**
 * @file findMostDemandingStations.h
 * @brief This file defines and implements a function that finds the pairs of stations that demand the most amount of trains.
 * 
 * @date 2023
 *
 */
#ifndef FINDMOSTDEMANDINGSTATIONS_H
#define FINDMOSTDEMANDINGSTATIONS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "stations.h"
#include "segment.h"
#include "stationPair.h"
/**
 * @brief Finds the pairs of stations with the most amount of trains needed.
 *
 * This function takes a vector of Station objects and a vector of Segment objects
 * as input. It calculates the maximum capacity (total capacity) between each pair
 * of stations based on the segments connecting them, and then sorts the station
 * pairs in descending order of maximum capacity. Finally, it prints the pairs
 * of stations with their maximum capacity.
 *  The time complexity of the findMostDemandingStations function is: O(n^3 log n) where n is the number of stations. This is because of the nested loops and sorting operation in the function.
 *  The first loop has an O(n) time complexity since it iterates through the stations vector, which contains n stations.
    The second loop iterates over the stations vector as well, but it does so starting from the subsequent station. As a consequence, the first station receives n-1 iterations, the second station receives n-2 iterations, and so on, for a total of (n-1) + (n-2) +... + 1 iterations. O(n^2) is the overall time complexity as a result.
    The third loop, which can take m iterations to complete, iterates over the segments vector and has an O(m) time complexity.
    An if-statement that has an O(1) time complexity is contained inside the third loop and checks for matching station names.
    The stationPairs vector, which contains n(n-1)/2 pairs, is then given the sort function to run on it. O(n^2 log n) time complexity is required to sort n(n-1)/2 pairs.

Since the most time-consuming operations in the function take up the most time, the findMostDemandingStations function's overall time complexity is O(n^3 log n).


 * @param stations The vector of Station objects representing the stations.
 * @param segments The vector of Segment objects representing the segments.
 */
void findMostDemandingStations(const std::vector<Station>& stations, const std::vector<Segment>& segments){
// create a vector of station pairs with their maximum capacity
    vector<StationPair> stationPairs;
    for (auto it1 = stations.begin(); it1 != stations.end(); ++it1) {
        for (auto it2 = it1 + 1; it2 != stations.end(); ++it2) {
            int maxCapacity = 0;
            for (auto segment : segments) {
                if ((segment.stationA == it1->name && segment.stationB == it2->name) ||
                    (segment.stationA == it2->name && segment.stationB == it1->name)) {
                    maxCapacity += segment.capacity;
                }
            }
            stationPairs.push_back({it1->name, it2->name, maxCapacity});
        }
    }

    // sort the station pairs by their maximum capacity in descending order
    sort(stationPairs.begin(), stationPairs.end(), compareStationPairs);

    // print the station pairs with their maximum capacity
    cout << "Pairs of stations with the most amount of trains needed:" << endl;
    for (auto pair : stationPairs) {
        if (pair.maxCapacity > 0) {
            cout << pair.stationA << " - " << pair.stationB << ": " << pair.maxCapacity << endl;
        }
    }
};
#endif // FINDMOSTDEMANDINGSTATIONS_H



