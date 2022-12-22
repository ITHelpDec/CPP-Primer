// Exercise 17.04:
/*
 Write and test your own version of the findBook function.
*/

// from exercise 16.61
#include "Sales_data.hpp"

#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

typedef std::tuple<std::vector<Sales_data>::size_type,
                   std::vector<Sales_data>::const_iterator,
                   std::vector<Sales_data>::const_iterator> matches;

bool compareISBN(const Sales_data &lhs, const Sales_data &rhs)
    { return lhs.isbn() < rhs.isbn(); }

std::vector<matches>
findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book) {
    std::vector<matches> ret;
    
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto found = std::equal_range(it->cbegin(), it->cend(), book, compareISBN);
        if (found.first != found.second)
            ret.push_back(std::make_tuple(it - files.cbegin(), found.first, found.second));
    }
    
    return ret;
}

void reportResults(std::istream &is, std::ostream &os, const std::vector<std::vector<Sales_data>> &files) {
    std::string s;
    std::cout << "Please enter an ISBN number: ";
    while (is >> s) {
        auto trans = findBook(files, s);
        if (trans.empty()) {
            std::cout << s << " not found in any stores." << std::endl;
            continue;
        }
        for (const auto &store : trans) {
            os << "Store " << std::get<0>(store) << " sales:"
               << std::accumulate(std::get<1>(store), std::get<2>(store), Sales_data(s))
               << std::endl;
        }
    }
}

int main()
{
    std::vector<std::vector<Sales_data>> files = {
        { Sales_data("123-456-789-X", 20, 100) },
        { Sales_data("123-456-789-Y", 20, 120) },
        { Sales_data("123-456-789-Z", 20, 180) },
        { Sales_data("123-456-789-X", 20, 200) },
    };
    
    reportResults(std::cin, std::cout, files);
    
    return 0;
}
