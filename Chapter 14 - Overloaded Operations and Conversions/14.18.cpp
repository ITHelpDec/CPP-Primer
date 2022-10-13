// Exercise 14.18:
/*
 Define relational operators for your StrBlob, StrBlobPtr, StrVec, and String classes.
 
 >> I'm not going to do them all again, just StrBlob
*/

#include <memory>

// StrBlob
class StrBlob {
    // plenty of friend members
    // first acts as a template to the next, and so on and so on
    friend bool operator<(const StrBlob&, const StrBlob&);
    friend bool operator>(const StrBlob&, const StrBlob&);
    friend bool operator<=(const StrBlob&, const StrBlob&);
    friend bool operator>=(const StrBlob&, const StrBlob&);
    
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);
public:
    // ...
private:
    std::shared_ptr<std::vector<std::string>> data;
    // ...
};

bool operator==(const StrBlob &lhs, const StrBlob &rhs)
{
    return lhs.data == rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs.data == rhs.data);
}

// "<" operator
bool operator<(const StrBlob &lhs, const StrBlob &rhs)
{
    return lhs.data < rhs.data;
}

// ">" operator
bool operator>(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs < rhs);
}

// "<=" operator
bool operator<=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs> rhs);
}

// ">=" operator
bool operator>=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs < rhs);
};
