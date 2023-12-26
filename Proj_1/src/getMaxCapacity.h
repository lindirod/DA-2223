/**
 * @file getMaxCapacity.h
 * @brief This file defines and implements a function that calculates the maximum capacity (or maximum flow) between two stations in a flow network.
 * 
 * @date 2023
 *
 */
#ifndef GETMAXCAPACITY_H
#define GETMAXCAPACITY_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include "stations.h"
#include "segment.h"
using namespace std;
/**
 * @brief Calculates the maximum capacity (or maximum flow) between two stations in a flow network.
 * The time complexity of this function that uses common algorithms such as the
 * Edmonds-Karp algorithm, is
 * typically on the order of O(V * E^2), where V is the number of vertices
 * (stations in this case) and E is the number of edges (segments in this case)
 * in the flow network.
 * 
 * @param stationA The name of the source station.
 * @param stationB The name of the sink station.
 * @param stations A vector of Station objects representing the stations in the flow network.
 * @param segments A vector of Segment objects representing the segments between stations in the flow network.
 *
 * @return The maximum flow (which is also the maximum capacity) between stationA and stationB.
 *         Returns -1 if stationA or stationB is not found in the stations vector.
 */
int getMaxCapacity(string stationA, string stationB, const vector<Station>& stations, const vector<Segment>& segments) {
    // Find the source and sink nodes
    int source = -1, sink = -1;
    for (size_t i = 0; i < stations.size(); i++) {
        if (stations[i].name == stationA) {
            source = i;
        }
        if (stations[i].name == stationB) {
            sink = i;
        }
    }
    if (source == -1) {
        cerr << "Error: station " << stationA << " not found" << endl;
        return -1;
    }
    if (sink == -1) {
        cerr << "Error: station " << stationB << " not found" << endl;
        return -1;
    }

    // Create the adjacency matrix for the flow network
    const int n = stations.size();
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (const auto& segment : segments) {
        int i = -1, j = -1;
        for (size_t k = 0; k < stations.size(); k++) {
            if (stations[k].name == segment.stationA) {
                i = k;
            }
            if (stations[k].name == segment.stationB) {
                j = k;
            }
        }
        if (i != -1 && j != -1) {
            adjMatrix[i][j] += segment.capacity;
            adjMatrix[j][i] += segment.capacity; // assume undirected
        }
    }

    // Compute the maximum flow between the source and sink nodes using the Edmonds-Karp algorithm
    int maxFlow = 0;
    vector<vector<int>> residual(adjMatrix); // initialize residual network to the same as the original network
    vector<int> parent(n, -1);
    while (true) {
        queue<int> q;
        q.push(source);
        fill(parent.begin(), parent.end(), -1);
        parent[source] = -2;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
                if (parent[v] == -1 && residual[u][v] > 0) {
                    parent[v] = u;
                    if (v == sink) {
                        break;
                    }
                    q.push(v);
                }
            }
        }
        if (parent[sink] == -1) {
            break; // no more augmenting paths
        }
        int pathCapacity = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathCapacity = min(pathCapacity, residual[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathCapacity;
            residual[v][u] += pathCapacity; // assume undirected
        }
        maxFlow += pathCapacity;
    }

    // Return the maximum flow, which is also the maximum capacity
    return maxFlow;
}

#endif // GETMAXCAPACITY_H
