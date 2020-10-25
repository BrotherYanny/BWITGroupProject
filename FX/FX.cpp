#include <bits/stdc++.h>
#include "FX.hpp"

std::string FX::computeCurrencyName(std::string fromCurrency, std::string toCurrency) {
    return fromCurrency + " " + toCurrency;
}

void FX::addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    allCurrencies[currency].insert({timestamp, price});
}

void FX::displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    std::set<std::pair<double, double>, std::greater<std::pair<double, double>>> setOfPrices = allCurrencies[currency];
    int size = setOfPrices.size();

    std::cout << std:: endl << "THESE ARE TOP " << numberOfPrices << " MOST RECENT PRICES FOR " << currency << std::endl;
    for (auto pair : setOfPrices) {
        if (numberOfPrices--) {
             std::cout << pair.first << " " << pair.second << std::endl;
        } else {
            break;
        }
    }
}

void FX::displayTop10RecentPrices() {

}