/**
 * @file real_world_tsp.h
 * @brief Code for solving the Traveling Salesman Problem (TSP) using Triangular Approximation Algorithm for the real-world graphs - 4.2 
 * 
 */
#ifndef REAL_WORLD_TSP_H
#define REAL_WORLD_TSP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include "csv.h"

const double EARTH_RADIUS_KM = 6371.0;
/**
 * @brief Convert degrees to radians.
 *
 * @param degrees The angle in degrees.
 * @return The angle in radians.
 */
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

/**
 * @brief Calculate the Haversine distance between two points given their latitude and longitude.
 *
 * @param lat1 The latitude of the first point.
 * @param lon1 The longitude of the first point.
 * @param lat2 The latitude of the second point.
 * @param lon2 The longitude of the second point.
 * @return The Haversine distance between the two points.
 */
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

/**
 * @brief Find the nearest neighbor node not visited yet. 
 * The time complexity of this function is O(n), where n is the number of nodes.
 *
 * @param currentNode The current node.
 * @param visited A vector indicating whether a node has been visited.
 * @param distances The matrix of distances between nodes.
 * @return The index of the nearest neighbor.
 *
 */
int findNearestNeighbor(int currentNode, const std::vector<bool>& visited, const std::vector<std::vector<double>>& distances) {
    int numNodes = visited.size();
    int nearestNeighbor = -1;
    double minDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i] && distances[currentNode][i] < minDistance) {
            minDistance = distances[currentNode][i];
            nearestNeighbor = i;
        }
    }

    return nearestNeighbor;
}

/**
 * @brief Perform the Triangular Approximation Heuristic algorithm.
 * The time complexity of this function is O(n^2), where n is the number of nodes.
 *
 * @param nodes The vector of node data.
 * @param distances The matrix of distances between nodes.
 * @return A vector representing the tour.
 *
 */
std::vector<int> triangularApproximation(const std::vector<NodeData>& nodes, const std::vector<std::vector<double>>& distances) {
    int numNodes = nodes.size();
    std::vector<bool> visited(numNodes, false);
    std::vector<int> tour;
    tour.reserve(numNodes);

    // Start at the node with the zero-identifier label
    int currentNode = 0;
    visited[currentNode] = true;
    tour.push_back(currentNode);

    // Select the nearest neighbor node not visited yet as the next node to visit
    for (int i = 0; i < numNodes - 1; ++i) {
        int nearestNeighbor = findNearestNeighbor(currentNode, visited, distances);
        currentNode = nearestNeighbor;
        visited[currentNode] = true;
        tour.push_back(currentNode);
    }

    // Add an edge from the last visited node back to the starting node
    tour.push_back(0);

    return tour;
}

/**
 * @brief Solve TSP using the Triangular Approximation Heuristic for real-world graphs.
 * The time complexity of this function depends on the number of nodes and edges in the input graph.
 *
 * @param nodesFile The name of the CSV file containing the node data.
 * @param edgesFile The name of the CSV file containing the edge data.
 *
 */
void solveTSPreal(const std::string& nodesFile, const std::string& edgesFile) {
    // Load node data
    std::vector<NodeData> nodes = loadNodesGraph(nodesFile);

    // Load edge data
    std::vector<EdgeData> edges = loadEdgeGraph(edgesFile);

    // Create a distance matrix
    int numNodes = nodes.size();
    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));

    // Initialize the distance matrix with the provided distances in the edge data
    for (const EdgeData& edge : edges) {
        distances[edge.origin][edge.destination] = edge.distance;
        distances[edge.destination][edge.origin] = edge.distance;
    }

    // Calculate the geographic distances for missing edges
    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            if (distances[i][j] == 0.0) {
                double lat1 = nodes[i].latitude;
                double lon1 = nodes[i].longitude;
                double lat2 = nodes[j].latitude;
                double lon2 = nodes[j].longitude;

                double distance = haversineDistance(lat1, lon1, lat2, lon2);
                distances[i][j] = distance;
                distances[j][i] = distance;
            }
        }
    }

    // Perform the Triangular Approximation Heuristic
    std::vector<int> tour = triangularApproximation(nodes, distances);

   // Print the tour
    std::cout << "Tour: ";
    for (int i = 0; i < numNodes; ++i) {
    std::cout << tour[i] << " ";
    if ((i + 1) % 10 == 0) {
        std::cout << std::endl; // Add a line break after every 10 nodes
    }
   }
    std::cout << std::endl;

  // Calculate the total distance of the tour
   double totalDistance = 0.0;
    for (int i = 0; i < numNodes; ++i) {
    totalDistance += distances[tour[i]][tour[(i + 1) % numNodes]];
    }

// Print the total distance
std::cout << "Total Distance: " << totalDistance << " Units" << std::endl;
}

#endif  // REAL_WORLD_TSP_H