// Exercise 16.59:
/*
 Assuming s is a string, explain svec.emplace_back(s).
*/

std::string s = "manbearpig";"

svec.emplace_back(s);
alloc.construct(first_free++, std::forward<Args>(s));
alloc.construct(first_free++, std::forward<std::string>(s));
alloc.construct(first_free++, "manbearpig");

// "The result type from std::forward<std::string> is std::string&&, so construct will be called with an rvalue reference."
// "The construct function will, in turn, forward this argument to the std::string move constructor to build this element." – pg. 705
