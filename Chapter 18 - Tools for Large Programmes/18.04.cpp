// Exercise 18.04:
/*
 Looking ahead to the inheritance hierarchy in Figure 18.1 (p. 783), explain what’s wrong with the following try block. Correct it.
*/

/* .:. HIERARCHY .:. */
/*
                     exception
                   /   /   \   \
                  /   /     \   \
          bad_cast   /       \   bad_alloc
                    /         \
      runtime_error            logic_error
                  |            |
 overflow_error---|            |---domain_error
                  |            |
underflow_error---|            |---invalid_argument
                  |            |
    range_error---|            |---out_of_range
                               |
                               |---length_error
 
*/

try {
    // use of the C++ standard library
} catch (std::exception) {
    // ...
} catch (const std::runtime_error &re) {
    // ...
} catch (std::overflow_error eobj) {
    /* ... */
}

// "...handlers for a derived type occur before a catch for its base type." – pg. 776

// we must re-order our try { } catch { } to do derived before base

try {
    // use of the C++ standard library
} catch (std::overflow_error eobj) {
    // ...
} catch (const std::runtime_error &re) {
    // ...
} catch (std::exception) {
    /* ... */
}
