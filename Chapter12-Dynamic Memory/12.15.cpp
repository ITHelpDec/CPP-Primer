// Exercise 12.15:
/*
 Rewrite the first exercise to use a lambda (§ 10.3.2, p. 388) in place of the end_connection function.
*/

#include <memory>
#include <string>
#include <iostream>

struct Destination {
    Destination(std::string &dest) : ip(dest) {
        std::cout << "Destination:\n" << "You have entered " << ip << " (Google) as the destination." << std::endl;
    }
    std::string ip;
    unsigned port = 80;
};

struct Connection {
    Destination *dest;
};

Connection connect(Destination *dest)
{
    Connection new_connection;
    new_connection.dest = dest;
    std::cout << "connect:\n" << "Attempting to connect to " << new_connection.dest->ip << " on port " << new_connection.dest->port << "." << std::endl;
    return new_connection;
}

void disconnect(Connection connection)
{
    std::cout << "disconnect:\n" << "Closing connection to " << connection.dest->ip << " on port " << connection.dest->port << "." << std::endl;
}

// void end_connection(Connection *p)
// {
//     std::cout << "end_connectoin:\n" << "p: " << p << ", p->dest->port: " << p->dest->port << std::endl;
//     disconnect(*p);
// }

void f(Destination &d /* other parameters */ )
{
    Connection c = connect(&d);
    // std::shared_ptr<Connection> p(&c, end_connection);
    std::shared_ptr<Connection> p(&c, [] (Connection *p) { disconnect(*p); } );
}

int main()
{
    std::string google = "209.85.231.104";
    Destination d1(google);
    
    f(d1);
    
    return 0;
}
