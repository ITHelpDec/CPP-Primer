// Exercise 9.27
/*
 // Write a program to find and remove the odd-valued elements in a forward_list<int>.
*/

 #include <forward_list>
 #include <iostream>

 int main()
 {
     // initialise forward_list from last exercise
     std::forward_list<int> flist = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
     std::cout << "flist: ";
     for (const auto &e : flist)
         std::cout << e << " ";
     
     // create prev and curr iterator
     auto prev = flist.before_begin();
     auto curr = flist.begin();
     
     std::cout << std::endl << "Removing odd numbers..." << std::endl;
     while (curr != flist.end()) {
         if (*curr % 2) {
             curr = flist.erase_after(prev);
         } else {
             prev = curr;
             ++curr;
         }
     }
     
     std::cout << "flist: ";
     for (const auto &e : flist)
         std::cout << e << " ";
     
     std::cout << std::endl;
     
     return 0;
 }
