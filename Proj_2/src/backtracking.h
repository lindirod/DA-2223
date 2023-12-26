/**
 * @file backtracking.h
 * @brief Code for solving the Traveling Salesman Problem (TSP) using backtracking - 4.1 
 * 
 */

#include <limits>
#include <iostream>
#include <chrono>
#include <vector>
#include "csv.h"

/**
 * @struct Vertex
 * @brief Represents a vertex in a graph, along with its adjacent edges
 * 
 */
struct Vertex {
    int id; ///< ID of the vertex
    std::vector<EdgeData> adj;   ///< List of adjacent edges
};

std::vector<Vertex> vertices;  ///< List of vertices in the graph

/**
 * @brief Reads the Edge Data from the csv.h file and constructs the graph by populating
 * the 'vertices' vector with the corresponding vertices and their adjacent edges
 * 
 * Time complexity: O(E) where E is the number of edges in the graph.
 * The function iterates over the edges twice. The first time is to determine the number of vertices
 * and resize the 'vertices' vector, and the second time to populate the adjacency list of vertices
 * 
 * @param filename The name of the csv file containing the graph
 */
void loadGraph(const std::string& filename) {
    std::vector<EdgeData> graph = loadEdgeGraph(filename);

    int numVertices = 0;
    for (const auto& edge : graph) {
        numVertices = std::max(numVertices, std::max(edge.origin, edge.destination) + 1);
    }

    vertices.resize(numVertices);

    for (const auto& edge : graph) {
        EdgeData reverseEdge = {edge.destination, edge.origin, edge.distance};

        vertices[edge.origin].adj.push_back(edge);
        vertices[edge.destination].adj.push_back(reverseEdge);
    }
}


/**
 * @brief Recursive function that uses backtracking to explore all possible paths in the graph and computes the distance
 * 
 * Time Complexity: O(V!) where V is the number of vertices in the graph.
 * The function explores all possible paths in the graph. They can be represented as permutations of the vertices which corresponds to the time complexity
 * 
 * @param path The current path being explored
 * @param visited A boolean array that indicates whether a vertex is visited or not
 * @param currentDistance The current distance of the path being explored
 * @return The minimum distance found
 */
double tspBacktracking(const std::vector<int>& path, const std::vector<bool>& visited, double currentDistance) {
    if (path.size() == vertices.size()) {
        int startVertex = path.front();
        for (const auto& edge : vertices[path.back()].adj) {
            if (edge.destination == startVertex) {
                double cycleDistance = currentDistance + edge.distance;
                return cycleDistance;
            }
        }
    }

    double minDistance = std::numeric_limits<double>::max();

    for (const auto& edge : vertices[path.back()].adj) {
        if (!visited[edge.destination]) {
            std::vector<int> newPath = path;
            std::vector<bool> newVisited = visited;

            newPath.push_back(edge.destination);
            newVisited[edge.destination] = true;

            double newDistance = tspBacktracking(newPath, newVisited, currentDistance + edge.distance);

            minDistance = std::min(minDistance, newDistance);
        }
    }

    return minDistance;
}

/**
 * @brief Solves the TSP using backtracking.
 * Calls the 'tspBacktracking' function to find the minimum distance and prints the solution as well as the execution time.
 * 
 * Time Complexity: O(V!) where V is the number of edges in the graph.
 * Since this functions calls the 'tspBacktracking' function, it has the same time complexity.
 */
void solveTSP() {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    double minDistance = std::numeric_limits<double>::max();
    std::vector<int> path = {0};
    std::vector<bool> visited(vertices.size(), false);
    visited[0] = true;

    minDistance = tspBacktracking(path, visited, 0.0);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

    std::cout << "TSP Backtracking Solution:" << std::endl;
    std::cout << "Distance: " << minDistance << std::endl;
    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;
    return;
}
