/**
 * @file csv.h
 * @brief Includes functions for loading and processing graph data from CSV files, along with relevant data structures.
 */
#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Struct representing data for tourism.
 */
struct TourismData {
    int origin;
    int destination;
    double distance;
    std::string labelOrigin;
    std::string labelDestination;
};

/**
 * @brief Struct representing data for shipping.
 */
struct ShippingData {
    int origin;
    int destination;
    double distance;
};

/**
 * @brief Struct representing data for stadium.
 */
struct StadiumData {
    int origin;
    int destination;
    double distance;
};

/**
 * @brief Struct representing general edge data.
 */
struct EdgeData {
    int origin;
    int destination;
    double distance;
};

/**
 * @brief Struct representing node data.
 */
struct NodeData {
    int id;
    double longitude;
    double latitude;
};

/**
 * @brief Load the graph data for tourism from a CSV file.
 *
 * @param filename The name of the CSV file.
 * @return A vector of TourismData containing the loaded graph data.
 */
std::vector<TourismData> loadTourismGraph(const std::string& filename) {
    std::vector<TourismData> graph;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string str;
        TourismData data;

        std::getline(iss, str, ',');
        data.origin = std::stoi(str);

        std::getline(iss, str, ',');
        data.destination = std::stoi(str);

        std::getline(iss, str, ',');
        data.distance = std::stod(str);

        std::getline(iss, data.labelOrigin, ',');
        std::getline(iss, data.labelDestination);

        graph.push_back(data);
    }

    file.close();
    return graph;
}

/**
 * @brief Load the graph data for shipping from a CSV file.
 *
 * @param filename The name of the CSV file.
 * @return A vector of ShippingData containing the loaded graph data.
 */
std::vector<ShippingData> loadShippingGraph(const std::string& filename) {
    std::vector<ShippingData> graph;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string str;
        ShippingData data;

        std::getline(iss, str, ',');
        data.origin = std::stoi(str);

        std::getline(iss, str, ',');
        data.destination = std::stoi(str);

        std::getline(iss, str);
        data.distance = std::stod(str);

        graph.push_back(data);
    }

    file.close();
    return graph;
}

/**
 * @brief Load the graph data for stadiums from a CSV file.
 *
 * @param filename The name of the CSV file.
 * @return A vector of StadiumData containing the loaded graph data.
 */
std::vector<StadiumData> loadStadiumsGraph(const std::string& filename) {
    std::vector<StadiumData> graph;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string str;
        StadiumData data;

        std::getline(iss, str, ',');
        data.origin = std::stoi(str);

        std::getline(iss, str, ',');
        data.destination = std::stoi(str);

        std::getline(iss, str);
        data.distance = std::stod(str);

        graph.push_back(data);
    }

    file.close();
    return graph;
}

/**
 * @brief Load the edge graph data from a CSV file.
 *
 * @param filename The name of the CSV file.
 * @return A vector of EdgeData containing the loaded graph data.
 */
std::vector<EdgeData> loadEdgeGraph(const std::string& filename) {
    std::vector<EdgeData> graph;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string str;
        EdgeData data;

        std::getline(iss, str, ',');
        data.origin = std::stoi(str);

        std::getline(iss, str, ',');
        data.destination = std::stoi(str);

        std::getline(iss, str);
        data.distance = std::stod(str);

        graph.push_back(data);
    }

    file.close();
    return graph;
}

/**
 * @brief Load the node graph data from a CSV file.
 *
 * @param filename The name of the CSV file.
 * @return A vector of NodeData containing the loaded graph data.
 */
std::vector<NodeData> loadNodesGraph(const std::string& filename) {
    std::vector<NodeData> graph;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string str;
        NodeData data;

        std::getline(iss, str, ',');
        data.id = std::stoi(str);

        std::getline(iss, str, ',');
        data.longitude = std::stod(str);

        std::getline(iss, str);
        data.latitude = std::stod(str);

        graph.push_back(data);
    }

    file.close();
    return graph;
}

/**
 * @brief Load the extra medium graph data from a CSV file.
 *
 * @param filename The name of the CSV file.
 * @return A vector of EdgeData containing the loaded graph data.
 */
std::vector<EdgeData> loadExtraMediumGraph(const std::string& filename) {
    std::vector<EdgeData> graph;
    std::ifstream file(filename);
    std::string line;

    std::string nodeCountStr = filename.substr(filename.find("_") + 1);
    int numNodes = std::stoi(nodeCountStr);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string str;
        EdgeData data;

        std::getline(iss, str, ',');
        data.origin = std::stoi(str);

        std::getline(iss, str, ',');
        data.destination = std::stoi(str);

        std::getline(iss, str);
        data.distance = std::stod(str);

        graph.push_back(data);
    }

    file.close();
    return graph;
}


#endif  // CSV_H