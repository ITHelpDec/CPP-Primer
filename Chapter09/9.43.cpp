// Exercise 9.43:
/*
 Write a function that takes three strings, s, oldVal, and newVal.
 Using iterators, and the insert and erase functions replace all instances of oldVal that appear in s by newVal.
 Test your function by using it to replace common abbreviations, such as “tho” by ”though” and ”thru” by “through”.
 
 >> I've included some code from Jaege below, but it doesn't work for single character abbreviations like "r" (replaces all instances of the character "r" instead of a string).
 >> I would like to use a string stream to create a vector and then compare elements to oldVal
 >> If the word matches, then add the newVal to the vector, else add the word normally
 >> Next step would be to find a way to copy the contents of the vector back to s
 >> I'll work on the code another time, but I've attached an example below
 
 void replaceAbbrev(std::string &s, const std::string &oldVal, const std::string &newVal)
 {
     std::istringstream iss(s);
     std::string word;
     std::vector<std::string> svec;
     
     std::cout << s << std::endl;
     
     while (iss >> word) {
         if (word == oldVal) {
             svec.push_back(newVal);
         } else {
             svec.push_back(word);
         }
         
     }
     
     for (const auto &e : svec) {
         std::cout << e << " ";
     }
     std::cout << std::endl;
 }
 
*/

void replaceAbbrev(std::string &s, const std::string &oldVal, const std::string &newVal)
{
    for (auto it = s.begin(); it < s.end() - oldVal.size() + 1; ) {
        auto it2 = oldVal.cbegin();
        for (auto it3 = it; it2 != oldVal.cend(); ++it2, ++it3)
          if (*it3 != *it2)
            break;
        if (it2 == oldVal.cend()) {
          std::string::size_type pos = it - s.begin();
          s.erase(pos, oldVal.size());
          s.insert(pos, newVal);
          // Recalculate `it` from `begin()` rather than use `+=` operator, because
          // `it` is invalid by `erase()` and `insert()`
          it = s.begin() + pos + newVal.size();
        } else
          ++it;
  }
}

int main()
{
    std::string s = "r u going thru the town tho?";
    
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "r", "are");
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "u", "you");
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "thru", "through");
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "tho", "though");
    std::cout << s << std::endl;
    
    return 0;
}
