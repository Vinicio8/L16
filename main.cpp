#include <iostream>
#include <CLI11/CLI11.hpp>
#include <barkeep/barkeep.h>
#include "analytics.hpp"

int main(int argc, char** argv) {
    CLI::App app{"Online Retail Data Analyzer"};
    
    std::string filename = "OnlineRetail.csv";
    std::string country;
    bool ukOnly = false;
    
    app.add_option("-f,--file", filename, "Input CSV file");
    app.add_option("-c,--country", country, "Filter by country");
    app.add_flag("--uk", ukOnly, "Analyze UK transactions only");
    
    CLI11_PARSE(app, argc, argv);
    
    try {
        barkeep::ProgressBar pb("Processing");
        auto transactions = readTransactions(filename, pb);
        
        auto countryCounts = analyzeByCountry(transactions, country);
        
        if (!country.empty()) {
            std::cout << "Transactions for " << country << ": " 
                      << countryCounts[country] << std::endl;
        } else {
            std::cout << "Transactions by country:\n";
            for (const auto& [country, count] : countryCounts) {
                std::cout << country << ": " << count << std::endl;
            }
        }
        
        double total = calculateTotalAmount(transactions, ukOnly);
        std::cout << "Total amount for " << (ukOnly ? "UK" : "all countries") 
                  << ": " << total << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
