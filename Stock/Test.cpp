#include <bits/stdc++.h>
#include "Stock.hpp"

class Test {

 public:
    void solve() {
        readAndDisplayStream();
    }

 private:
    Stock *stock = new Stock();

    void addInfo() {
        std::string industry, description, securityIDString, list, token;
        std::vector<std::string> listOfMembers;
        double timestamp, price;
        int securityID;

	    std::cout << "INSERT securityID = ";
	    std::getline(std::cin, securityIDString);
        securityID = std::stoi(securityIDString);

        std::cout <<"INSERT industry = ";
        std::getline(std::cin, industry);

        std::cout <<"INSERT description = ";
        std::getline(std::cin, description);

        std::cout <<"INSERT (with commas) the board members' list = ";
        std::getline(std::cin, list);
        std::istringstream ss(list);
        
        while (std::getline(ss, token, ',')) {
            listOfMembers.push_back(token);
        }

        stock->addBasicSecurityInfo(securityID, industry, description, listOfMembers);
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void addTick() {
        std::string securityIDString, timeString, priceString;
        double timestamp, price;
        int securityID;

	    std::cout << "INSERT securityID = ";
	    std::getline(std::cin, securityIDString);

        std::cout << "INSERT timestamp = ";
        std::getline(std::cin, timeString);

        std::cout << "INSERT price = ";
        std::getline(std::cin, priceString);

        securityID = std::stoi(securityIDString);
        timestamp = std::stod(timeString);
        price = std::stod(priceString);

        stock->addTick(securityID, price, timestamp);
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void lowest() {
        std::string securityIDString;
        int securityID;

	    std::cout << "INSERT securityID = ";
	    std::getline(std::cin, securityIDString);
        securityID = std::stoi(securityIDString);

        std::cout << stock->allTimeLow(securityID);
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void highest() {
        std::string securityIDString;
        int securityID;

	    std::cout << "INSERT securityID = ";
	    std::getline(std::cin, securityIDString);
        securityID = std::stoi(securityIDString);

        std::cout << stock->allTimeHigh(securityID);
        std::cout << std::endl << DELIMITER << std::endl;
    }

    void history() {
        std::string securityIDString, startTimeString, endTimeString;
        double startTime, endTime;
        int securityID;

        std::cout << "INSERT securityID = ";
	    std::getline(std::cin, securityIDString);
        securityID = std::stoi(securityIDString);

        
        std::cout << "INSERT startTime = ";
	    std::getline(std::cin, startTimeString);
        startTime = std::stod(startTimeString);

        std::cout << "INSERT endTime = ";
	    std::getline(std::cin, endTimeString);
        endTime = std::stod(endTimeString);

        stock->getAllPriceHistory(securityID, startTime, endTime);
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

		    } else if (command == "addInfo") {
                addInfo();

            } else if (command == "addTick") {
                addTick();

            } else if (command == "lowest") {
                lowest();

            } else if (command == "highest") {
                highest();
            
            } else if (command == "history") {
                history();
            
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