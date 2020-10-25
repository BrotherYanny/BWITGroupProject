#include <bits/stdc++.h>
#include "FX.hpp"


bool comp::operator()(const std::pair<std::string, std::pair<double, double>>& firstPair,
     const std::pair<std::string, std::pair<double, double>>& secPair) const{
		if (firstPair.second.first == secPair.second.first)
			return firstPair.second.second > secPair.second.second;

		return firstPair.second.first > secPair.second.first;
}

void FX::addToTopTen(std::string currency, std::pair<double, double> timePrice) {
    if (topTenCurrencies.size() < 10) {
        topTenCurrencies.insert({currency, timePrice});
    } else {
        std::set<std::pair<std::string, std::pair<double, double>>>::reverse_iterator it = topTenCurrencies.rbegin();
        std::pair<std::string, std::pair<double, double>> currencyTimePrice = *it;
        double time = currencyTimePrice.second.first;
        if (time < timePrice.first) {
            topTenCurrencies.erase(currencyTimePrice);
            topTenCurrencies.insert({currency, timePrice});
        }
    }
}

std::string FX::computeCurrencyName(std::string fromCurrency, std::string toCurrency) {
    return fromCurrency + "-" + toCurrency;
}

void FX::addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    allCurrencies[currency].insert({timestamp, price});
    std::pair<double, double> timePrice = std::make_pair(timestamp, price);
    addToTopTen(currency, timePrice);
}

void FX::displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    std::set<std::pair<double, double>, std::greater<std::pair<double, double>>> setOfPrices = allCurrencies[currency];
    int size = setOfPrices.size();

    std::cout << std:: endl << "THESE ARE TOP " << numberOfPrices << " MOST RECENT PRICES FOR " << currency << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (auto timePrice : setOfPrices) {
        if (numberOfPrices--) {
             std::cout << "timestamp: " << timePrice.first << ", and price: " << timePrice.second << std::endl;
        } else {
            break;
        }
    }
}

void FX::displayTop10RecentPrices() {
    std::cout << std:: endl << "THESE ARE TOP 1O RECENT PRICES " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (auto pair : topTenCurrencies) {
        std::cout << pair.first << " at timestamp: " << pair.second.first << ", and PRICE: " << pair.second.second << std::endl;
    }
}