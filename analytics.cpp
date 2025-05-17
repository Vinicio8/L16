#include "analytics.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <barkeep/barkeep.h>

std::vector<Transaction> readTransactions(const std::string& filename, barkeep::ProgressBar& pb) {
    std::vector<Transaction> transactions;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line);
    
    size_t lineCount = 0;
    while (std::getline(file, line)) lineCount++;
    file.clear();
    file.seekg(0);
    std::getline(file, line);
    
    pb.setMax(lineCount);
    pb.start();
    
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        Transaction t;
        std::string field;
        
        std::getline(ss, t.invoiceNo, ',');
        std::getline(ss, t.stockCode, ',');
        std::getline(ss, t.description, ',');
        
        std::getline(ss, field, ',');
        t.quantity = field.empty() ? 0 : std::stoi(field);
        
        std::getline(ss, field, ',');
        t.unitPrice = field.empty() ? 0.0 : std::stod(field);
        
        std::getline(ss, t.customerID, ',');
        std::getline(ss, t.country);
        
        transactions.push_back(t);
        pb.tick();
    }
    
    pb.finish();
    return transactions;
}

std::map<std::string, int> analyzeByCountry(
    const std::vector<Transaction>& transactions,
    const std::string& countryFilter) {
    
    std::map<std::string, int> countryCounts;
    
    for (const auto& t : transactions) {
        if (countryFilter.empty() || t.country == countryFilter) {
            countryCounts[t.country]++;
        }
    }
    
    return countryCounts;
}

double calculateTotalAmount(
    const std::vector<Transaction>& transactions,
    bool ukOnly) {
    
    double total = 0.0;
    
    for (const auto& t : transactions) {
        if (!ukOnly || t.country == "United Kingdom") {
            total += t.quantity * t.unitPrice;
        }
    }
    
    return total;
}
