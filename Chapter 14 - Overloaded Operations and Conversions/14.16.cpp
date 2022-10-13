// Exercise 14.16:
/*
 Define equality and inequality operators for your StrBlob (§ 12.1.1, p. 456), StrBlobPtr (§ 12.1.6, p. 474), StrVec (§ 13.5, p. 526), and String (§ 13.5, p. 531) classes.
 
 >> I'll just do StrBlob
*/

#include <memory>

// StrBlob
class StrBlob {
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);
public:
    // ...
private:
    std::shared_ptr<std::vector<std::string>> data;
    // ...
};

// == operator
bool operator==(const StrBlob &lhs, const StrBlob &rhs)
{
    return lhs.data == rhs.data;
}

// != operator
bool operator!=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs.data == rhs.data);
}
