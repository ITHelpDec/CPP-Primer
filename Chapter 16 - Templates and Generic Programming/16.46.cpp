// Exercise 16.46:
/*
 Explain this loop from StrVec::reallocate in § 13.5 (p. 530):
*/

for (std::size_t i = 0; i != size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
}

// std::move(*elem++);
// elem is a std::string, so *elem is a char

// function argument is an lvalue, .:. T is deduced as char&
// std::move does its magic, removes the references and converts the char& to char (see page 691), ...
// ...so we end up with something like:
// char&& std::move(char &t);

// this is then repeated for every iteration from 0 -> size()
