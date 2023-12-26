/**
 * @file segment.h
 * @brief This file defines the Segment struct.
 * 
 * @date 2023
 *
 */
#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <vector>
/**
 * Struct representing a train segment between two stations.
 */
struct Segment {
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
     * @param capacity - The maximum number of trains that can run on the segment
     * 
     */
int capacity;
 /**
     * @param flow - The current number of trains running on the segment. 
     * 
     */
int flow;
 /**
     * @param service - a string that represents the type of service running on the segment
     * 
     */
std::string service;
};

std::vector<Segment> readSegmentsFromFile(std::string filename);

#endif