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
    * allPairCurrencies = hashtable: 
    * key:   pair of currencies as string, e.g. "USD-EUR" to avoid hashing a pair
    * value: set of (timestamp, price) to keep track of all changes of price in chronological order
    *
    * topTenCurrencies = set of size 10 to keep most recent currencies in order
    * value: pair of currency and (timestamp, price)
    *
    * graphOfFX = hashtable:
    * key: source (fromCurrency)
    * value: hashtable for adjacency lists: (key: destination (toCurrency), value: price)
    *
    * currencies = set with all currencies to keep track of all the nodes
    */
    std::unordered_map<std::string, std::set<std::pair<double, double>, std::greater<std::pair<double, double>>>> allPairCurrencies;
    std::set<std::pair<std::string, std::pair<double, double>>, comp> topTenCurrencies;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> graphOfFX;
    std::unordered_set<std::string> currencies;

    void addForeignExchangeValue(std::string fromCurrency, std::string toCurrency, double price, double timestamp);
    void displayTop10RecentPrices();
    void displayTopMostRecentPricesForCurrencyPair(std::string fromCurrency, std::string toCurrency, int numberOfPrices);
    void displayBestPriceToBuyCurrency(std::string fromCurrency, std::string toCurrency);

 private:
    /*
    * computeCurrencyName = stringifies a pair of two currencies
    *
    * addToTopTen = takes care of keeping the size of topTenCurrencies up to 10
    *
    * addToGraph = adds a new edge or updates in the graph of currencies
    *
    * BellmanFord = runs Bellman-Ford algorithm for finding cheapest transaction
    */
    std::string computeCurrencyName(std::string fromCurrency, std::string toCurrency);
    void addToTopTen(std::string currencyName, std::pair<double, double> timePrice);
    void addToGraph(std::string currency, std::string fromCurrency, std::string toCurrency);
    void BellmanFord(std::string fromCurrency, std::string toCurrency);
};

#endif