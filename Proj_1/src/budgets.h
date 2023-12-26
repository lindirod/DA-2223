/**
 * @file budgets.h
 * @brief This file contains the declarations of the Budget class. 
 * 
 * @date 2023
 * 
 */

#ifndef MUNICIPALITIES_H
#define MUNICIPALITIES_H

#include <string>

/**
 * Struct that contains the information about a budget.
 */
struct Budget{ 
    /**
     * @param municipality - a string that represents the municipality of a station
     * 
     */
    std::string municipality;

    /**
     * @param district - a string that represents the district of a station
     * 
     */
    std::string district;

    /**
     * @param counter - an integer that represents the counter of stations
     * 
     */
    int counter;
};

/**
 * @brief Boolean function that sorts 'Budget' objects in descending order by municipalities and districts based on the number os stations they have.
 * 
 * @param a 
 * @param b 
 * @return true if the counter of stations of a is greater than the counter of stations of b
 * @return false otherwise
 */
bool compareMunDis(const Budget& a, const Budget& b){
    return a.counter > b.counter;
};


#endif //MUNICIPALITIES_H
