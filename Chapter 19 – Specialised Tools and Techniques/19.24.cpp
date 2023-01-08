// Exercise 19.24:
/*
 Explain what happens if we assign a Token object to itself.
*/

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

/*
 
 >> If we assign a Token object to itself, we will go through the steps above
 
 >> (1) both sides have differing / similar tokens (STR / SALES_DATA)?
 >> >>> destruct / copy-assign
 
 >> (2) perform copyUnion
 >> (3) update the token
 
 >> if both tokens are the same, then this operation feels slightly wasteful
 >> in my move assignment operator, I check if the union member is the same first
 >> if it's the same, then it's needlessly expensive to perform all of the swaps, so we just return
 
*/

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
