// Exercise 12.14:
/*
 Write your own version of a function that uses a shared_ptr to manage a connection.
 
 >> Quite a vague exercise...
*/

#include <memory>
#include <string>
#include <iostream>

// represents what we are connecting to
struct Destination {
    // constructor for struct and ip address
    Destination(std::string &dest) : ip(dest)
    {
        std::cout << "Destination:\n" << "You have entered " << ip << " (Google) as the destination." << std::endl;
    }
    
    // variables for the ip address and port
    std::string ip;
    unsigned port = 80;
};

// information needed to use the connection
struct Connection {
    // create a pointer to a Destination struct
    // this gives us access to "ip" and "port"
    Destination *dest;
    
    // e.g.
    // std::string ip = dest->ip;
    // unsigned port = dest->port;
};

// open the connection
// Connection connect(Destination*)
// (Destination *dest) gives us access to all the elements and members
Connection connect(Destination *dest)
{
    // create a new_connection from "Connection" struct
    Connection new_connection;
    
    // the code below gives us access to Destination through Connection
    // without it, the next line of code points to nothing from int main()
    new_connection.dest = dest;
    
    // print out variables from within Destination
    std::cout << "connect:\n" << "Attempting to connect to " << new_connection.dest->ip << " on port " << new_connection.dest->port << "." << std::endl;
    
    // function is type "Connection", so need to return a result of same type
    return new_connection;
}

// close the given connection
// void disconnect(Connection)
// take a Connection class as a parameter and output closure
void disconnect(Connection connection)
{
    std::cout << "disconnect:\n" << "Closing connection to " << connection.dest->ip << " on pport " << connection.dest->port << "." << std::endl;
}


void end_connection(Connection *p)
{
    std::cout << "end_connectoin:\n" << "p: " << p << ", p->dest->port: " << p->dest->port << std::endl;
    disconnect(*p);
}

void f(Destination &d /* other parameters */ )
{
    Connection c = connect(&d);
    std::shared_ptr<Connection> p(&c, end_connection);
}

int main()
{
    std::string google = "209.85.231.104";
    Destination d1(google);
    
    f(d1);
    
    return 0;
}
