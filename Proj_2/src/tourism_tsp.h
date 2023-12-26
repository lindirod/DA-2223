/**
 * @file tourism_tsp.h
 * @brief Code for solving the Traveling Salesman Problem (TSP) for tourism routes using the Triangular Approximation Algorithm for the tourism toy graph - 4.2.
 */
#ifndef TOURISM_TSP_H
#define TOURISM_TSP_H

#include <iostream> 
#include <vector>
#include <limits>
#include "csv.h"

/**
 * @brief Find the nearest neighbor node not visited yet.
 * The time complexity of this function is O(n), where n is the number of nodes.
 * @param currentNode The current node.
 * @param visited A vector indicating whether a node has been visited.
 * @param distances The matrix of distances between nodes.
 * @return The index of the nearest neighbor.
 *
 */
int findNearestNeighborTourism(int currentNode, const std::vector<bool>& visited, const std::vector<std::vector<double>>& distances) {
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
 * @brief Perform the Triangular Approximation Heuristic for tourism routes.
 * The time complexity of this function is O(n^2), where n is the number of nodes.
 * @param edges The vector of tourism route data.
 * @param numNodes The number of nodes in the graph.
 * @return A vector representing the tour.
 *
 */
std::vector<int> triangularApproximationTourism(const std::vector<TourismData>& edges, int numNodes) {
    // Create a distance matrix
    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));

    // Initialize the distance matrix with the provided distances in the edge data
    for (const TourismData& edge : edges) {
        distances[edge.origin][edge.destination] = edge.distance;
        distances[edge.destination][edge.origin] = edge.distance;
    }

    std::vector<bool> visited(numNodes, false);
    std::vector<int> tour;
    tour.reserve(numNodes);

    // Start at the node with the zero-identifier label
    int currentNode = 0;
    visited[currentNode] = true;
    tour.push_back(currentNode);

    // Select the nearest neighbor node not visited yet as the next node to visit
    for (int i = 0; i < numNodes - 1; ++i) {
        int nearestNeighbor = findNearestNeighborTourism(currentNode, visited, distances);
        currentNode = nearestNeighbor;
        visited[currentNode] = true;
        tour.push_back(currentNode);
    }

    // Add an edge from the last visited node back to the starting node
    tour.push_back(0);

    return tour;
}

/**
 * @brief Solve TSP for tourism routes using the Triangular Approximation Heuristic.
 * The time complexity of this function depends on the number of nodes and edges in the input graph.
 * @param filename The name of the CSV file containing the tourism route data.
 *
 */
void solveTSPTourism(const std::string& filename) {
    // Load tourism data
    std::vector<TourismData> tourismData = loadTourismGraph(filename);

    // Get the number of nodes
    int numNodes = 0;
    for (const TourismData& data : tourismData) {
        numNodes = std::max(numNodes, std::max(data.origin, data.destination) + 1);
    }

    // Perform the Triangular Approximation Heuristic
    std::vector<int> tour = triangularApproximationTourism(tourismData, numNodes);

    // Create a distance matrix
    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));

    // Initialize the distance matrix with the provided distances in the tourism data
    for (const TourismData& data : tourismData) {
        distances[data.origin][data.destination] = data.distance;
        distances[data.destination][data.origin] = data.distance;
    }

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

#endif  // TOURISM_TSP_H
