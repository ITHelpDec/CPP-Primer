// Exercise 12.29:
/*
 We could have written the loop to manage the interaction with the user as a do while (§ 5.4.4, p. 189) loop.
 Rewrite the loop to use a do while.
 Explain which version you prefer and why.
 
 // I prefer the explicit "while (true)" at the beginning
 // Feels easier to follow
*/

void runQueries(std::ifstream &infile) {
    do {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << endl;
    } while (true)
}
