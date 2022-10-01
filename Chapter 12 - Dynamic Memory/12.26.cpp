// Exercise 12.26:
/*
 Rewrite the program on page 481 using an allocator.
*/

// pg. 481
#include <string>
#include <iostream>

void fourEightOne()
{
    int n = 5;
    std::string *const p = new std::string[n];
    std::string s;
    std::string *q = p;
    while (std::cin >> s && q != p + n)
        *q++ = s;
    const std::size_t size = q - p;
    // do things
    delete [] p;
}

void fourEightOneAlloc()
{
    // int n = 5;
    // constexpr suggested in other examples?
    const std::size_t n = 5;
    // create allocator of strings
    std::allocator<std::string> alloc;
    // set p to allocate 5 unconstructed strings
    auto const p = alloc.allocate(n);
    
    // q will point to one past the last constructed element
    auto q = p;
    
    // take standard input
    std::string s;
    std::cout << "Please input some strings: ";
    while (std::cin >> s && q != p + n)
        alloc.construct(q++, s);
    
    std::cout << q - p << " elements were constructed." << std::endl;
    
    std::cout << "Outputting constructed elements: ";
    for (auto pos = p; pos != q; ++pos) {
        std::cout << *pos << " ";
    } std::cout << std::endl;
    
    // destory the elements
    // as long as p doesn't become the off-the-end operator
    std::cout << "Destroying elements...\n";
    while (q != p)
        alloc.destroy(--q);
    // then free the memory
    alloc.deallocate(p, n);
    
    std::cout << "p now has " << q - p << " elements." << std::endl;
}

int main()
{
    fourEightOneAlloc();
    
    return 0;
}
