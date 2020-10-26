#include <bits/stdc++.h>
#include "FX.hpp"

class Test {

 public:
    void solve() {
        // readInput();
        // printOutput();
        readAndDisplayStream();
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
        fx->displayTopMostRecentPricesForCurrencyPair("USD", "EUR", 5);
        fx->displayTop10RecentPrices();
    }

    void addFX() {
        std::string fromCurrency, toCurrency, timeString, priceString;
        double timestamp, price;

	    std::cout << "INSERT fromCurrency = ";
	    std::getline(std::cin, fromCurrency);

        std::cout <<"INSERT toCurrency = ";
        std::getline(std::cin, toCurrency);

        std::cout <<"INSERT price = ";
        std::getline(std::cin, priceString);

        std::cout <<"INSERT timestamp = ";
        std::getline(std::cin, timeString);

        timestamp = std::stod(timeString);
        price = std::stod(priceString);
	    fx->addForeignExchangeValue(fromCurrency, toCurrency, price, timestamp);
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void displayTopMostRecent() {
        std::string fromCurrency, toCurrency, numberString;
        int numberOfPrices;
	    std::cout << "INSERT fromCurrency = ";
	    std::getline(std::cin, fromCurrency);

        std::cout << "INSERT toCurrency = ";
        std::getline(std::cin, toCurrency);

        std::cout << "INSERT number = ";
        std::getline(std::cin, numberString);

        numberOfPrices = std::stod(numberString);

        fx->displayTopMostRecentPricesForCurrencyPair(fromCurrency, toCurrency, numberOfPrices);
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void displayTopTen() {
        fx->displayTop10RecentPrices();
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void wrongCommand() {
        std::cout << std::endl << "WRONG COMMAND!" << std::endl << DELIMITER << std::endl;
    }

    // reads commands from stdin in real time
    void readAndDisplayStream() {
        bool notExit = 1;
        while (notExit) {
            std::string command;
            std::cout << "COMMAND: ";
		    std::getline(std::cin, command);
            if (command == "exit") {
				break;

		    } else if (command == "addFX") {
                addFX();

            } else if (command == "displayTopMostRecent") {
                displayTopMostRecent();

            } else if (command == "displayTopTen") {
                displayTopTen();

            } else {
                wrongCommand();
            }
        }
    }
};


int main() {
    Test *test = new Test();
    test->solve();
    delete test;
    return 0;
}