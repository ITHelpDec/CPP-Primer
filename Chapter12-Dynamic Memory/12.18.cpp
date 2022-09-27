// Exercise 12.18:
/*
 Why doesn’t shared_ptr have a release member?
 
 >> shared_ptr's can have use counts, whereas unique_ptr's cannot – they must be unique
 >> in order for a unique_ptr to remain unique,
 >> it must relenquish its hold over a particular memory location (release)
 >> and give it to the next unique_ptr, or be freed
*/

// pg. 471
// "Calling release breaks the connection between a unique_ptr and the object it had been managing.
// Often the pointer returned by release is used to initialise or assign another smart pointer.
// In that case, responsibility for managing the memory is simply transferred from one smart pointer to another.
// However, if we do not use another smart pointer to hold the pointer returned from reelase, our programme takes over responsibiltiy for freeing that resource"
