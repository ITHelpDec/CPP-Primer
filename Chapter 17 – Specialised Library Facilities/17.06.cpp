// Exercise 17.06:
/*
 Rewrite findBook so that it does not use tuple or pair.
 
 >> Lines in comments are previous std::tuple<Args> and std::pair<Size, std::pair<It, It>> definitions
*/

// from exercise 16.62
#include "Sales_data.hpp"

#include <vector>
#include <algorithm>
#include <numeric>

// typedef std::tuple<std::vector<Sales_data>::size_type,
//                    std::vector<Sales_data>::const_iterator,
//                    std::vector<Sales_data>::const_iterator> matches;

// typedef std::pair<std::vector<Sales_data>::size_type,
//                  std::pair<std::vector<Sales_data>::const_iterator,
//                            std::vector<Sales_data>::const_iterator>> matches;

// with the aim of improving intelligibility (could do more, but this is enough for now)
typedef std::vector<Sales_data> SDVec;

struct Matches {
    Matches(const SDVec::size_type &sz, const SDVec::const_iterator &cbegin, const SDVec::const_iterator &cend)
        : number_(sz), cbegin_(cbegin), cend_(cend) { }
    
    SDVec::size_type number_;
    SDVec::const_iterator cbegin_;
    SDVec::const_iterator cend_;
};

bool compareISBN(const Sales_data &lhs, const Sales_data &rhs) { return lhs.isbn() < rhs.isbn(); }

// std::vector<matches>
std::vector<Matches> findBook(const std::vector<SDVec> &files, const std::string &book) {
    // std::vector<matches> ret;
    std::vector<Matches> ret;
    
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto found = std::equal_range(it->cbegin(), it->cend(), book, compareISBN);
        if (found.first != found.second)
            // ret.push_back(std::make_tuple(it - files.cbegin(), found.first, found.second));
            // ret.push_back(std::make_pair(it - files.cbegin(), std::make_pair(found.first, found.second)));
            ret.push_back(Matches(it - files.cbegin(), found.first, found.second));
    }
    
    return ret;
}

void reportResults(std::istream &is, std::ostream &os, const std::vector<SDVec> &files) {
    std::string s;
    std::cout << "Please enter an ISBN number: ";
    while (is >> s) {
        auto trans = findBook(files, s);
        if (trans.empty()) {
            std::cout << s << " not found in any stores." << std::endl;
            continue;
        }
        for (const auto &store : trans) {
            // os << "Store " << std::get<0>(store) << " sales:"
            // os << "Store " << std::get<0>(store) << " sales:"
            os << "Store " << store.number_ << " sales:"
               // << std::accumulate(std::get<1>(store), std::get<2>(store), Sales_data(s))
               // << std::accumulate(store.second.first, store.second.second, Sales_data(s))
               << std::accumulate(store.cbegin_, store.cend_, Sales_data(s)) << std::endl;
        }
    }
}

int main()
{
    std::vector<SDVec> files = {
        { Sales_data("123-456-789-X", 20, 100) },
        { Sales_data("123-456-789-Y", 20, 120) },
        { Sales_data("123-456-789-Z", 20, 180) },
        { Sales_data("123-456-789-X", 20, 200) },
    };
    
    reportResults(std::cin, std::cout, files);
    
    return 0;
}
