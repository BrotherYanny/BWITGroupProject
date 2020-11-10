#include <bits/stdc++.h>
#include "Stock.hpp"

// Any constructor
Security::Security(int securityID, std::string industry, std::string description,
        std::vector<std::string> listOfBoardMembers) {

    this->securityID = securityID;
    this->industry = industry;
    this->description = description;
    this->listOfBoardMembers = listOfBoardMembers;
    this->historyStockPrices = {};
    this->lowestPrice = INT_MAX;
    this->highestPrice = INT_MIN;
}

// Copy-constructor
Security::Security(const Security& other) {
    this->securityID = other.securityID;
    this->industry = other.industry;
    this->description = other.description;
    this->listOfBoardMembers = other.listOfBoardMembers;
    this->historyStockPrices = other.historyStockPrices;
    this->lowestPrice = other.lowestPrice;
    this->highestPrice = other.highestPrice;
}

// Copy-assignment
Security& Security::operator=(const Security& other) {
    this->securityID = other.securityID;
    this->industry = other.industry;
    this->description = other.description;
    this->listOfBoardMembers = other.listOfBoardMembers;
    this->historyStockPrices = other.historyStockPrices;
    this->lowestPrice = other.lowestPrice;
    this->highestPrice = other.highestPrice;
    return *this;
}

// adds new stock price, updates lowest and highest
void Security::addTick(double price, double timestamp) {
    if (lowestPrice > price) {
        lowestPrice = price;
    }

    if (highestPrice < price) {
        highestPrice = price;
    }

    historyStockPrices.push_back({timestamp, price});
}

// gets the lowest stock price
double Security::allTimeLow() {
    return lowestPrice;
}

// gets the highest stock price
double Security::allTimeHigh() {
    return highestPrice;
}

// gets the index of the next greater or equal element
int Security::getGreaterOrEqualElement(double startTime) {
    int start = 0; 
    int ans = -1;
    int target = startTime;
    int end = historyStockPrices.size() - 1;

    while (start <= end) { 
        int mid = (start + end) / 2; 
  
        // move to right side if target is greater
        if (historyStockPrices[mid].first < target) {
            start = mid + 1; 
        } else if (historyStockPrices[mid].first > target) { 
            ans = mid; 
            end = mid - 1; 
        } else {
            return mid;
        }
    } 

    return ans; 
}

// gets the stock price history between two timestamps
std::vector<std::pair<double, double>> Security::getAllPriceHistory(double startTime, double endTime) {

    std::sort(historyStockPrices.begin(), historyStockPrices.end());
    int startPosition = getGreaterOrEqualElement(startTime);
    std::vector<std::pair<double, double>> history;

    if (startPosition == -1) {
        return {};
    }

    for (int i = startPosition; i < historyStockPrices.size(); i++) {
        if (historyStockPrices[i].first > endTime) {
            break;
        }
        history.push_back(historyStockPrices[i]);
    }

    return history;
}

// adds to the hashtable a new security with its information
void Stock::addBasicSecurityInfo(int securityID, std::string industry, std::string description,
    std::vector<std::string> listOfBoardMembers) {

        Security newSecurity(securityID, industry, description, listOfBoardMembers);
        allSecurities.insert({securityID, newSecurity});
}

// adds or updates the history of stock prices of a certain security with securityID
void Stock::addTick(int securityID, double price, double timestamp) {

    if (allSecurities.find(securityID) == allSecurities.end()) {
        std::cout << "NU EXISTA SECURITY CU ACEST ID!" << std::endl;
    } else {
        Security &currentSecurity = allSecurities[securityID];
        currentSecurity.addTick(price, timestamp);
    }
}

// gets the lowest stock price for a certain security with securityID
double Stock::allTimeLow(int securityID) {
    
    if (allSecurities.find(securityID) == allSecurities.end()) {
        std::cout << "NU EXISTA SECURITY CU ACEST ID!" << std::endl;
        return -1;
    } else {
        Security &currentSecurity = allSecurities[securityID];
        return currentSecurity.allTimeLow();
    }
}


// gets the highest stock price for a certain security with securityID
double Stock::allTimeHigh(int securityID) {

     if (allSecurities.find(securityID) == allSecurities.end()) {
        std::cout << "NU EXISTA SECURITY CU ACEST ID!" << std::endl;
        return -1;
    } else {
        Security currentSecurity = allSecurities[securityID];
        return currentSecurity.allTimeHigh();
    }
}

// gets the history of stock prices for a certain security with securityID
void Stock::getAllPriceHistory(int securityID, double startTime, double endTime) {

     if (allSecurities.find(securityID) == allSecurities.end()) {
        std::cout << "NU EXISTA SECURITY CU ACEST ID!" << std::endl;
    } else {
        Security currentSecurity = allSecurities[securityID];

        std::string list = "";
        for (auto name : currentSecurity.listOfBoardMembers) {
            list += "\n\t" + name;
        }

        std::vector<std::pair<double, double>> history = currentSecurity.getAllPriceHistory(startTime, endTime);
        std::string message1 = "Security Details:\nID: " + std::to_string(securityID) + " \nINDUSTRY: " +
            currentSecurity.industry + "\nDESCRIPTION: " + currentSecurity.description + "\nBOARD MEMBERS: " + list + "\n";

        std::string message2 = "Stock prices between these timestamps: " + std::to_string(startTime) + " and " + std::to_string(endTime);
        std::cout << std::endl << message1 << std::endl << message2 << ":\n";
        for (auto timePrice : history) {
            std::cout << "TIME: " << timePrice.first << " with STOCK PRICE: " << timePrice.second << std::endl;
        }
    }
}