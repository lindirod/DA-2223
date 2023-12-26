/**
 * @file stadiums_tsp.h
 * @brief Code for solving the Traveling Salesman Problem (TSP) using Triangular Approximation Algorithm for the stadiums toy graph - 4.2 
 * 
 */
#ifndef STADIUMS_TSP_H
#define STADIUMS_TSP_H

#include <iostream>
#include <vector>
#include <limits>
#include "csv.h"

/**
 * @brief Find the nearest neighbor node not visited yet.
 *
 * This function finds the nearest neighbor node to the current node that has not been visited yet,
 * based on the distances between nodes and the visited status. 
 * The time complexity is O(n), where n is the number of nodes.
 *
 * @param currentNode The index of the current node.
 * @param visited A vector indicating whether each node has been visited or not.
 * @param distances A 2D vector representing the distances between nodes.
 * @return The index of the nearest neighbor node that has not been visited yet.
 * 
 */
int findNearestNeighborStadiums(int currentNode, const std::vector<bool>& visited, const std::vector<std::vector<double>>& distances) {
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
 * @brief Perform the Triangular Approximation Heuristic for the "stadiums.csv" file.
 *
 * This function performs the Triangular Approximation Heuristic to find the tour for the given edges and number of nodes.
 * It returns a vector representing the tour, where each element is the index of a node in the tour.
 * The time complexity is O(n^2), where n is the number of nodes.
 * 
 * @param edges The edges representing the distances between nodes.
 * @param numNodes The total number of nodes in the graph.
 * @return A vector representing the tour.
 * 
 */
std::vector<int> triangularApproximationStadiums(const std::vector<StadiumData>& edges, int numNodes) {
    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));

    for (const StadiumData& edge : edges) {
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
        int nearestNeighbor = findNearestNeighborStadiums(currentNode, visited, distances);
        currentNode = nearestNeighbor;
        visited[currentNode] = true;
        tour.push_back(currentNode);
    }

    tour.push_back(0);

    return tour;
}

/**
 * @brief Solve TSP using the Triangular Approximation Heuristic for the "stadiums.csv" file.
 *
 * This function solves the Traveling Salesman Problem (TSP) using the Triangular Approximation Heuristic.
 * It loads the stadium data from the specified file, performs the Triangular Approximation Heuristic
 * to find the tour, and calculates the total distance of the tour. It then prints the tour and the total distance.
 * The time complexity is O(n^2), where n is the number of nodes.
 * 
 * @param filename The filename of the "stadiums.csv" file.
 *
 */
void solveTSPStadiums(const std::string& filename) {
    std::vector<StadiumData> stadiumData = loadStadiumsGraph(filename);

    int numNodes = 0;
    for (const StadiumData& data : stadiumData) {
        numNodes = std::max(numNodes, std::max(data.origin, data.destination) + 1);
    }

    std::vector<int> tour = triangularApproximationStadiums(stadiumData, numNodes);

    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));
    for (const StadiumData& data : stadiumData) {
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

#endif  // STADIUMS_TSP_H
