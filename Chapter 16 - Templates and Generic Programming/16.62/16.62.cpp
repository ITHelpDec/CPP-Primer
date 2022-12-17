// Exercise 16.62:
/*
 Define your own version of hash<Sales_data> and define an unordered_multiset of Sales_data objects.
 Put several transactions into the container and print its contents.
*/

#include "Sales_data.hpp"

int main()
{
    Sales_data test1 = { "123-456-789-A", 2, 30 };
    Sales_data test2 = { "123-456-789-B", 2, 40 };
    Sales_data test3 = { "123-456-789-C", 2, 30 };
    
    std::unordered_multiset<Sales_data> sd_mset;
    sd_mset.insert(test1);
    sd_mset.insert(test2);
    sd_mset.insert(test3);
    
    printSet(sd_mset);
    
    std::cout << "sd_mset.bucket_count():     " << sd_mset.bucket_count()     << "\n";
    std::cout << "sd_mset.max_bucket_count(): " << sd_mset.max_bucket_count() << "\n";
    std::cout << "sd_mset.bucket_size():      " << sd_mset.bucket_size(5)     << "\n";
    std::cout << "sd_mset.bucket(test1):      " << sd_mset.bucket(test1)      << "\n";
    std::cout << "sd_mset.bucket(test2):      " << sd_mset.bucket(test2)      << "\n";
    std::cout << "sd_mset.bucket(test3):      " << sd_mset.bucket(test3)      << "\n";
    std::cout << "sd_mset.load_factor():      " << sd_mset.load_factor()      << "\n";
    std::cout << "sd_mset.max_load_factor():  " << sd_mset.max_load_factor()  << std::endl;
    
    return 0;
}
