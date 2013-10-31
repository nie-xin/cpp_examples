#include <iostream>
#include <string>

// exchange rate
const double JPY_to_USD = 0.0102;
const double EUR_to_USD = 1.3585;
const double GBP_to_USD = 1.6046;

double exchange(std::string currency, double quantity) {
    if (currency == "JPY") {
        return quantity*JPY_to_USD;
    } else if (currency == "EUR") {
        return quantity*EUR_to_USD;
    } else if (currency == "GBP") {
        return quantity*GBP_to_USD;
    } else {
        std::cout << "Error input" << std::endl;
        return -1;
    }

}

int main(void) {
    std::string currency = "";
    double quantity = 0.0;

    std::cout << "Please enter the currency followed by the quantity that you want to exchange to USD: ";
    std::cin >> currency >> quantity;
    double exchanged = exchange(currency, quantity);

    if (exchanged < 0) {
        return -1;
    } else {
        std::cout << currency << "*" << quantity << " to " << exchanged <<"USD" << std::endl;
    }

    return 0;
}