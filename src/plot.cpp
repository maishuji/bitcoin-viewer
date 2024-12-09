#include "plot.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void BitcoinPlot::loadData(const std::string &file, std::vector<double> &dates, std::vector<double> &prices) {
    std::ifstream infile(file);

    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file: " + file);
    }

    std::string line;
    
    //first line is headers
    std::getline(infile,line);

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string date_str, price_str;

        if (std::getline(iss, date_str, ',') && std::getline(iss, price_str, ',')) {
            dates.push_back(std::stod(date_str));  // Convert date (timestamp) to double
            prices.push_back(std::stod(price_str)); // Convert price to double
        }
    }
}

void BitcoinPlot::plot(const std::vector<double> &dates, const std::vector<double> &prices) {
    if (dates.empty() || prices.empty()) {
        throw std::runtime_error("No data to plot");
    }

    // Plot data
    plt::figure_size(1200, 600);
    plt::plot(dates, prices, "b-");
    plt::xlabel("Date (timestamp)");
    plt::ylabel("Bitcoin Price (USD)");
    plt::title("Bitcoin Price Evolution");
    plt::show();
}
