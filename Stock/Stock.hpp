#ifndef STOCK_H
#define STOCK_H
#define DELIMITER "-----------------------------------------------------------------"

class Security {
 public:

    int securityID;
    std::string industry;
    std::string description;
    std::vector<std::string> listOfBoardMembers;
    std::vector<std::pair<double, double>> historyStockPrices;
    double lowestPrice;
    double highestPrice;

    Security() {}

    Security(int securityID, std::string industry, std::string description,
    std::vector<std::string> listOfBoardMembers);

    Security(const Security& other);

    Security& operator=(const Security& other);

    ~Security() {}

    void addTick(double price, double timestamp);

    double allTimeLow();

    double allTimeHigh();

    std::vector<std::pair<double, double>> getAllPriceHistory(double startTime, double endTime);

 private:
    int getGreaterOrEqualElement(double startTime);
};

class Stock {
 public:
    /*
    *
    * allSecurities = hashtable
    * key: securityID
    * value: a Security Object with its details: industry, description, listOfBoardMembers, history,
    *       lowest, highest stock prices.
    *
    */
    
    std::unordered_map<int, Security> allSecurities;

    void addBasicSecurityInfo(int securityID, std::string industry, std::string description,
    std::vector<std::string> listOfBoardMembers);

    void addTick(int securityID, double price, double timestamp);

    double allTimeLow(int securityID);

    double allTimeHigh(int securityID);

    void getAllPriceHistory(int securityID, double startTime, double endTime);
};


#endif