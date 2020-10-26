#ifndef FX_H
#define FX_H

#define DELIMITER "-----------------------------------------------------------"

struct comp {
	bool operator()(const std::pair<std::string, std::pair<double, double>>& firstPair,
            const std::pair<std::string, std::pair<double, double>>& secPair) const;
};

class FX {
 public:
    /*
    * allCurrencies = hashtable: 
    * key:   pair of currencies as string, e.g. "USD-EUR" to avoid hashing a pair
    * value: set of (timestamp, price) to keep track of all changes of price in chronological order
    *
    * topTenCurrencies = set of size 10 to keep most recent currencies in order
    * value: pair of currency and (timestamp, price)
    */
    std::unordered_map<std::string, std::set<std::pair<double, double>, std::greater<std::pair<double, double>>>> allCurrencies;
    std::set<std::pair<std::string, std::pair<double, double>>, comp> topTenCurrencies;

    void addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp);
    void displayTop10RecentPrices();
    void displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices);

 private:
    /*
    * computeCurrencyName = stringifies a pair of two currencies
    * addToTopTen = takes care of keeping the size of topTenCurrencies up to 10
    */
    std::string computeCurrencyName(std::string fromCurrency, std::string toCurrency);
    void addToTopTen(std::string currencyName, std::pair<double, double> timePrice);
};

#endif