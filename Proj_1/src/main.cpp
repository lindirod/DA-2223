#include <iostream>
#include "csv.h"
#include "stations.h"
#include "segment.h"
#include "stationPair.h"
#include "getMaxCapacity.h"
#include "findMostDemandingStations.h"
#include "mostTrainsAt.h"
#include "largerBudget.h"
#include "budgets.h"
#include "getMinCost.h"
#include "maxTrains.h"




int main() {
    std::vector<Station> stations = readStationsFromFile("stations.csv");
    std::vector<Segment> segments = readSegmentsFromFile("network.csv");
    std::vector<Budget> municipalityDistrict;
    int choice = 0,k;
    std::string source, destination;
    int maxFlow = 0, maxTrains,mxTrains;
    bool exit_program = false;

    while (!exit_program) {
        std::cout << "Welcome to the Portuguese Railing Network Management System\n";
        std::cout << "Please choose an option:\n";
        std::cout << "1. Calculate max flow between two stations\n";
        std::cout << "2. Find most demanding station pairs\n";
        std::cout << "3. Top-k municipalities and districts\n";
        std::cout << "4. Calculate most trains that can simultaneously arrive at a station\n";
        std::cout << "5. Calculate minimum cost\n";
        std::cout << "6. Calculate max number of trains in reduced connectivity\n";
        std::cout << "7. Top-k most affected stations for each segment\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
            std::cout << "Enter source station: ";
                std::cin >> source;
                std::cout << "Enter destination station: ";
                std::cin >> destination;
                std::cout << "The max flow between " << source << " and " << destination << " is: " << getMaxCapacity(source, destination, stations, segments) << std::endl;
                break;
            case 2:
             findMostDemandingStations(stations,segments);
                break;
            case 3:
                 std::cout << "Enter a number k: ";
                 std::cin >> k;
                if(k <= 0){   
                    std::cout << "k must be greater than 0\n";
                }else{      
                    municipalityDistrict = largerBudget(stations, k);
                    std::cout << "Top " << k << " Municipalities and Districts\n";
                    for(auto& muniDis : municipalityDistrict) {
                        std::cout << muniDis.municipality << " in " << muniDis.district << endl;
                    }
                break;
            case 4:
                std::cout << "Enter destination station: ";
                std::cin >> destination;
                mostTrainsAt(stations,segments,destination);
                break;
            case 5:
            std::cin.ignore(); // ignore the remaining newline character
                std::cout << "Enter source station: ";
                std::cin >> source;
                std::cout << "Enter destination station: ";
                std::cin >> destination;
                maxTrains = getMinCost(source,destination, stations, segments);
                cout << "Max flow between " << source << " and " << destination << " with minimum cost: " << maxTrains << endl;
                break;
            case 6:
             std::cout << "Enter source station: ";
                std::cin >> source;
                std::cout << "Enter destination station: ";
                std::cin >> destination;
                mxTrains = getMaxTrains(source,destination, stations, segments);
                break;
            case 7:
                std::cout << "Enter k: ";
                std::cin >> k;
                    
                if(k <= 0){   
                    std::cout << "k must be greater than 0\n";
                }else
                findMostAffectedStations( stations, segments, k);
                break;

            case 0:
                std::cout << "Exiting...\n";
                exit_program = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
  return 0;
}
