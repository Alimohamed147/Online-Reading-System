#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>
#define nl '\n'
using namespace std;

int ReadInt(int low, int high) {
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int value;

    cin >> value;

    if (low <= value && value <= high)
        return value;

    cout << "ERROR: invalid number...Try again\n";
    return ReadInt(low, high);
}

int ShowReadMenu(const vector<string> &choices) {
    cout << "\nMenu:\n";
    for (int ch = 0; ch < (int) choices.size(); ++ch) {
        cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
    }
    return ReadInt(1, choices.size());
}

class book {
private :
    string title;
    string author;
    vector<string> pages;

public :
    void read() {
        cout << "Enter book title :";
        cin >> title;
        cout << "Enter book author :";
        cin >> author;
        cout << "Enter the size of the book :";
        int size_of_book;
        cin >> size_of_book;
        pages.resize(size_of_book);
        for (int i = 0; i < size_of_book; i++) {
            cout << "Enter page " << i + 1 << ':';
            cin >> pages[i];
        }
    }

    void set_title(const string &t) {
        title = t;
    }

    string get_title() const {
        return title;
    }

    void set_author(const string &a) {
        author = a;
    }

    string get_author() const {
        return author;
    }

    void set_page(int index, const string &content) {
        if (index >= 0 && index < pages.size()) {
            pages[index] = content;
        } else {
            cout << "Index out of bounds" << endl;
        }
    }

    void set_pages(const vector<string> &p) {
        pages = p;
    }

    string get_page(int index) const {
        if (index >= 0 && index < pages.size()) {
            return pages[index];
        } else {
            cout << "Index out of bounds" << endl;
            return "";
        }
    }

    int get_page_count() const {
        return pages.size();
    }
};

class book_reading_session {
private :
    book *current_book;
    int current_page;
    time_t timestamp;

public :
    book_reading_session(book* b): current_book(b), current_page(0) {
        timestamp = time(nullptr);
    }

    void get_next_page() {
        if (current_page + 1 < current_book->get_page_count()) {
            current_page++;
        } else {
            cout << "You are at the end of the book" << endl;
        }
    }

    void get_previous_page() {
        if (current_page - 1 >= 0) {
            current_page--;
        } else {
            cout << "You are at the beginning of the book" << endl;
        }
    }
    int get_current_page_idx()const {
    return current_page;
}
    string get_current_page_content() const {
        return current_book->get_page(current_page);
    }

    string get_timestamp() const {
        return ctime(&timestamp);
    }

    void set_timestamp(time_t t) {
        timestamp = t;
    }

    void set_current_page(int page) {
        if (page >= 0 && page < current_book->get_page_count()) {
            current_page = page;
        } else {
            cout << "Index out of bounds" << endl;
        }
    }

    void get_reading_session_info() const {
        cout << "Current page: " << current_page + 1 << endl;
        cout << "Timestamp: " << get_timestamp() << endl;
    }
};

class user {
private :
    string name;
    string username;
    string password;
    string Email;
    bool is_admin;
    vector<book_reading_session *> reading_sessions;

public :
    user(const user &) = delete;

    user &operator=(const user &) = delete;

    user() {
        is_admin = false;
    }

    ~user() {
        cout << "Destroying user and cleaning up resources" << endl;
        for (auto session: reading_sessions) {
            delete session;
        }
        reading_sessions.clear();
    }

    string get_user_info() const {
        ostringstream s;
        s << "Name : " << name << nl;
        s << "User name : " << username << nl;
        s << "Email : " << Email << nl;
        return s.str();
    }

    void Read(const string &user_name) {
        set_username(user_name);
        string str;
        cout << "Enter password: ";
        cin >> str;
        set_password(str);
        cout << "Enter name: ";
        cin >> str;
        set_name(str);
        cout << "Enter email: ";
        cin >> str;
        set_Email(str);
    }

    void set_password(const string &s) {
        password = s;
    }

    void set_name(const string &s) {
        name = s;
    }

    void set_username(const string &s) {
        username = s;
    }

    void set_Email(const string &s) {
        Email = s;
    }

    string get_username() const {
        return username;
    }

    string get_name() const {
        return name;
    }

    string get_email() const {
        return Email;
    }

    string get_password() const {
        return password;
    }

    void set_library_admin(bool admin) {
        is_admin = admin;
    }

    bool is_library_admin() const {
        return is_admin;
    }

    book_reading_session *add_reading_session(book* book) {
        book_reading_session *session = new book_reading_session(book);
        reading_sessions.emplace_back(session);
        return session;
    }

    vector<book_reading_session *> get_reading_sessions() const {
        return reading_sessions;
    }
};

class user_managment {
private :
    user *current_user = nullptr;
    map<string, user *> username_to_user;

    void FreeLoadedData() {
        for (auto pair: username_to_user) {
            delete pair.second;
        }
        username_to_user.clear();
        current_user = nullptr;
    }

public :
    void LoadDatabase() {
        cout << "UsersManager: LoadDatabase\n";
        FreeLoadedData();
        user *user1 = new user();
        user1->set_username("mostafa");
        user1->set_password("111");
        user1->set_Email("most@gmail.com");
        user1->set_library_admin(true);
        user1->set_name("Mostafa Saad Ibrahim");
        username_to_user[user1->get_username()] = user1;

        user *user2 = new user();
        user2->set_username("asmaa");
        user2->set_password("222");
        user2->set_Email("asmaa@gmail.com");
        user2->set_library_admin(false);
        user2->set_name("Asmaa Saad Ibrahim");
        username_to_user[user2->get_username()] = user2;
    }

    void login(const string &username, const string &password) {
        user *u = get_user_by_username(username);
        if (u != nullptr && u->get_password() == password) {
            cout << "Login successful" << endl;
            current_user = u;
        } else {
            cout << "Invalid username or password" << endl;
        }
    }

    void access_system() {
        if (ShowReadMenu({"Login", "Signup"}) == 1) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            login(username, password);
        } else {
            string name, username, password, email;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter email: ";
            cin >> email;
            signup(name, username, password, email);
        }
    }

    void signup(const string &name, const string &username, const string &password, const string &email) {
        if (get_user_by_username(username) != nullptr) {
            cout << "Username already exists" << endl;
            return;
        }
        user *u = new user();
        u->set_name(name);
        u->set_username(username);
        u->set_password(password);
        u->set_Email(email);
        add_user(u);
        cout << "Signup successful" << endl;
        current_user = u;
    }

    void logout() {
        current_user = nullptr;
    }

    void add_user(user *u) {
        username_to_user[u->get_username()] = u;
    }

    user *get_user_by_username(const string &username) {
        if (username_to_user.find(username) != username_to_user.end()) {
            return username_to_user[username];
        } else {
            return nullptr;
        }
    }
    void add_reading_session(book* book) {
        current_user->add_reading_session(book);
    }
    user *get_current_user() {
        return current_user;
    }

    ~user_managment() {
        for (auto pair: username_to_user) {
            delete pair.second;
        }
        username_to_user.clear();
    }
};

class books_management {
private :
    vector<book *> books;
    map<string, book *> title_to_book;

    void FreeLoadedData() {
        for (auto b: books)
            delete b;

        books.clear();
        title_to_book.clear();
    }

public :
    void load_data() {
        cout << "BooksManager: LoadDatabase\n";
        FreeLoadedData();
        book *book1 = new book();
        book1->set_author("Mostafa");
        book1->set_title("C++ how to program");
        vector<string> pages1 = {"A C++", "B C++", "C C++", "D C++", "E C++"};
        book1->set_pages(pages1);
        add_book(book1);

        book *book2 = new book();
        book2->set_author("Morad");
        book2->set_title("Intro to algo");
        vector<string> pages2 = {"A Algo", "B Algo", "C Algo", "D Algo", "E "};
        book2->set_pages(pages2);
        add_book(book2);
        book *book3 = new book();
        book3->set_author("Morad");
        book3->set_title("Data Structures in C++");
        vector<string> pages3 = {"A Data", "B Data", "C Data", "D Data", "E Data"};
        book3->set_pages(pages3);
        add_book(book3);
    }

    void add_book(book *b) {
        books.emplace_back(b);
        title_to_book[b->get_title()] = books.back();
    }

    book *get_book_by_title(const string &title) {
        if (title_to_book.find(title) != title_to_book.end()) {
            return title_to_book[title];
        } else {
            return nullptr;
        }
    }

    vector<book *> get_all_books() {
        return books;
    }

    ~books_management() {
        FreeLoadedData();
    }
};

class user_view {
private :
    user_managment &user_mgr;
    books_management &books_mgr;

public :
    user_view(user_managment &um, books_management &bm): user_mgr(um), books_mgr(bm) {
    }

    void start() {
        user_mgr.access_system();
    }

    void display() {
        cout << "User View Display" << endl;
        vector<string> choices = {"view Profile", "View Books", "View Reading Sessions", "Logout"};
        while (true) {
            int choice = ShowReadMenu(choices);
            if (choice == 1) {
                view_profile();
            } else if (choice == 2) {
                view_books();
            } else if (choice == 3) {
                view_reading_sessions();
            } else if (choice == 4) {
                user_mgr.logout();
                break;
            }
        }
    }

    void view_profile() {
        user *u = user_mgr.get_current_user();
        if (u != nullptr) {
            cout << u->get_user_info() << endl;
        } else {
            cout << "No user logged in" << endl;
        }
    }

    void view_books() {
        int idx = 0;
        auto all_books = books_mgr.get_all_books();
        for (auto i: all_books) {
            cout << "book " << ++idx << " : Title: " << i->get_title() << ", Author: " << i->get_author() << endl;
        }
        cout << "Choose which book to read";
        int choice = ReadInt(1,idx);
        auto session = user_mgr.get_current_user()->add_reading_session(all_books[choice-1]);
        display_session(session);
    }
    void display_session(book_reading_session* session) {
        vector<string>choices = {"Next page","Previous page","Exit"};
        ShowReadMenu(choices);
        while (true) {
            cout<<"Current page is "<<session->get_current_page_idx()<<nl;
            cout<<session->get_current_page_content()<<nl;
            int choice = ShowReadMenu(choices);
            if (choice == 1)
                session->get_next_page();
            else if (choice == 2)
                session->get_previous_page();
            else
                break;
        }
    }
    void view_reading_sessions() {
        user *u = user_mgr.get_current_user();
        if (u != nullptr) {
            for (auto i: u->get_reading_sessions()) {
                i->get_reading_session_info();
            }
        } else {
            cout << "No user logged in" << endl;
        }
    }
};

class admin_view {
private :
    user_managment &user_mgr;
    books_management &books_mgr;

public :
    admin_view(user_managment &um, books_management &bm): user_mgr(um), books_mgr(bm) {
    }

    void start() {
        user_mgr.access_system();
    }

    void display() {
        cout << "Admin View Display" << endl;
        vector<string> choices = {"view Profile", "Add Books", "Logout"};
        while (true) {
            int choice = ShowReadMenu(choices);
            if (choice == 1) {
                view_profile();
            } else if (choice == 2) {
                add_book();
            } else if (choice == 3) {
                user_mgr.logout();
                break;
            }
        }
    }

    void view_profile() {
        user *u = user_mgr.get_current_user();
        if (u != nullptr) {
            cout << u->get_user_info() << endl;
        } else {
            cout << "No user logged in" << endl;
        }
    }

    void add_book() {
        book *b = new book();
        b->read();
        books_mgr.add_book(b);
        cout << "Book added successfully" << endl;
    }

    void logout() {
        user_mgr.logout();
    }
};

class online_library_system {
private :
    user_managment *user_mgr;
    books_management *books_mgr;

    void LoadDatabase() {
        user_mgr->LoadDatabase();
        books_mgr->load_data();
    }

public :
    online_library_system(): user_mgr(new user_managment()), books_mgr(new books_management()) {
    }

    ~online_library_system() {
        delete user_mgr;
        delete books_mgr;
    }

    void start() {
        LoadDatabase();
        while (true) {
            user_mgr->access_system();
            if (user_mgr->get_current_user() == nullptr) {
                continue;
            }
            if (user_mgr->get_current_user()->is_library_admin()) {
                admin_view view(*user_mgr, *books_mgr);
                view.display();
            } else {
                user_view view(*user_mgr, *books_mgr);
                view.display();
            }
        }
    }
};

int main() {
    online_library_system system;
    system.start();
    return 0;
}
