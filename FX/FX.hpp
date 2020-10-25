#ifndef FX_H
#define FX_H

class FX {
 public:
    std::unordered_map<std::string, std::set<std::pair<double, double>, std::greater<std::pair<double, double>>>> allCurrencies;
    std::vector<std::pair<double, double>> topTenCurrencies;

    std::string computeCurrencyName(std::string fromCurrency, std::string toCurrency);
    void addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp);
    void displayTop10RecentPrices();
    void displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices);
};

#endif