// Exercise 16.31:
/*
 Explain how the compiler might inline the call to the deleter if we used DebugDelete with unique_ptr.
 
 >> The compiler might inline the call to the deleter if we were to bind the Deleter at compile time, as opposed to at run-time.
 
 >> "The type of del is either the default deleter yype or a user-supplied type. It doesn't matter; either way the code that will be executed is known at compile time."
 
 >> "Indeed, if the deleter is something like our DebugDeleter class, this call might even be inlined at compile time" – pg. 678
*/
