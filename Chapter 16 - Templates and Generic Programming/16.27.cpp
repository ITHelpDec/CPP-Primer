// Exercise 16.27:
/*
 For each labeled statement explain what, if any, instantiations happen.
 If a template is instantiated, explain why; if not, explain why not.
 
 // Programme will run if we remove (e)
*/

// (a) no instantiation; compiles (instantiated when called)
template <typename T> class Stack { };

// (b) no instantiatian; compiles (references and pointers don't need instantiation)
void f1(Stack<char>);

// (c) instantiation; does not compile
class Exercise {
    Stack<double> &rsd;
    Stack<int>    si;
};

int main()
{
    // (d) as with (b)
    Stack<char> *sc;
    
    // (e) instantiation of Stack<char>; does not compile
    f1(*sc);
    
    // (f) instantiation; does not compile (although compiles on my computer)
    int iObj = sizeof(Stack< string >);
    // std::cout << iObj << std::endl;
}

// from the C++ Standard
// https://stackoverflow.com/questions/21598635/how-is-a-template-instantiated
/*
 Unless a function template specialization has been explicitly instantiated or explicitly specialized, the function template specialization is implicitly instantiated when the specialization is referenced in a context that requires a function definition to exist. Unless a call is to a function template explicit specialization or to a member function of an explicitly specialized class template, a default argument for a function template or a member function of a class template is implicitly instantiated when the function is called in a context that requires the value of the default argument.
*/
