# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (17/12/2022) .:.

```cpp
// Exercise 16.61:
/*
 Define your own version of make_shared.
*/

#include <memory>
#include <iostream>

/* >> shared_ptr.hpp <<
 
template<class _Tp, class ..._Args, class = _EnableIf<!is_array<_Tp>::value> >
_LIBCPP_HIDE_FROM_ABI
shared_ptr<_Tp> make_shared(_Args&& ...__args)
{
    return _VSTD::allocate_shared<_Tp>(allocator<_Tp>(), _VSTD::forward<_Args>(__args)...);
}
 
*/

// replica of STL implementation
template <class T, class ...Args>
inline std::shared_ptr<T> make_shared(Args &&...rest) {
    return std::allocate_shared<T>(std::allocator<T>(), std::forward<Args>(rest)...);
}

int main()
{
    // my implementation
    auto my_sp = make_shared<std::string>("manbearpig");
    std::cout << "my make_shared:    my_sp = " << *my_sp << std::endl;

    // STL implementation
    auto stl_sp = std::make_shared<std::string>("manbearpig");
    std::cout << "std::make_shared: stl_sp = " << *stl_sp << std::endl;
    
    return 0;
}
```
```
output:
my make_shared:    my_sp = manbearpig
std::make_shared: stl_sp = manbearpig
Program ended with exit code: 0
```
