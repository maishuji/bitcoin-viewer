#include "plot.hpp"
#include <iostream>

int main() {
    const std::string data_file = "../data/bitcoin_prices.csv";

    try {
        std::vector<double> dates, prices;
        BitcoinPlot::loadData(data_file, dates, prices);

        BitcoinPlot::plot(dates, prices);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}