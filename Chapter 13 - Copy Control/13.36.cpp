#include <string>
#include <set>
#include <iostream>

// define classes first, followed by members to avoid running into errors
class Message;

// Folder and Message will share a lot of functionality as they relate to each other
class Folder {
    // Folder will need to swap messages between itself
    friend void swap(Message&, Message&);
    // Folder will also need access to Message members
    friend class Message;
    // function to print contents of Folder
    friend std::ostream &printFolder(std::ostream&, Folder&);
    
public:
    // default constructor
    Folder() = default;
    // copy constructor
    Folder(const Folder&);
    // copy assignment
    Folder& operator=(const Folder&);
    // destructor
    ~Folder();
    
    // as with Message, add this message to a Folder
    void save(Message&);
    // remove message form a folder
    void remove(Message&);
    
    // create member to return how many files are in folder
    std::size_t size() { return messages.size(); }
    
private:
    // create a similar set to store messages located in folder
    std::set<Message*> messages;
    
    // replace functions from Message for use in copy-control
    // used by Folder class to add self to this Message's set of Folders
    void add_to_Message_locations(const Folder&);
    void remove_from_Message_locations();
    
    // "f.addMsg(this);" and "f.remMsg(this)" both return type " Message* "
    void addMsg(Message *m) { messages.insert(m); }
    void remMsg(Message *m) { messages.erase(m); }
};

class Message {
    friend class Folder;
    friend void swap(Message&, Message&);
    friend std::ostream &printMessage(std::ostream&, const Message&);
    
public:
    explicit Message(const std::string &str = "") : contents(str) { }
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    
    void save(Folder&);
    void remove(Folder&);
    
private:
    std::string contents;
    std::set<Folder*> folders;
    
    void add_to_Folders(const Message&);
    void remove_from_Folders();
    
    void addFolder(Folder *f) { folders.insert(f); }
    void remFolder(Folder *f) { folders.erase(f); }
};

// Folder copy
Folder::Folder(const Folder &f)
{
    messages = f.messages;
    add_to_Message_locations(f);
}

// Folder copy-assignment
Folder& Folder::operator=(const Folder &rhs)
{
    // handle self-assignment by removing pointers before assigning them
    remove_from_Message_locations();
    messages = rhs.messages;
    add_to_Message_locations(rhs);
    return *this;
}

// Folder destructor
Folder::~Folder()
{
    remove_from_Message_locations();
}

// add this Folder to Messages that point to f
void Folder::add_to_Message_locations(const Folder &f)
{
    // for each message that holds f
    for (auto m : f.messages)
        // add a pointer to this Folder to that Message
        m->addFolder(this);
}

// remove this Folder from the relevant Messages
void Folder::remove_from_Message_locations()
{
    // for every pointer in the lisr of messages
    for (auto m : messages)
        // remove pointer to this Folder from that Message
        m->remFolder(this);
    // no Message points to this Folder
    messages.clear();
}

// Folder save
void Folder::save(Message &m)
{
    messages.insert(&m);
    m.addFolder(this);
}

// Folder remove
void Folder::remove(Message &m)
{
    messages.erase(&m);
    m.remFolder(this);
}

// Message members described as before
Message::Message(const Message &m)
{
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
    folders.clear();
}

void swap (Message &lhs, Message &rhs)
{
    using std::swap;
    
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

std::ostream &printMessage(std::ostream &os, const Message &m)
{
    os << m.contents << " ";
    for (const auto &e : m.folders) {
        std::cout << e << " ";
    } std::cout << std::endl;
    return os;
}

std::ostream &printFolder(std::ostream &os, Folder &f)
{
    for (const auto m : f.messages) {
        os << m << " ";
    } std::cout << std::endl;
    return os;
}

int main()
{
    std::cout << "Loading folders...\n";
    Folder drafts, deleted;
    
    std::cout << "Creating new message...\n";
    Message m1("manbearpig");
    
    printMessage(std::cout, m1);
    
    std::cout <<"\nSaving message to Drafts...\n";
    m1.save(drafts);
    std::cout << "There are " << drafts.size() << (drafts.size() == 1 ? " message" : " messages") << " in Drafts." << std::endl;
    
    std::cout <<"\nDeleting message from Drafts...\n";
    m1.save(deleted);
    m1.remove(drafts);
    std::cout << "There are now " << drafts.size() << (drafts.size() == 1 ? " message" : " messages") << " in Drafts." << std::endl;
    std::cout << "There " << (deleted.size() == 1 ? "is" : "are") <<  " also now " << deleted.size() << " deleted " << (deleted.size() == 1 ? "item" : "items") << " in the Deleted Items folder." << std::endl;
    
    return 0;
}
