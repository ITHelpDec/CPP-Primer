// Exercise 8.3:
/*
 What causes the following while to terminate? while (cin >> i) ...
 
 The following will cause a while loop to terminate:
 >> Reaching end-of-file (eofbit and failbit)
 >> A recoverable error e.g. reading a character when numeric data was expected (failbit)
 >> A system-level failure e.g. an unrecoverable read of write (badbit)
*/
