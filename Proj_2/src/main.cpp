#include <iostream>
#include "backtracking.h"
#include "csv.h"
#include "stadiums_tsp.h"
#include "shipping_tsp.h"
#include "real_world_tsp.h"
#include "tourism_tsp.h"
#include "extraMedium_tsp.h"
#include "heuristicST.h"
#include "heuristicT.h"
#include "heuristic.h"

int main() {
    int choice,choice1,k;

    std::cout << "1.TSP Solver using backtracking" << std::endl;
    std::cout << "2.TSP Solver using Triangular Approximation" << std::endl;
    std::cout << "3.TSP Solver using Our Heuristic Approach" << std::endl;
    std::cout << "Enter your choice (1-3): ";
    std::cin >> choice1;
    
    std::cout << "Select which graph to use:";
    std::cout << "1. Toy Graph 1 - Tourism" << std::endl;
    std::cout << "2. Toy Graph 2 - Shipping" << std::endl;
    std::cout << "3. Toy Graph 3 - Stadium" << std::endl;
    if (choice1== 2){
    std::cout << "4. Real-World Graph 1" << std::endl;
    std::cout << "5. Real-World Graph 2" << std::endl;
    std::cout << "6. Real-World Graph 3" << std::endl;
    std::cout << "7. Extra Medium-Size Graph (25 nodes)" << std::endl;
    std::cout << "8. Extra Medium-Size Graph (50 nodes)" << std::endl;
    std::cout << "9. Extra Medium-Size Graph (100 nodes)" << std::endl;
    std::cout << "Enter your choice (1-9): ";
    }

    if(choice1==3 || choice1==1) std::cout << "Enter your choice (1-3): ";
    std::cin >> choice;
    if(choice1==3){ std::cout << "Enter k for k-clusters: ";
    std::cin >> k;
    }
    

    std::string filename, filename2;
    switch (choice) {
        case 1:
            filename = "Dataset/Toy-Graphs/tourism.csv";
            if(choice1==2) solveTSPTourism(filename);
            else if (choice1==3) solveHTourism(filename,k);
            break;
        case 2:
            filename = "Dataset/Toy-Graphs/shipping.csv";
            if(choice1==2) solveTSPShipping(filename);
            else if (choice1==3) solveHShipping(filename,k);
            break;
        case 3:
            filename = "Dataset/Toy-Graphs/stadiums.csv";
            if(choice1==2) solveTSPStadiums(filename);
            else if (choice1==3) solveHStadiums(filename,k);
            break;
        case 4:
           filename = "Dataset/Real-Word_Graphs/graph1/edges.csv";
           filename2 = "Dataset/Real-Word_Graphs/graph1/nodes.csv";
           if(choice1==2) solveTSPreal(filename,filename2);
            break;
        case 5:
            filename = "Dataset/Real-Word_Graphs/graph2/edges.csv";
            filename2 = "Dataset/Real-Word_Graphs/graph2/nodes.csv";
            if(choice1==2) solveTSPreal(filename,filename2);
            break;
        case 6:
            filename = "Dataset/Real-Word_Graphs/graph3/edges.csv";
            filename2 = "Dataset/Real-Word_Graphs/graph3/nodes.csv";
            if(choice1==2) solveTSPreal(filename,filename2);
            break;
        case 7:
            filename = "Dataset/Extra_Fully_Connected_Graphs/edges_25.csv";
            if(choice1==2) solveTSPExtra(filename);
            break;
        case 8:
            filename = "Dataset/Extra_Fully_Connected_Graphs/edges_50.csv";
            if(choice1==2) solveTSPExtra(filename);
            break;
        case 9:
            filename = "Dataset/Extra_Fully_Connected_Graphs/edges_100.csv";
            if(choice1==2) solveTSPExtra(filename);
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            return 0;
    }

   
    if(choice1==1){
         loadGraph(filename);
         solveTSP();
    }
    

    return 0;
}
