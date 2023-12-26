/**
 * @file shipping_tsp.h
 * @brief Code for solving the Traveling Salesman Problem (TSP) for shipping routes using the Triangular Approximation Algorithm for the shipping toy graph - 4.2.
 */
#ifndef SHIPPING_TSP_H
#define SHIPPING_TSP_H

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
int findNearestNeighborShipping(int currentNode, const std::vector<bool>& visited, const std::vector<std::vector<double>>& distances) {
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
 * @brief Perform the Triangular Approximation Heuristic for shipping routes.
 * The time complexity of this function is O(n^2), where n is the number of nodes.
 * @param edges The vector of shipping route data.
 * @param numNodes The number of nodes in the graph.
 * @return A vector representing the tour.
 * 
 */
std::vector<int> triangularApproximationShipping(const std::vector<ShippingData>& edges, int numNodes) {
    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));

    for (const ShippingData& edge : edges) {
        distances[edge.origin][edge.destination] = edge.distance;
        distances[edge.destination][edge.origin] = edge.distance;
    }

    std::vector<bool> visited(numNodes, false);
    std::vector<int> tour;
    tour.reserve(numNodes);

    int currentNode = 0;
    visited[currentNode] = true;
    tour.push_back(currentNode);

    while (tour.size() < numNodes) {
        int nearestNeighbor = findNearestNeighborShipping(currentNode, visited, distances);
        currentNode = nearestNeighbor;
        visited[currentNode] = true;
        tour.push_back(currentNode);
    }

    tour.push_back(0);

    return tour;
}

/**
 * @brief Solve TSP for shipping routes using the Triangular Approximation Heuristic.
 * The time complexity of this function depends on the number of nodes and edges in the input graph.
 *
 * @param filename The name of the CSV file containing the shipping route data.
 *
 */
void solveTSPShipping(const std::string& filename) {
    std::vector<ShippingData> shippingData = loadShippingGraph(filename);

    int numNodes = 0;
    for (const ShippingData& data : shippingData) {
        numNodes = std::max(numNodes, std::max(data.origin, data.destination) + 1);
    }

    std::vector<int> tour = triangularApproximationShipping(shippingData, numNodes);

    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));
    for (const ShippingData& data : shippingData) {
        distances[data.origin][data.destination] = data.distance;
        distances[data.destination][data.origin] = data.distance;
    }

    std::cout << "Tour: ";
    for (int i = 0; i < numNodes; ++i) {
        std::cout << tour[i] << " ";
    }
    std::cout << std::endl;

    double totalDistance = 0.0;
    for (int i = 0; i < numNodes; ++i) {
        totalDistance += distances[tour[i]][tour[(i + 1) % numNodes]];
    }

    std::cout << "Total Distance: " << totalDistance << " Units" << std::endl;
}

#endif  // SHIPPING_TSP_H
