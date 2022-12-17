// Exercise 16.57:
/*
 Write and test a variadic version of errorMsg.
*/

template <typename ...Args>
std::ostream& errorMsg(std::ostream &os, const Args &...rest)
{
    return print(os, debug_rep(rest)...);
}

// ...vs...

void error_msg(ErrCode e, initializer_list<string> il) {
    std::cout << e.msg() << ": ";
    for (const auto &elem : il) {
        std::cout << elem << " " ;
    } std::cout << std::endl;
}

/* Variadic (errorMsg) */
// Advantages:
//
// // allows multiple arguments of DIFFERENT types
// // useful when we know neither the number nor the type of arguments being passed to the function
//
// Disadvantages:
//
// // can produce unexpected behaviour if functions are not defined properly
// // recursive in nature – could be performing potentialy-unnecessary work; less flexible than manually taking control of the stack (think "bfs" vs "dfs" / std::queue<T> vs std::stack<T>)

/* Initialiser-list (error_msg) */
// Advantages:
//
// // probably less expensive of an operation because less deduction is needed before execution
//
// Disadvantages:
//
// // the initialiser list must contains elements of all the same type (not as flexible as a variadic template)
