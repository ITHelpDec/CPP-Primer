// Exercise 19.21:
/*
 Write your own version of the Token class.
*/

#include <string>
#include <iostream>

class Token {
    friend std::ostream& operator<<(std::ostream&, const Token&);
public:
    Token() : tok(INT), ival{0} { }
    
    Token(const Token &t) : tok(t.tok) { copyUnion(t); }
    
    Token& operator=(const Token&);
    
    // code supplied by book
    // ~Token() { if (tok == STR) sval.~string(); }
    // error: "Qualified member access refers to a member in namespace 'std'"
    
    ~Token() { if (tok == STR) sval.std::string::~string(); }
    
    // can also use basic_string
    // ~Token() { if (tok == STR) sval.~basic_string(); }
    
    Token& operator=(int);
    Token& operator=(char);
    Token& operator=(double);
    Token& operator=(const std::string&);
    
private:
    enum { INT, CHAR, DBL, STR } tok;
    union {
        int ival;
        char cval;
        double dval;
        std::string sval;
    };
    
    void copyUnion(const Token&);
    
};

Token& Token::operator=(const Token &t)
{
    if (tok == STR && t.tok != STR) { sval.std::string::~string(); }
    if (tok == STR && t.tok == STR) { sval = t.sval; }
    else
        copyUnion(t);
    tok = t.tok;
    return *this;
    
    // tok = rhs.tok;
    // copyUnion(rhs);
    // return *this;
}

Token& Token::operator=(int i)
{
    // error: "Qualified member access refers to a member in namespace 'std'"
    // if (tok == STR) sval.~string();
    if (tok == STR) sval.std::string::~string();
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(char c)
{
    if (tok == STR) sval.std::string::~string();
    cval = c;
    tok = CHAR;
    return *this;
}

Token& Token::operator=(double d)
{
    if (tok == STR) sval.std::string::~string();
    dval = d;
    tok = DBL;
    return *this;
}

Token& Token::operator=(const std::string &s)
{
    if (tok == STR)
        sval = s;
    else
        new(&sval) std::string(s);
    tok = STR;
    return *this;
}

void Token::copyUnion(const Token &t)
{
    switch (t.tok) {
        case Token::INT: ival = t.ival; break;
        case Token::CHAR: cval = t.cval; break;
        case Token::DBL: dval = t.dval; break;
        case Token::STR: new(&sval) std::string(t.sval); break;
    }
}

std::ostream& operator<<(std::ostream &os, const Token &t)
{
    switch (t.tok) {
        case Token::INT: os << t.ival; break;
        case Token::CHAR: os << t.cval; break;
        case Token::DBL: os << t.dval; break;
        case Token::STR: os << t.sval; break;
    }
    
    return os;
}
