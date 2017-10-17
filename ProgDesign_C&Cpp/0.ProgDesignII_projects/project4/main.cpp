#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <time.h>

#include <json/json.h>

std::string getTime() {
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d", localtime(&t));
    return std::string(tmp);
}

#include "exceptions.cpp"
#include "books.cpp"
#include "users.cpp"
#include "UI.cpp"

string check_login(string userName, string password, UsersLib *usrLib) {
    try {
        int userIndex = usrLib->search_one_User(userName);
        if (password == usrLib->get_password_byIndex(userIndex)) {
            cout << "password correct." << endl;
            string ret =  usrLib->get_Group(userIndex);
            cout << "group : " << ret << endl;
            return ret;
        }
        return string("Invalid UserName or Password");
    } catch (Library_Base_Exception &e) {
        cout << e.what() << endl;
    }
    return string("Invalid UserName or Password");
}
void UserInit(Users &user, string userName, string password, UsersLib *userLibs, Library *bookLibrary) {
    user.set(userName, password);
    user.connect_to_Userlib(userLibs);
    user.connect_to_Library(bookLibrary);
}
bool inputNewUser(string &userName, string &password) {
    printf("Enter the UserName : ");
    cin >> userName;
    cin.sync();
    printf("Enter the password : ");
    cin >> password;
    cin.sync();

    printf("The new userName is [%s], password : [%s]. Enter 'y' to register, other to cancel. ",
           userName.c_str(), password.c_str());
    char c;
    cin >> c;
    cin.sync();
    return c == 'y';
}

void Op_NormalUsers(string userName, string password, UsersLib *userLibs, Library *bookLibrary);
void Op_Admin(string userName, string password, UsersLib *userLibs, Library *bookLibrary);
void Op_root(string userName, string password, UsersLib *userLibs, Library *bookLibrary);

int main() {
    Library bookLibrary("./json_data/BookLibrary.json");
    UsersLib userLibs;
    userLibs.init("./json_data/Users.json");

    Welcome();
    char choice;
    do {
        string userName, password, correGroup;
        int numGroup = -1;
        Choose();
        pre_login();
        cin >> choice;
        cin.sync();
        switch (choice) {
        case 'l':
            cout << "UserName : ";
            cin >> userName;
            cin.sync();
            cout << "Password : ";
            cin >> password;
            cin.sync();
            correGroup = check_login(userName, password, &userLibs);
            cout << "userGroup : " << correGroup << endl;
            if (correGroup == string("root")) numGroup = 2;
            else if (correGroup == string("Administrator")) numGroup = 1;
            else if (correGroup == string("Users")) numGroup = 0;
            switch (numGroup) {
            case 0:
                Op_NormalUsers(userName, password, &userLibs, &bookLibrary);
                break;
            case 1:
                Op_Admin(userName, password, &userLibs, &bookLibrary);
                break;
            case 2:
                Op_root(userName, password, &userLibs, &bookLibrary);
                break;
            case -1:
                continue;
            }
            break;
        case 'r':
            try {
                bool confirm_regi = inputNewUser(userName, password);
                if (confirm_regi) {
                    userLibs.add_new_User(userName, password);
                    cout << "New User [" << userName << "] has been registered. Now you can log-in with it." << endl;
                }
            } catch (Library_Base_Exception &e) {
                cout << e.what() << endl;
            }
            break;
        }
    } while (choice != 'q');
    cout << "GoodBye." << endl;
}

void Op_NormalUsers(string userName, string password, UsersLib *userLibs, Library *bookLibrary) {
    Normal_Users normal_user;
    UserInit(normal_user, userName, password, userLibs, bookLibrary);
    if (normal_user.is_rejected()) {
        cout << "Your account is REJECTED. Please contact with the Administrator." << endl;
        return;
    }

    char choice;
    main_menu_NormalUsers();
    do {
        Choose();
        cin >> choice;
        cin.sync();
        switch (choice) {
        case 'k':
            normal_user.query_All_books();
            break;
        case 'l':
            normal_user.query_Inlib_books();
            break;
        case 'c':
            normal_user.search_bookName();
            break;
        case 'v':
            normal_user.search_bookISBN();
            break;
        case 'j':
            normal_user.list_my_borrowingBooks();
            break;
        case 'b':
            normal_user.borrow_oneBook();
            break;
        case 'g':
            normal_user.givback_oneBook();
            break;
        case ',':
            main_menu_NormalUsers();
            break;
        case 'p':
            normal_user.changePswd();
            break;
        }
    } while (choice != 'q');
    prt_logout();
}

void Op_Admin(string userName, string password, UsersLib *userLibs, Library *bookLibrary) {
    Admin_User admin_user;
    UserInit(admin_user, userName, password, userLibs, bookLibrary);

    char choice;
    main_menu_Admin();
    do {
        Choose();
        cin >> choice;
        switch (choice) {
        case 'k':
            admin_user.query_All_books();
            break;
        case 'l':
            admin_user.query_Inlib_books();
            break;
        case 'c':
            admin_user.search_bookName();
            break;
        case 'v':
            admin_user.search_bookISBN();
            break;
        case 'u':
            admin_user.query_All_Users();
            break;
        case 'i':
            admin_user.create_new_User();
            break;
        case 'y':
            admin_user.query_oneUsers_borrowing();
            break;
        case 'a':
            admin_user.add_bookNum();
            break;
        case 'd':
            admin_user.sub_bookNum();
            break;
        case 'w':
            admin_user.create_new_book();
            break;
        case 's':
            admin_user.remove_one_book();
            break;
        case 'r':
            admin_user.setRejected_to_Users();
            break;
        case 'f':
            admin_user.setUNrejected_to_Users();
            break;
        case 'b':
            admin_user.help_Users_brwout();
            break;
        case 'g':
            admin_user.help_Users_givback();
            break;
        case ',':
            main_menu_Admin();
            break;
        case 'p':
            admin_user.changePswd();
            break;
        }

    } while (choice != 'q');
    prt_logout();
}

void Op_root(string userName, string password, UsersLib *userLibs, Library *bookLibrary) {
    Root_User root_user;
    UserInit(root_user, userName, password, userLibs, bookLibrary);

    char choice;
    main_menu_Root();
    do {
        Choose();
        cin >> choice;
        cin.sync();
        switch (choice) {
        case 'j':
            root_user.query_All_Admins();
            break;
        case 'h':
            root_user.create_new_Admin();
            break;
        case 'n':
            root_user.delete_one_Admin();
            break;
        case 'u':
            root_user.query_All_Users();
            break;
        case 'U':
            root_user.delete_one_User();
            break;
        case ',':
            main_menu_Root();
            break;
        case 'p':
            root_user.changePswd();
            break;
        }
    } while (choice != 'q');
    prt_logout();
}
