#include <bits/stdc++.h>
#include "FX.hpp"

#define DELIMITER "------------------------------------------------"

bool comp::operator()(const std::pair<std::string, std::pair<double, double>>& firstPair,
     const std::pair<std::string, std::pair<double, double>>& secPair) const{
    // compare function for the set of pairs in chronological order
	if (firstPair.second.first == secPair.second.first)
		return firstPair.second.second > secPair.second.second;

	return firstPair.second.first > secPair.second.first;
}

void FX::addToTopTen(std::string currency, std::pair<double, double> timePrice) {
    topTenCurrencies.insert({currency, timePrice}); // O(log10) = O(1)

    // if the size exceeds 10 after insert, retrieve last value, i.e. oldest price
    // reverse iterator to erase the last value in set carefully (end() = not safe)
    if (topTenCurrencies.size() > 10) {
        std::set<std::pair<std::string, std::pair<double, double>>>::reverse_iterator it = topTenCurrencies.rbegin();
        std::pair<std::string, std::pair<double, double>> currencyTimePrice = *it;
        topTenCurrencies.erase(currencyTimePrice); // O(log10) = O(1)
    }
}

std::string FX::computeCurrencyName(std::string fromCurrency, std::string toCurrency) {
    return fromCurrency + "-" + toCurrency;
}

void FX::addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    // inserting a new pair of (time, price) in the set for the currency
    // N = number of prices for a currency
    allCurrencies[currency].insert({timestamp, price}); // O(logN)
    std::pair<double, double> timePrice = std::make_pair(timestamp, price);
    addToTopTen(currency, timePrice); // O(1)
}

void FX::displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    std::set<std::pair<double, double>, std::greater<std::pair<double, double>>> setOfPrices = allCurrencies[currency];
    int size = setOfPrices.size();

    std::cout << std:: endl << "THESE ARE TOP " << numberOfPrices << " MOST RECENT PRICES FOR " << currency << std::endl;
    std::cout << DELIMITER << std::endl;
    // printing top most recent number of prices for a certain currency = O(min(numberOfPrices, N))
    for (auto timePrice : setOfPrices) {
        if (numberOfPrices--) {
            std::string time = std::to_string(timePrice.first);
            std::string price = std::to_string(timePrice.second);
            std::string message = "timestamp: " + time + ", and price: " + price;
            std::cout << message << std::endl;
        } else {
            break;
        }
    }
}

void FX::displayTop10RecentPrices() {
    std::cout << std:: endl << "THESE ARE TOP 1O RECENT PRICES " << std::endl;
    std::cout << DELIMITER << std::endl;

    for (auto nameTimePrice : topTenCurrencies) {
        std::string currency = nameTimePrice.first;
        std::string time = std::to_string(nameTimePrice.second.first);
        std::string price = std::to_string(nameTimePrice.second.second);
        std::string message = currency + " at timestamp: " + time + ", and PRICE: " + price;
        std::cout << message << std::endl;
    }
}