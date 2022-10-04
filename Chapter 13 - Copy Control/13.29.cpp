// Exercise 13.29:
/*
 Explain why the calls to swap inside swap(HasPtr&, HasPtr&) do not cause a recursion loop.
 */
 // "Each call to swap must be unqualified. That is, each call should be to swap, not std::swap.
 // For reasons we'll explain in 16.3 (p. 697), if there is a type-specific version of swap, that version will be a better match than the one defined in std.
 // As a result, if there is a type-specific version of swap, calls to swap will match that type specific version.
 // If there is no type-specific version, then – assuming there is a using declaration for swap in scope – calls to swap will use the version in std." pg. 518
/*
 >> We are using unqualified calls to swap for swapping members within HasPtr. If a type-specific version of swap cannot be found then the compiler will fall back to std, meaning no risk of recursion.
*/
