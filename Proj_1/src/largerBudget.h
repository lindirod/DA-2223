/**
 * @file largerBudget.h
 * @brief This file contains the definition and implementation of the largerBudget function.
 * 
 * @date 2023
 * 
 */

#ifndef LARGERBUDGET_H
#define LARGERBUDGET_H

#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include "stations.h"
#include "segment.h"
#include "budgets.h"
using namespace std;

/**
 * @brief Function to find the top-k municipalities and districts to assign larger budgets for the purchasing and maintenence of trains, based on the number of train stations in each municipality and district.
 * 
 * @param stations - vector of 'Station' objects representing all train stations in a given region.
 * @param k - number of top municipalities and districts to be returned.
 * @return vector<Budget> - A vector of 'Budget' objects representing the top-k municipalities and districts with the highest number of train stations.
 */

vector<Budget> largerBudget(vector<Station>& stations, int k){
    vector<Budget> municipalityDistrict;

    for(const auto& station : stations){
          bool found = false;
        for(auto& muniDis : municipalityDistrict){
            if(muniDis.municipality == station.municipality && muniDis.district == station.district){
                muniDis.counter++;
                found = true;  //The municipality and district have been found
                break;
            }
        }
        if(!found){
            municipalityDistrict.push_back(Budget{station.municipality, station.district});
        }
       
    }
    sort(municipalityDistrict.begin(), municipalityDistrict.end(), compareMunDis);

    //If the size of the vector is greater than k, resize the vector to contain k elements
    if(municipalityDistrict.size() > k)
        municipalityDistrict.resize(k);
    

    return municipalityDistrict;
}




#endif //LARGERBUDGET_H
