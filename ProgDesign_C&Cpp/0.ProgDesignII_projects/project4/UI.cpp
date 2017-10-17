#include <iostream>

using namespace std;

void Welcome() {
    cout << "Welcome to Advanced Library Agenda." << endl;
}
void Choose() {
    cout << "Choose one :" << endl;
}
void prt_login(string userName, string usrGroup) {
    cout << "You have logged in with UserName [" << userName << "], Group : [" << usrGroup << "]." << endl;
}
void prt_logout() {
    cout << " You have logged out." << endl;
}

void pre_login() {
    cout << " l : login " << endl;
    cout << " r : register" << endl;
    cout << " q : quit" << endl;
}

void main_menu_NormalUsers() {
    cout << " k : list all books" << endl;
    cout << " l : list all books available in Library" << endl;
    cout << " c : search Book by Name" << endl;
    cout << " v : search Book by ISBN" << endl;
    cout << " j : list My Borrowing Book" << endl;
    cout << " b : borrow one book" << endl;
    cout << " g : give_back one book" << endl;
    cout << " p : change your password" << endl;
    cout << " , : print the menu again" << endl;
    cout << " q : logout" << endl;
}
void main_menu_Admin() {
    cout << " k : list all books" << endl;
    cout << " l : list all books available IN LIBRARY" << endl;
    cout << " c : search Book by Name" << endl;
    cout << " v : search Book by ISBN" << endl;
    cout << " u : list all Normal_Users" << endl;
    cout << " i : create one NEW Normal_Users Account" << endl;
    cout << " y : list target User's Book_Borrowing List" << endl;
    cout << " a : ADD one certain book's NUMBER" << endl;
    cout << " d : SUB one certain book's NUMBER" << endl;
    cout << " w : create one NEW book" << endl;
    cout << " s : REMOVE one book" << endl;
    cout << " r : set ONE USER to be REJECTED" << endl;
    cout << " f : set ONE USER to be UN-REJECTED" << endl;
    cout << " b : HELP ONE USER to borrow one book" << endl;
    cout << " g : HELP ONE USER to give_back one book" << endl;
    cout << " p : Change your password" << endl;
    cout << " , : print the menu again" << endl;
    cout << " q : Logout" << endl;
}
void main_menu_Root() {
    cout << " j : list all Admin_Users" << endl;
    cout << " h : create a new Administrator account" << endl;
    cout << " n : remove an Administrator account" << endl;
    cout << " u : list all Normal_Users" << endl;
    cout << " U : remove a Normal_User's account" << endl;
    cout << " p : Change your password" << endl;
    cout << " , : print the menu again" << endl;
    cout << " q : Logout" << endl;
}

