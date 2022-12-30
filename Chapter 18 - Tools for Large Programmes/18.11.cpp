// Exercise 18.11:
/*
 Why is it important that the what function doesn’t throw?
 
 >> std::exception::what() is noexcept by definition – if it were to throw, the entire catch would be wasted, and std::terminate() would be called.
 
 >> "The what function returns a const char* that points to a null-terminated character array, and is guaranteed not to throw any exceptions." – pg. 782
 
 >> I've attached a discussion from stackoverflow below
 >> https://stackoverflow.com/questions/34800519/is-it-important-that-what-does-not-throw-exception-classes
 
*/
