#include <bits/stdc++.h>
#include "FX.hpp"

class Test {

 public:
    void solve() {
        readInput();
        printOutput();
    }

 private:
    std::string fromCurrency, toCurrency;
    double timestamp, price;
    int numberOfExchanges;
    FX *fx = new FX();

    void readInput() {
        std::ifstream fin("file.in");
        fin >> numberOfExchanges;
        for (int i = 0; i < numberOfExchanges; i++) {
            fin >> fromCurrency >> toCurrency >> price >> timestamp;
            fx->addForeignExchangeValue(fromCurrency, toCurrency, price, timestamp);
        }
        fin.close();
    }

    void printOutput() {
        fx->displayTopMostRecentPricesForCurrencyPair("USD", "EUR", 3);
    }
};


int main() {
    Test *test = new Test();
    test->solve();
    delete test;
    return 0;
}