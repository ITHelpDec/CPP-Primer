// Exercise 14.48:
/*
 Determine whether the class you used in exercise 7.40 from § 7.5.1 (p. 291) should have a conversion to bool.
 If so, explain why, and explain whether the operator should be explicit.
 If not, explain why not.
 
 >> It might be useful if we wanted to test the state of the object in a conditional check?
 
 // "Whenever we use a stream object in a condition, we use the operator bool that is defined for the IO types." – pg. 583
 // "That function returns true if the condition state of cin is good (§ 8.1.2, p. 312), and false otherwise." – pg. 583
 // "Under the new standard, the IO library instead defines an explicit conversion to bool." -pg. 583
 // "Conversion to bool is usually intended for use in conditions. As a result, operator bool should ordinarily be defined as explicit." – pg. 583
*/
