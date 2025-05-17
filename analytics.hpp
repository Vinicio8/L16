#ifndef ANALYTICS_HPP
#define ANALYTICS_HPP

#include <string>
#include <vector>
#include <map>

struct Transaction {
    std::string invoiceNo;
    std::string stockCode;
    std::string description;
    int quantity;
    double unitPrice;
    std::string customerID;
    std::string country;
};

std::vector<Transaction> readTransactions(const std::string& filename);
std::map<std::string, int> analyzeByCountry(
    const std::vector<Transaction>& transactions,
    const std::string& countryFilter = "");
double calculateTotalAmount(
    const std::vector<Transaction>& transactions,
    bool ukOnly = false);

#endif
