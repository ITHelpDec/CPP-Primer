// Exercise 16.13:
/*
 Explain which kind of friendship you chose for the equality and rela- tional operators for BlobPtr.
 
 >> There are three choices of friendship explained in the book – one-to-one, general of specific.
 >> I have used the one-one friendship for the bool operator.
 
 >> "The friend declarations use Blob's template parameter as their own template argument. Thus, the friendship is restricted to those instantiations of BlobPtr and the equality operator that are instantied with the same type" – pg. 665
 
 >> i.e. we want out instantiations to be of the same template parameter type, e.g.
 >> BlobPtr<int> == BlobPtr<int>
 >> ...and not...
 >> BlobPtr<std::string> == BlobPtr<char>
 
*/

template <typename> class BlobPtr;

template <typename T> bool operator< (const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T> class BlobPtr {
    friend bool operator< <T>(const BlobPtr<T> &lhs, const BlobPtr<T>& rhs)
    { return lhs < rhs; }
};
