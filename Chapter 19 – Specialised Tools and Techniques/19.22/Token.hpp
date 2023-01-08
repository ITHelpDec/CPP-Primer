// Exercise 19.22:
/*
 Add a member of type Sales_data to your Token class.
 
 >> Updates / modifications highlighted in the comments
 
*/

#include <string>
#include <iostream>

// added Sales_data header
#include "Sales_data.hpp"

class Token {
    friend std::ostream& operator<<(std::ostream&, const Token&);
public:
    Token() : tok(INT), ival{0} { }
    
    Token(const Token &t) : tok(t.tok) { copyUnion(t); }
    
    Token& operator=(const Token&);
    
    ~Token()
    {
        if (tok == STR) { sval.std::string::~string(); }
        
        // added Sales_data destructor
        // "Unlike ordinary members of a class type, class member that...
        // ... are part of a union are not automatically destroyed"
        if (tok == SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
    }
    
    Token& operator=(int);
    Token& operator=(char);
    Token& operator=(double);
    Token& operator=(const std::string&);
    
    // added Sales_data copy-assignment operator
    Token& operator=(const Sales_data&);
    
private:
    // added Sales_data enum token
    enum { INT, CHAR, DBL, STR, SALES_DATA} tok;
    union {
        int ival;
        char cval;
        double dval;
        std::string sval;
        
        // added Sales_data union member
        Sales_data sdobj;
    };
    
    void copyUnion(const Token&);
};

Token& Token::operator=(const Token &t)
{
    if (tok == STR && t.tok != STR) { sval.std::string::~string(); }
    if (tok == STR && t.tok == STR) { sval = t.sval; }
    
    // added token checks for Sales_data similar to std::stirng
    if (tok == SALES_DATA && t.tok != SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
    if (tok == SALES_DATA && t.tok == SALES_DATA) { sdobj = t.sdobj; }
    
    else { copyUnion(t); }
    tok = t.tok;
    return *this;
}

Token& Token::operator=(int i)
{
    if (tok == STR) sval.std::string::~string();
    
    // Sales_data destruction check
    if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
    
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(char c)
{
    if (tok == STR) sval.std::string::~string();
    
    // Sales_data destruction check
    if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
    
    cval = c;
    tok = CHAR;
    return *this;
}

Token& Token::operator=(double d)
{
    if (tok == STR) sval.std::string::~string();
    
    // Sales_data destruction check
    if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
    
    dval = d;
    tok = DBL;
    return *this;
}

Token& Token::operator=(const std::string &s)
{
    if (tok == STR) { sval = s; }
    
    // Sales_data destruction check
    if (tok == SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
    
    else { new(&sval) std::string(s); }
    tok = STR;
    return *this;
}

// added Sales_data copy-assignment operator
Token& Token::operator=(const Sales_data &sd)
{
    if (tok == STR) { sval.std::string::~string(); }
    if (tok == SALES_DATA) { sdobj = sd; }
    else { new(&sdobj) Sales_data(sd); }
    tok = SALES_DATA;
    return *this;
}

void Token::copyUnion(const Token &t)
{
    switch (t.tok) {
        case Token::INT: ival = t.ival; break;
        case Token::CHAR: cval = t.cval; break;
        case Token::DBL: dval = t.dval; break;
        case Token::STR: new(&sval) std::string(t.sval); break;
            
        // Sales_data switch case for new element
        case Token::SALES_DATA: new(&sdobj) Sales_data(t.sdobj); break;
    }
}

std::ostream& operator<<(std::ostream &os, const Token &t)
{
    switch (t.tok) {
        case Token::INT: os << t.ival; break;
        case Token::CHAR: os << t.cval; break;
        case Token::DBL: os << t.dval; break;
        case Token::STR: os << t.sval; break;
            
        // Sales_data switch case for printing element
        case Token::SALES_DATA: os << t.sdobj; break;
    }
    
    return os;
}
