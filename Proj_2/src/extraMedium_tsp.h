/**
 * @file extraMedium_tsp.h
 * @brief Code for solving the Traveling Salesman Problem (TSP) using Triangular Approximation Algorithm for the extra medium-size graphs - 4.2 
 * 
 */
#ifndef EXTRAMEDIUM_TSP_H
#define EXTRAMEDIUM_TSP_H

#include <iostream>
#include <vector>
#include <limits>
#include "csv.h"

/**
 * @brief Find the nearest unvisited neighbor from a given set of distances.
 * This function finds the nearest unvisited neighbor from a given set of distances. It iterates over the distances, looking for the minimum distance that has not been visited yet.
 * The time complexity of this function is O(n), where n is the number of nodes.
 * 
 * @param distances The distances between nodes.
 * @param visited A vector indicating which nodes have been visited.
 * @return The index of the nearest unvisited neighbor.
 *
 */
int findNearestNeighbor(const std::vector<double>& distances, const std::vector<bool>& visited) {
    int numNodes = distances.size();
    int nearestNeighbor = -1;
    double minDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            nearestNeighbor = i;
        }
    }

    return nearestNeighbor;
}

/**
 * @brief Perform triangular approximation to solve the Traveling Salesman Problem (TSP).
 *  This function performs the triangular approximation algorithm to solve
 *          the Traveling Salesman Problem (TSP). It takes a set of edges representing
 *          the distances between nodes and the number of nodes in the graph. It creates
 *          a distance matrix based on the edges, initializes the visited vector, and
 *          starts with an initial node. It then iteratively finds the nearest unvisited
 *          neighbor and adds it to the tour until all nodes are visited. Finally, it
 *          completes the tour by returning to the initial node.
 * The time complexity of this function is O(n^2), where n is the number
 *             of nodes. The nested loop that initializes the distance matrix has a
 *             time complexity of O(n^2), and the main loop that finds the nearest
 *             neighbor runs for n iterations.
 * @param edges The edges representing the distances between nodes.
 * @param numNodes The number of nodes in the graph.
 * @return The tour representing the order of nodes to visit.
 *
 */
std::vector<int> triangularApproximation(const std::vector<EdgeData>& edges, int numNodes) {
    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));

    for (const EdgeData& edge : edges) {
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
        int nearestNeighbor = findNearestNeighbor(distances[currentNode], visited);
        currentNode = nearestNeighbor;
        visited[currentNode] = true;
        tour.push_back(currentNode);
    }

    tour.push_back(0);

    return tour;
}


/**
 * @brief Solve the Traveling Salesman Problem (TSP) using triangular approximation.
 *  This function solves the Traveling Salesman Problem (TSP) using the
 *          triangular approximation algorithm. It loads the edge graph from the
 *          specified CSV file, extracts the number of nodes from the filename,
 *          and applies the triangular approximation algorithm to find the tour.
 *          It then calculates the total distance of the tour and prints the
 *          tour and the total distance.
 * The time complexity of this function depends on the complexity
 *             of the triangularApproximation function, which is O(n^2), where n
 *             is the number of nodes.
 * @param filename The name of the file containing the edge graph data.
 * 
 */
void solveTSPExtra(const std::string& filename) {
     std::vector<EdgeData> graph = loadEdgeGraph(filename);

    // Extract the number of nodes from the file name
    std::size_t startPos = filename.find("_") + 1;
    std::size_t endPos = filename.find(".", startPos);
    std::string numNodesStr = filename.substr(startPos, endPos - startPos);
    int numNodes = std::stoi(numNodesStr);

    std::vector<int> tour = triangularApproximation(graph, numNodes);

    std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));
    for (const EdgeData& data : graph) {
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


#endif  // EXTRAMEDIUM_TSP_H
