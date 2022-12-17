// Exercise 16.60:
/*
 Explain how make_shared (§ 12.1.1, p. 451) works.
*/

// std::make_shared works by taking an expandable set of arguments and returning a std::shared_ptr<T>

// The body of the function performs std::allocate__shared<T> using std::allocator<T>() as its first argument, and std::forward<Args>(rest)... as its second argument, before returning our std::shared_ptr<T>

// The official STL implementation has been atttached below, taken directly from shared_ptr.hpp

template<class _Tp, class ..._Args, class = _EnableIf<!is_array<_Tp>::value> >
_LIBCPP_HIDE_FROM_ABI
shared_ptr<_Tp> make_shared(_Args&& ...__args)
{
    return _VSTD::allocate_shared<_Tp>(allocator<_Tp>(), _VSTD::forward<_Args>(__args)...);
}
