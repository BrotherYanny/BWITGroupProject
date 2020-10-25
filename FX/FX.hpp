#ifndef FX_H
#define FX_H

struct comp {
	bool operator()(const std::pair<std::string, std::pair<double, double>>& firstPair,
            const std::pair<std::string, std::pair<double, double>>& secPair) const;
};

class FX {
 public:
    std::unordered_map<std::string, std::set<std::pair<double, double>, std::greater<std::pair<double, double>>>> allCurrencies;
    std::set<std::pair<std::string, std::pair<double, double>>, comp> topTenCurrencies;

    void addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp);
    void displayTop10RecentPrices();
    void displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices);

 private:
    std::string computeCurrencyName(std::string fromCurrency, std::string toCurrency);
    void addToTopTen(std::string currencyName, std::pair<double, double> timePrice);
};

#endif