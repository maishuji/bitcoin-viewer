#ifndef BITCOIN_PLOT_H
#define BITCOIN_PLOT_H

#include <vector>
#include <string>

class BitcoinPlot {
public:
    // Load data from a CSV file
    static void loadData(const std::string &file, std::vector<double> &dates, std::vector<double> &prices);

    // Plot the data using matplotlib
    static void plot(const std::vector<double> &dates, const std::vector<double> &prices);
};

#endif // BITCOIN_PLOT_H