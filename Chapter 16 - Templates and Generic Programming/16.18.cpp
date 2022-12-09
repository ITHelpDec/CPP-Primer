// Exercise 16.17:
/*
 Explain each of the following function template declarations and iden- tify whether any are illegal. Correct each error that you find.
*/

// (a) – illegal, U typename not defined
template <typename T, U, typename V> void f1(T, U, V);
template <typename T, typename U, typename V> void f1(T, U, V);

// (b) – illegal, T and int should be swapped, or T should be lowercase
// you can't say "bool f2(int &bool)""
template <typename T> T f2(int &T);
template <typename T> T f2(T &t); // or
template <typename T> T f2(int &t);

// (c) - illegal, inline should be after <typename T>
inline template <typename T> T foo(T, unsigned int*);
template <typename T> inline T foo(T, unsigned int*);

// (d) – no return type
template <typename T> f4(T, T);
template <typename T> T f4(T, T);

// (e) – ambiguous; there will be issues with scope
// if you know it's a char, use char
typedef char Ctype;
template <typename Ctype> Ctype f5(Ctype a);
char f5(char a);

