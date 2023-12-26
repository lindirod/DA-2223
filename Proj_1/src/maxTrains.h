#include <iostream>
#include <vector>
#include <queue>
#include <cstring>  // memset
#include "stations.h"
#include "stationPair.h"
#include "segment.h"

using namespace std;

/**

*@file maxTrains.h
*@brief Implementation of the maximum flow algorithm using the Ford-Fulkerson method with Edmonds-Karp improvement.
*/
const int MAX_NODES = 100005; // maximum number of nodes
const int INF = 1e9; // infinity

// Structure to represent an edge in the graph
struct Edge {
int to; // destination node
int capacity; // capacity of the edge
int reverse_edge_index; // index of the reverse edge in the adjacency list of the destination node
};

vector<Edge> graph[MAX_NODES]; // adjacency list to store the graph
int level[MAX_NODES]; // level of each node in the BFS tree
int iterator_index[MAX_NODES]; // index of the next edge to be explored in the DFS tree

/**

*@brief Add an edge to the graph with a given capacity.
*@param from The source node of the edge.
*@param to The destination node of the edge.
*@param capacity The capacity of the edge.
*/
void add_edge(int from, int to, int capacity) {
graph[from].push_back({ to, capacity, (int)graph[to].size() });
graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}




/**

*@brief Build a level graph from the source to the sink using BFS

*@param source_node - an integer that represents the source node of the graph
*/
void bfs(int source_node) {
    memset(level, -1, sizeof(level));  // Initialize all levels to -1
    queue<int> q;
    level[source_node] = 0;
    q.push(source_node);

    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        for (Edge& edge : graph[current_node]) {
            if (edge.capacity > 0 && level[edge.to] < 0) {
                level[edge.to] = level[current_node] + 1;
                q.push(edge.to);
            }
        }
    }
}

/**

*@brief Find an augmenting path in the residual graph using DFS

*@param current_node - an integer that represents the current node being visited

*@param sink_node - an integer that represents the sink node of the graph

*@param flow - an integer that represents the flow of the path

*@return the maximum flow of the path
*/
int dfs(int current_node, int sink_node, int flow) {
    if (current_node == sink_node) {
        return flow;
    }

    for (int& i = iterator_index[current_node]; i < graph[current_node].size(); i++) {
        Edge& edge = graph[current_node][i];

        if (edge.capacity > 0 && level[current_node] < level[edge.to]) {
            int current_flow = dfs(edge.to, sink_node, min(flow, edge.capacity));

            if (current_flow > 0) {
                edge.capacity -= current_flow;
                graph[edge.to][edge.reverse_edge_index].capacity += current_flow;
                return current_flow;
            }
        }
    }

    return 0;
}

/**

*@brief Compute the maximum flow from the source to the sink in the graph using the Ford-Fulkerson algorithm with the Edmonds-Karp optimization.

*@param source_node - an integer that represents the source node

*@param sink_node - an integer that represents the sink node

*@return the maximum flow value
*/
int max_flow(int source_node, int sink_node) {
    int flow = 0;

    while (true) {
        bfs(source_node);

        if (level[sink_node] < 0) {  // If sink is not reachable from the source, terminate
            return flow;
        }

        memset(iterator_index, 0, sizeof(iterator_index));  // Reset iterator_index for each iteration
        int current_flow;

        while ((current_flow = dfs(source_node, sink_node, INF)) > 0) {
            flow += current_flow;
        }
    }

}

/**

*@brief Finds the maximum number of trains that can travel from station A to station B given a list of stations and segments.
*@param stA - a string that represents station A
*@param stB - a string that represents station B
*@param stations - a vector of Station objects that represent the stations
*@param segments - a vector of Segment objects that represent the segments between the stations
*@return the maximum number of trains that can travel from station A to station B
*/
int getMaxTrains(string stA, string stB, vector<Station> stations, vector<Segment> segments ) {
    int source = -1, sink = -1;
    for (size_t i = 0; i < stations.size(); i++) {
        if (stations[i].name == stA) {
            source = i;
        }
        if (stations[i].name == stB) {
            sink = i;
        }
    }

    for (Segment& segment : segments) {
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
        for (Station& station : stations) {
            if (station.name == segment.stationA || station.name == segment.stationB) {
                add_edge(i, j, segment.capacity);
                add_edge(j, i, segment.capacity);
            }
        }
    }
    }
    int max_flow_value = max_flow(source, sink);
    cout << "Maximum flow value: " << max_flow_value << endl;

    return 0;
}



/**

*@brief Finds the top-k most affected stations for each segment, where the most affected stations are those that share a station with the segment and have the highest capacity.

*@param stations - a vector of Station objects representing all stations in the system

*@param segments - a vector of Segment objects representing all segments in the system

*@param k - an integer representing the number of top most affected stations to find for each segment
*/
void findMostAffectedStations(vector<Station> stations, vector<Segment> segments, int k){
    // Create a vector of station pairs, where each pair is a unique combination of two stations
    vector<StationPair> stationPairs;
    for (int i = 0; i < segments.size(); i++) {
        StationPair pair = {segments[i].stationA, segments[i].stationB, segments[i].capacity};
        stationPairs.push_back(pair);
    }
    
    // Sort the station pairs in descending order of capacity
    sort(stationPairs.begin(), stationPairs.end(), [](const StationPair& a, const StationPair& b) {
        return a.maxCapacity > b.maxCapacity;
    });
    
    // Loop through each segment and find the top-k most affected stations
    for (int i = 0; i < segments.size(); i++) {
        cout << "Segment " << i+1 << ": " << segments[i].stationA << " - " << segments[i].stationB << endl;
        vector<string> affectedStations;
        int numAffected = 0;
        for (int j = 0; j < stationPairs.size(); j++) {
            if ((stationPairs[j].stationA == segments[i].stationA && stationPairs[j].stationB != segments[i].stationB)
                    || (stationPairs[j].stationA != segments[i].stationA && stationPairs[j].stationB == segments[i].stationB)) {
                // This station pair shares a station with the current segment
                string affectedStation = stationPairs[j].stationA == segments[i].stationA ? stationPairs[j].stationB : stationPairs[j].stationA;
                if (find(affectedStations.begin(), affectedStations.end(), affectedStation) == affectedStations.end()) {
                    // This station hasn't been added to the list of affected stations yet
                    affectedStations.push_back(affectedStation);
                    numAffected++;
                    if (numAffected == k) {
                        // We've found the top-k most affected stations, so we can stop searching
                        break;
                    }
                }
            }
        }
        // Print the top-k most affected stations
        for (int j = 0; j < affectedStations.size(); j++) {
            cout << "  " << j+1 << ". " << affectedStations[j] << endl;
        }
    }
}
