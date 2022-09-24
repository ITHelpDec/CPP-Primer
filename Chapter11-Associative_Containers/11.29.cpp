// Exercise 11.29:
/*
 What do upper_bound, lower_bound, and equal_range return when you pass them a key that is not in the container?
 
 >> They all return a iterator where it is safe to insert an element safely within the container
 //
 // container.upper_bound() will return container.end()
 // container.lower_bound() will return container.end()
 // container.equal_range() will return {container.end(), container.end()}}
 //
 */
