/**
 * @file getMinCost.h
 * @brief This file contains the definition of the getMinCost function.
 * 
 * @date 2023
 * 
 */

#ifndef GETMINCOST_H
#define GETMINCOST_H

#include <string>
#include <vector>
#include <queue>
#include <climits>
#include "stations.h"
#include "segment.h"
#include "getMaxCapacity.h"

using namespace std;
/**
 * @brief Function to get the minimum cost for the maximum flow between two stations.
 * 
 * @param stationA - source station
 * @param stationB - destination station
 * @param stations - vector of 'Station' objects that describes all the stations in the network
 * @param segments - vector of 'Segment' objects that describes all the segments (connections) between the stations
 * @return minimum cost per unit of flow for the maximum flow 
 */
int getMinCost(string stationA, string stationB, const vector<Station>& stations, const vector<Segment>& segments) {
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

    // Compute the maximum flow between the source and sink nodes using the Edmonds-Karp algorithm
    int maxCapacity = getMaxCapacity(stationA, stationB, stations, segments);
    if (maxCapacity == -1) {
        cerr << "Error: cannot compute maximum capacity" << endl;
        return -1;
    }

    // Initialize the adjacency matrix for the cost network
    const int n = stations.size();
    vector<vector<int>> cost(n, vector<int>(n, 0));
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
            int segmentCost = (segment.service == "ALFA") ? 4 : 2;
            cost[i][j] = segment.capacity * segmentCost;
            cost[j][i] = segment.capacity * segmentCost; // assume undirected
        }
    }

    //Find the minimum cost for the maximum flow using Dijkstra's Algorithm
    const int INF = INT_MAX / 2;
    vector<int> dist(n, INF);
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));
    vector<int> parent(n, -1);
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < n; v++) {
            if (cost[u][v] > 0 && dist[u] < INF && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Return the minimum cost per unit of flow for the maximum flow
    return dist[sink] / maxCapacity;
}

#endif /* GETMMINCOST_H */
