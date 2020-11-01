#include <bits/stdc++.h>
#include "FX.hpp"

bool comp::operator()(const std::pair<std::string, std::pair<double, double>>& firstPair,
     const std::pair<std::string, std::pair<double, double>>& secPair) const{
    // Compare function for the set of pairs in chronological order (the bigger = the more recent).
	if (firstPair.second.first == secPair.second.first)
		return firstPair.second.second > secPair.second.second;

	return firstPair.second.first > secPair.second.first;
}

void FX::addToTopTen(std::string currency, std::pair<double, double> timePrice) {
    topTenCurrencies.insert({currency, timePrice}); // O(log10) = O(1)

    // If the size exceeds 10 after insert, retrieve last value, i.e. oldest price
    // reverse iterator to erase the last value in set carefully (end() = not safe).
    if (topTenCurrencies.size() > 10) {
        std::set<std::pair<std::string, std::pair<double, double>>>::reverse_iterator it = topTenCurrencies.rbegin();
        std::pair<std::string, std::pair<double, double>> currencyTimePrice = *it;
        topTenCurrencies.erase(currencyTimePrice); // O(log10) = O(1)
    }
}

std::string FX::computeCurrencyName(std::string fromCurrency, std::string toCurrency) {
    return fromCurrency + "-" + toCurrency;
}

void FX::BellmanFord(std::string fromCurrency, std::string toCurrency) {
    // Prices (distances) from source to all currencies (nodes).
    std::unordered_map<std::string, double> prices;
    int noCurrencies = currencies.size();

    // Initialiazing the prices with MAX because we search for MIN.
    for (auto currency : currencies) {
        prices.insert({currency, DBL_MAX});
    }

    // Marking the source with 1, bc of multiplication.
    prices[fromCurrency] = 1;
    int flag;

    // Relaxing the edges for "number of currencies" times.
    for (int i = 0; i < noCurrencies; i++) {
        flag = 1;
        for (auto src : currencies) {
            for (auto valKey : graphOfFX[src]) {
                std::string dest = valKey.first;
                double cost = valKey.second;

                if (prices[src] == DBL_MAX) {
                    continue;
                } else {
                    if (prices[dest] > prices[src] * cost) {
                        flag = 0;
                        prices[dest] = prices[src] * cost;
                    }
                }
            }
        }

        // If the edges can't be relaxed anymore, MIN DISTANCE was found.
        if (flag == 1) {
            break;
        } else {
            continue;
        }
    }

    // If the edges can be relaxed after that number of times, there is a cycle.
    for (auto src : currencies) {
        for (auto valKey : graphOfFX[src]) {
            std::string dest = valKey.first;
            double cost = valKey.second;

            if (prices[src] == DBL_MAX) {
                continue;
            } else {
                if (prices[dest] > prices[src] * cost) {
                    std::cout << std::endl << "NEGATIVE CYCLE" << std::endl;
                    return;
                }
            }
        }
    }

    std::string message =  "BEST PRICE for " + fromCurrency + "-" + toCurrency +  " is "; 
    std::cout << std::endl << message << prices[toCurrency] << std::endl;
}

void FX::addToGraph(std::string currency, std::string fromCurrency, std::string toCurrency) {
    auto latestPrice = allPairCurrencies[currency].begin();
    std::pair<double, double> priceTime = *latestPrice;
  
    if (graphOfFX.find(fromCurrency) == graphOfFX.end()) {
        graphOfFX.insert({fromCurrency, std::unordered_map<std::string, double>()});

    }
    // Adding or updating latest price for a pair of currencies
    auto &mapOfSrc = graphOfFX[fromCurrency];
    if (mapOfSrc.find(toCurrency) == mapOfSrc.end()) {
        mapOfSrc.insert({toCurrency, priceTime.second});
    } else {
        mapOfSrc[toCurrency] = priceTime.second;
    }
}

void FX::addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp) {
    // Adding currencies in the set with all currencies.
    currencies.insert(fromCurrency); // O(1)
    currencies.insert(toCurrency); // O(1)
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    // Inserting a new pair of (time, price) in the set for the currency.
    // N = number of prices for a currency
    allPairCurrencies[currency].insert({timestamp, price}); // O(logN)
    std::pair<double, double> timePrice = std::make_pair(timestamp, price);
    addToTopTen(currency, timePrice); // O(1)
    addToGraph(currency, fromCurrency, toCurrency); // O(1)
}

void FX::displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices) {
    std::string currency = computeCurrencyName(fromCurrency, toCurrency);
    std::set<std::pair<double, double>, std::greater<std::pair<double, double>>> setOfPrices = allPairCurrencies[currency];
    int size = setOfPrices.size();

    std::cout << std:: endl << "THESE ARE TOP " << numberOfPrices << " MOST RECENT PRICES FOR " << currency << std::endl;
    std::cout << DELIMITER << std::endl;
    // Printing top most recent number of prices for a certain currency = O(min(numberOfPrices, N)).
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

void FX::displayBestPriceToBuyCurrency(std::string fromCurrency, std::string toCurrency) {
    std::cout << std::endl << "THE GRAPH OF CURRENCIES:" << std::endl;
    for (auto edges : graphOfFX) {
            std::cout << edges.first << " is the SRC and " << std::endl;
            for (auto pairs : edges.second) {
            std::cout << "\t" << pairs.first << " is the DEST at price " << pairs.second << std::endl;
            }
            std::cout << std::endl;
    }
    // Using Bellman-Ford for finding minimum price, this way it will not be a problem if there is a cycle.
    BellmanFord(fromCurrency, toCurrency); // O(E * V) where E-number of pairs, V-number of currencies
}