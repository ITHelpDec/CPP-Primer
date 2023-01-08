// Exercise 19.25:
/*
 Write assignment operators that take values of each type in the union.
 
 >> Didn't realise I had already done this in exercise 19.23
*/

#include "Sales_data.hpp"

class Token {
    friend std::ostream& operator<<(std::ostream&, const Token&);
public:
    Token() : tok(INT), ival{0} { }
    
    // copy and copy-assignment
    Token(const Token &t) : tok(t.tok) { copyUnion(t); }
    Token& operator=(const Token&);
    
    // move and move-assignment
    Token(Token &&t) noexcept : tok(std::move(t.tok)) { moveUnion(std::move(t)); }
    Token& operator=(Token&&) noexcept;
    
    ~Token()
    {
        if (tok == STR) { sval.std::string::~string(); }
        if (tok == SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
    }
    
    // copy assingment operators
    Token& operator=(const int&);
    Token& operator=(const char&);
    Token& operator=(const double&);
    Token& operator=(const std::string&);
    Token& operator=(const Sales_data&);
    
    // move-assignment operators
    Token& operator=(int&&) noexcept;
    Token& operator=(char&&) noexcept;
    Token& operator=(double&&) noexcept;
    Token& operator=(std::string&&) noexcept;
    Token& operator=(Sales_data&&) noexcept;
    
private:
    enum { INT, CHAR, DBL, STR, SALES_DATA} tok;
    union {
        int ival;
        char cval;
        double dval;
        std::string sval;
        Sales_data sdobj;
    };
    
    void copyUnion(const Token&);
    
    // moveUnion member function created
    void moveUnion(Token&&) noexcept;
};

Token& Token::operator=(const Token &t)
{
    if (tok == STR && t.tok != STR) { sval.std::string::~string(); }
    if (tok == STR && t.tok == STR) { sval = t.sval; }
    
    if (tok == SALES_DATA && t.tok != SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
    if (tok == SALES_DATA && t.tok == SALES_DATA) { sdobj = t.sdobj; }
    
    else { copyUnion(t); }
    tok = t.tok;
    return *this;
}

// move assignment
Token& Token::operator=(Token &&t) noexcept
{
    if (this != &t) {
        if (tok == STR && t.tok != STR) { sval.std::string::~string(); }
        if (tok == STR && t.tok == STR) { sval = std::move(t.sval); }
        
        if (tok == SALES_DATA && t.tok != SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
        if (tok == SALES_DATA && t.tok == SALES_DATA) { sdobj = std::move(t.sdobj); }
        
        else { moveUnion(std::move(t)); }
        tok = std::move(t.tok);
    }
    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// COPY-ASSIGNMENT - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Token& Token::operator=(const int &i)
{
    if (tok == STR) sval.std::string::~string();
    if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
    
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(const char &c)
{
    if (tok == STR) sval.std::string::~string();
    if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
    
    cval = c;
    tok = CHAR;
    return *this;
}

Token& Token::operator=(const double &d)
{
    if (tok == STR) sval.std::string::~string();
    if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
    
    dval = d;
    tok = DBL;
    return *this;
}

Token& Token::operator=(const std::string &s)
{
    if (tok == STR) { sval = s; }
    if (tok == SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
    
    else { new(&sval) std::string(s); }
    tok = STR;
    return *this;
}

Token& Token::operator=(const Sales_data &sd)
{
    if (tok == STR) { sval.std::string::~string(); }
    if (tok == SALES_DATA) { sdobj = sd; }
    else { new(&sdobj) Sales_data(sd); }
    tok = SALES_DATA;
    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// MOVE-ASSIGNMENT - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Token& Token::operator=(int &&i) noexcept
{
    if (ival != i) {
        if (tok == STR) sval.std::string::~string();
        if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
        
        ival = std::move(i);
        tok = INT;
    }
    return *this;
}

Token& Token::operator=(char &&c) noexcept
{
    if (cval != c) {
        if (tok == STR) sval.std::string::~string();
        if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
        
        cval = std::move(c);
        tok = CHAR;
    }
    return *this;
}

Token& Token::operator=(double &&d) noexcept
{
    if (dval != d) {
        if (tok == STR) sval.std::string::~string();
        if (tok == SALES_DATA) sdobj.Sales_data::~Sales_data();
        
        dval = std::move(d);
        tok = DBL;
    }
    return *this;
}

Token& Token::operator=(std::string &&s) noexcept
{
    if (sval != s) {
        if (tok == STR) { sval = std::move(s); }
        if (tok == SALES_DATA) { sdobj.Sales_data::~Sales_data(); }
        
        else { new(&sval) std::string(std::move(s)); }
        tok = STR;
    }
    return *this;
}

Token& Token::operator=(Sales_data &&sd) noexcept
{
    if (sdobj != sd) {
        if (tok == STR) { sval.std::string::~string(); }
        if (tok == SALES_DATA) { sdobj = std::move(sd); }
        else { new(&sdobj) Sales_data(std::move(sd)); }
        tok = SALES_DATA;
    }
    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Token::copyUnion(const Token &t)
{
    switch (t.tok) {
        case Token::INT: ival = t.ival; break;
        case Token::CHAR: cval = t.cval; break;
        case Token::DBL: dval = t.dval; break;
        case Token::STR: new(&sval) std::string(t.sval); break;
        case Token::SALES_DATA: new(&sdobj) Sales_data(t.sdobj); break;
    }
}

void Token::moveUnion(Token &&t) noexcept
{
    if (this != &t) {
        switch (t.tok) {
            case Token::INT: ival = std::move(t.ival); break;
            case Token::CHAR: cval = std::move(t.cval); break;
            case Token::DBL: dval = std::move(t.dval); break;
            case Token::STR: new(&sval) std::string(std::move(t.sval)); break;
            case Token::SALES_DATA: new(&sdobj) Sales_data(std::move(t.sdobj)); break;
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

std::ostream& operator<<(std::ostream &os, const Token &t)
{
    switch (t.tok) {
        case Token::INT: os << t.ival; break;
        case Token::CHAR: os << t.cval; break;
        case Token::DBL: os << t.dval; break;
        case Token::STR: os << t.sval; break;
        case Token::SALES_DATA: os << t.sdobj; break;
    }
    
    return os;
}
