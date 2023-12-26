    /**
     * @file heuristic.h
     * @brief Code for solving the Traveling Salesman Problem (TSP) using hierarchical clustering, divide and conquer, and nearest neighbor 2-approximation for the stadiums toy graph - 4.3
     * 
     */

    #ifndef HEURISTIC_H
    #define HEURISTIC_H

    #include <iostream>
    #include <vector>
    #include <limits>
    #include <cmath>
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
    int findNearestNeighborH(int currentNode, const std::vector<bool>& visited, const std::vector<std::vector<double>>& distances) {
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
     * @brief Perform the nearest neighbor 2-approximation algorithm to find a sub-tour for a given cluster.
     *
     * This function performs the nearest neighbor 2-approximation algorithm to find a sub-tour for a given cluster.
     * It starts from the first node in the cluster and iteratively finds the nearest unvisited neighbor, adding it to the tour.
     * The time complexity is O(n), where n is the number of nodes in the cluster.
     *
     * @param cluster The vector of indices representing the nodes in the cluster.
     * @param distances A 2D vector representing the distances between nodes.
     * @return A vector representing the sub-tour for the cluster.
     *
     */
    std::vector<int> nearestNeighborApproximation(const std::vector<int>& cluster, const std::vector<std::vector<double>>& distances) {
        int numNodes = cluster.size();
        std::vector<bool> visited(numNodes, false);
        std::vector<int> tour;

        int current = cluster[0]; // Start from the first node in the cluster
        visited[current] = true;
        tour.push_back(current);

        for (int i = 0; i < numNodes - 1; ++i) {
            int next = findNearestNeighborH(current, visited, distances);
            visited[next] = true;
            tour.push_back(next);
            current = next;
        }

        return tour;
    }

    /**
     * @brief Perform the hierarchical clustering algorithm to divide the points into clusters.
     *
     * This function performs the hierarchical clustering algorithm to divide the points into the specified number of clusters.
     * It returns a vector of clusters, where each cluster is represented by a vector of point indices.
     * The time complexity is O(n^2 * log(n)), where n is the number of nodes.
     *
     * @param data The vector of data points.
     * @param numClusters The number of clusters to create.
     * @return A vector of clusters, where each cluster is represented by a vector of point indices.
     *
     */
  
    std::vector<std::vector<int>> performHierarchicalClustering(const std::vector<ShippingData>& data, int numClusters) {
        int numPoints = data.size();
        
        // Initialize each data point as a separate cluster
        std::vector<std::vector<int>> clusters;
        for (int i = 0; i < numPoints; ++i) {
            clusters.push_back(std::vector<int>{i});
        }
        
        // Merge clusters until the desired number of clusters is reached
        while (clusters.size() > numClusters) {
            double minDistance = std::numeric_limits<double>::max();
            int cluster1Index = -1;
            int cluster2Index = -1;
            
            // Find the closest pair of clusters
            for (int i = 0; i < clusters.size(); ++i) {
                for (int j = i + 1; j < clusters.size(); ++j) {
                    double distance = data[clusters[i][0]].distance;
                    if (distance < minDistance) {
                        minDistance = distance;
                        cluster1Index = i;
                        cluster2Index = j;
                    }
                }
            }
            
            // Merge the closest pair of clusters
            clusters[cluster1Index].insert(clusters[cluster1Index].end(), clusters[cluster2Index].begin(), clusters[cluster2Index].end());
            clusters.erase(clusters.begin() + cluster2Index);
        }
        
        return clusters;
    }

    /**
     * @brief Perform the divide and conquer algorithm to find the best tour for each cluster.
     *
     * This function performs the divide and conquer algorithm to find the best tour for each cluster.
     * It returns a vector representing the tour, where each element is the index of a node in the tour.
     * The time complexity is O(n^2), where n is the total number of nodes in all clusters.
     *
     * @param clusters The vector of clusters, where each cluster is represented by a vector of point indices.
     * @param distances A 2D vector representing the distances between nodes.
     * @return A vector representing the tour.
     *
     */
    std::vector<int> performDivideAndConquer(const std::vector<std::vector<int>>& clusters, const std::vector<std::vector<double>>& distances) {
        std::vector<int> tour;
        
        for (const std::vector<int>& cluster : clusters) {
            std::vector<int> subTour = nearestNeighborApproximation(cluster, distances);
            tour.insert(tour.end(), subTour.begin(), subTour.end() - 1);  // Exclude duplicate starting point
        }
        
        tour.push_back(tour.front());  // Connect back to the starting point
        
        return tour;
    }

  
    /**
     * @brief Solve the Shipping Traveling Salesman Problem (TSP) using hierarchical clustering, divide and conquer, and nearest neighbor 2-approximation.
     *
     * This function solves the Traveling Salesman Problem (TSP) using hierarchical clustering, divide and conquer,
     * and nearest neighbor 2-approximation. It loads the shipping data from the specified file, performs the necessary steps
     * to find the tour, and calculates the total distance of the tour. It then prints the tour and the total distance.
     * The time complexity is O(n^2), where n is the number of nodes.
     *
     * @param filename The filename of the shipping data file.
     * @param numClusters The number of clusters to create using hierarchical clustering.
     *
     */
    void solveHShipping(const std::string& filename, int numClusters) {
        std::vector<ShippingData> shippingData = loadShippingGraph(filename);
        std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

        int numNodes = shippingData.size();

        // Initialize the distances between nodes
        std::vector<std::vector<double>> distances(numNodes, std::vector<double>(numNodes, 0.0));
        for (const ShippingData& data : shippingData) {
            distances[data.origin][data.destination] = data.distance;
            distances[data.destination][data.origin] = data.distance;
        }

        // Perform hierarchical clustering
        std::vector<std::vector<int>> clusters = performHierarchicalClustering(shippingData, numClusters);

        // Perform divide and conquer for each cluster and get the sub-tour for each cluster
        std::vector<int> tour = performDivideAndConquer(clusters, distances);

        std::cout << "Tour: ";
        for (int i : tour) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        double totalDistance = 0.0;
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            totalDistance += distances[tour[i]][tour[i + 1]];
        }
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
        std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;

        std::cout << "Total Distance: " << totalDistance << " Units" << std::endl;
    }

    #endif  // HEURISTIC_H
