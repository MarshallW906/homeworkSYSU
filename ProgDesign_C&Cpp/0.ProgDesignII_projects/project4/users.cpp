#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>

using namespace std;

class UsersLib {
  private:
    ifstream lib_File_;
    Json::Value lib_root_user_;
    Json::Reader json_reader_;
    Json::StyledWriter json_writer_;

    std::string fileName_;
    int UserCount;
  public:
    UsersLib() {}
    static Json::Value create_User_Turnover(int mode, std::string bkName, std::string bkISBN, std::string tmpTime, int time_long = 30) {
        Json::Value ret;
        ret["op"] = mode ? string("give_back") : string("borrow_out");
        ret["book_Name"] = bkName;
        ret["book_ISBN"] = bkISBN;
        ret["time"] = tmpTime;
        ret["time_long"] = mode ? -1 : time_long;
        return ret;
    }
    void init(std::string fileName) {
        fileName_ = fileName;
        lib_File_.open(fileName);
        if (!json_reader_.parse(lib_File_, lib_root_user_, false))
            throw JsonReadError();
        UserCount = lib_root_user_["UserCount"].asInt();
    }
    void save_to_File() {
        if (lib_File_.is_open()) lib_File_.close();

        string data = json_writer_.write(lib_root_user_);
        ofstream ofs_File;
        ofs_File.open(fileName_);
        ofs_File << data;
        ofs_File.close();
        printf("UsersLib Data have been stored successfully.\n");
    }
    ~UsersLib() {
        if (lib_File_.is_open()) lib_File_.close();
        save_to_File();
    }

    bool add_new_User(std::string userName, std::string password, int mode = 0) {
        int index = search_one_User(userName);
        if (index < UserCount) throw UserDuplicated();

        lib_root_user_["UserCount"] = ++UserCount;
        Json::Value tmpNewUser;
        tmpNewUser["Group"] = mode ? "Administrator" : "Users";
        tmpNewUser["UserName"] = userName;
        tmpNewUser["password"] = password;
        if (mode == 0) {
            tmpNewUser["book_borrowing_num"] = 0;
            Json::Value bkborwing(Json::arrayValue);
            tmpNewUser["book_borrowing"] = bkborwing;
            tmpNewUser["is_Rejected"] = false;
        }
        lib_root_user_["UserList"].append(tmpNewUser);
        return true;
    }
    bool delete_one_User(std::string userName) {
        int index = search_one_User(userName);
        if (index == UserCount) throw UserNotFound();
        Json::Value tmpRm;
        lib_root_user_["UserList"].removeIndex(index, &tmpRm);
        lib_root_user_["UserCount"] = --UserCount;
        return true;
    }

    void List_all_Users() {
        for (int i = 0; i < UserCount; i++) {
            if (lib_root_user_["UserList"][i]["Group"].asString() == "Users")
                printf("%20s %20s %s\n",
                       lib_root_user_["UserList"][i]["UserName"].asString().c_str(),
                       lib_root_user_["UserList"][i]["UserName"].asString().c_str(),
                       lib_root_user_["UserList"][i]["is_Rejected"].asBool() ? "REJECTED" : "");
        }
    }
    // List_all_Users() is only available for Administrator or root
    void List_all_Admins() {
        for (int i = 0; i < UserCount; i++) {
            if (lib_root_user_["UserList"][i]["Group"].asString() == "Administrator")
                printf("%20s %20s\n",
                       lib_root_user_["UserList"][i]["UserName"].asString().c_str(),
                       lib_root_user_["UserList"][i]["UserName"].asString().c_str());
        }
    }
    // List Admins()  is only available for "root"
    int search_one_User(std::string userName) {
        for (int i = 0; i < UserCount; i++)
            if (lib_root_user_["UserList"][i]["UserName"].asString() == userName) return i;
        return UserCount;
    }

    string get_password_byIndex(int userIndex) {
        if (userIndex >= UserCount) throw IndexOverflow();
        return lib_root_user_["UserList"][userIndex]["password"].asString();
    }
    bool change_password(std::string userName, std::string new_pswd) {
        int index = search_one_User(userName);
        if (index == UserCount) throw UserNotFound();
        lib_root_user_["UserList"][index]["password"] = new_pswd;
        return true;
    }
    // bool change_Group(std::string userName) {return true;}
    std::string get_Group(int userIndex) {
        if (userIndex >= UserCount) throw UserNotFound();
        return lib_root_user_["UserList"][userIndex]["Group"].asString();
    }
    bool append_bw_gb_Turnovers_to_Users(int mode, string bkName, string bkISBN, string userName, int time_long = 30) {
        int userIndex = search_one_User(userName);
        lib_root_user_["UserList"][userIndex]["Turnovers"].append(create_User_Turnover(mode, bkName, bkISBN, getTime(), time_long));
        return true;
    }

    bool add_one_BookBorrowing(int userIndex, string bkISBN) {
        if (userIndex >= UserCount) throw IndexOverflow();
        lib_root_user_["UserList"][userIndex]["book_borrowing"].append(bkISBN);
        int book_borrowing_num = lib_root_user_["UserList"][userIndex]["book_borrowing_num"].asInt();
        lib_root_user_["UserList"][userIndex]["book_borrowing_num"] = book_borrowing_num + 1;
        return true;
    }
    bool remove_one_BookBorrowing(int userIndex, string bkISBN) {
        if (userIndex >= UserCount) throw IndexOverflow();
        int i, borrow_num = lib_root_user_["UserList"][userIndex]["book_borrowing_num"].asInt();
        for (i = 0; i < borrow_num; i++)
            if (lib_root_user_["UserList"][userIndex]["book_borrowing"][i].asString() == bkISBN) break;
        if (i == borrow_num) throw BookNotFound();
        Json::Value tmpRm;
        lib_root_user_["UserList"][userIndex]["book_borrowing"].removeIndex(i, &tmpRm);
        lib_root_user_["UserList"][userIndex]["book_borrowing_num"] = borrow_num - 1;
        return true;
    }
    void List_One_BookBorrowing(int userIndex) {
        if (userIndex >= UserCount) throw IndexOverflow();
        int book_borrowing_num = lib_root_user_["UserList"][userIndex]["book_borrowing_num"].asInt();
        for (int i = 0; i < book_borrowing_num; i++)
            printf("%d %s\n", i + 1, lib_root_user_["UserList"][userIndex]["book_borrowing"][i].asString().c_str());
    }

    bool is_normalUser_rejected(std::string userName) {
        int userIndex = search_one_User(userName);
        if (userIndex >= UserCount) throw UserNotFound();
        if (get_Group(userIndex) != "Users") throw UserGroupError();
        return lib_root_user_["UserList"][userIndex]["is_Rejected"].asBool();
    }
    bool set_normalUser_rejected(std::string userName) {
        int userIndex = search_one_User(userName);
        if (userIndex >= UserCount) throw UserNotFound();
        if (get_Group(userIndex) != "Users") throw UserGroupError();
        lib_root_user_["UserList"][userIndex]["is_Rejected"] = true;
        printf("%s has been rejected.\n", userName.c_str());
        return true;
    }
    bool set_normalUser_UNrejected(std::string userName) {
        int userIndex = search_one_User(userName);
        if (userIndex >= UserCount) throw UserNotFound();
        if (get_Group(userIndex) != "Users") throw UserGroupError();
        lib_root_user_["UserList"][userIndex]["is_Rejected"] = false;
        printf("%s has been UN-rejected.\n", userName.c_str());
        return true;
    }
};

class Users {
  public:
    std::string self_UserName;
    std::string self_password;
    UsersLib *usrLib;
    Library *bookLib;

    void set(std::string userName, std::string password) {
        self_UserName = userName;
        self_password = password;
    }
    void connect_to_Library(Library *tmpBkLib) {
        bookLib = tmpBkLib;
    }
    void connect_to_Userlib(UsersLib *tmpUsrlib) {
        usrLib = tmpUsrlib;
    }

    void query_All_books() {
        bookLib->List_all_books();
    }
    void query_Inlib_books() {
        bookLib->List_inLib_books();
    }
    void search_bookName() {
        std::string name_to_search;
        printf("Enter the keywords to search : ");
        cin >> name_to_search;
        cin.sync();

        int resCount, resArray[1000];
        resCount = bookLib->search_book_byName(name_to_search, resArray);
        if (!resCount)
            printf("Didn't find any book whose Name contains [%s].\n", name_to_search.c_str());
        else bookLib->print_CertainBooks(resArray, resCount);
    }
    void search_bookISBN() {
        std::string ISBN_to_search;
        printf("Enter the completed ISBN to search : ");
        cin >> ISBN_to_search;
        cin.sync();

        int resIndex = bookLib->search_book_byISBN(ISBN_to_search);
        bookLib->print_CertainBooks(&resIndex, 1);
    }

    bool changePswd() {
        string new_password;
        printf("Enter the old_password : ");
        string tmpPswd;
        cin >> tmpPswd;
        cin.sync();
        if (tmpPswd != self_password) {
            puts("Wrong Password. Please re-enter this mode to try again.");
            return false;
        }
        printf("Enter the new_password : ");
        cin >> tmpPswd;
        cin.sync();
        printf("Enter the new_password Again : ");
        cin >> new_password;
        cin.sync();
        if (new_password != tmpPswd) {
            puts("Not the same new_password. Please try again.");
            return false;
        }
        self_password = new_password;
        try {
            usrLib->change_password(self_UserName, new_password);
            printf("Your password has been changed to [%s] successfully.\n", new_password.c_str());
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
        return true;
    }
};

class Admin_Group : public Users {
  public:
    void query_All_Users() {
        usrLib->List_all_Users();
    }

    bool create_new_User() {
        std::string userName;
        std::string password;
        printf("Enter the UserName : ");
        cin >> userName;
        cin.sync();
        printf("Enter the password : ");
        cin >> password;
        cin.sync();

        printf("The new Normal_User userName is [%s], password : [%s]. type 'y' to register, other to cancel. ",
               userName.c_str(), password.c_str());
        char c;
        cin >> c;
        cin.sync();
        if (c == 'y')
            return usrLib->add_new_User(userName, password);
        else
            return false;
    }
    bool delete_one_User() {
        string usr_toDel;
        printf("Enter the Name of the to_delete User : ");
        cin >> usr_toDel;
        cin.sync();
        return usrLib->delete_one_User(usr_toDel);
    }

    int create_new_book() {
        struct BookInfo tmpBkInfo;
        tmpBkInfo.input();
        int num;
        printf("Enter the Num of the new book : ");
        cin >> num;
        cin.sync();
        try {
            bookLib->create_new_book(tmpBkInfo, num);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
        printf("[%s] has been uploaded, with num [%d].\n", tmpBkInfo.Name.c_str(), num);
        return 0;
    }
    int remove_one_book() {
        int index;
        printf("Enter the index of the to_del book : ");
        cin >> index;
        cin.sync();
        string bkName, bkISBN;
        bkName = bookLib->getBookName_byIndex(index);
        bkISBN = bookLib->getBookISBN_byIndex(index);
        try {
            bookLib->delete_one_book(index);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
        printf("[%s] (with ISBN [%s]) has been removed.\n", bkName.c_str(), bkISBN.c_str());
        return 0;
    }
    int add_bookNum() {
        int index, num;
        printf("Enter the index of the target book : ");
        cin >> index;
        cin.sync();
        printf("Enter the num of the target book : ");
        cin >> num;
        cin.sync();
        int ret = -1;
        try {
            ret = bookLib->add_one_bookNum(index, num);
            printf("the Book Num has been changed to %d\n", ret);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
        return ret;
    }
    int sub_bookNum() {
        int index, num;
        printf("Enter the index of the target book : ");
        cin >> index;
        printf("Enter the num of the target book : ");
        cin >> num;
        cin.sync();
        int ret = -1;
        try {
            ret = bookLib->sub_one_bookNum(index, num);
            printf("the Book Num has been changed to %d\n", ret);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
        return ret;
    }

};

class Root_User : public Admin_Group {
  public:
    void query_All_Admins() {
        usrLib->List_all_Admins();
    }
    bool create_new_Admin() {
        std::string userName;
        std::string password;
        printf("Enter the UserName : ");
        cin >> userName;
        cin.sync();
        printf("Enter the password : ");
        cin >> password;
        cin.sync();

        printf("The new userName is [%s], password : [%s]. type 'y' to register, other to cancel. ",
               userName.c_str(), password.c_str());
        char c;
        cin >> c;
        cin.sync();
        if (c == 'y')
            return usrLib->add_new_User(userName, password, 1);
        else
            return false;
    }
    bool delete_one_Admin() {
        string usr_toDel;
        printf("Enter the Name of the to_delete Admin: ");
        cin >> usr_toDel;
        cin.sync();
        return usrLib->delete_one_User(usr_toDel);
    }
};

class Admin_User : public Admin_Group {
  public:
    void help_Users_givback() {
        string userName, bkISBN, bkName;
        printf("Enter the Normal_User's userName : ");
        cin >> userName;
        cin.sync();
        try {
            int userIndex = usrLib->search_one_User(userName);
            string usrGroup = usrLib->get_Group(userIndex);
            if (usrGroup != string("Users")) throw UserGroupError();
            cout << "usrGroup check" << endl;
            usrLib->List_One_BookBorrowing(userIndex);
            printf("Enter the ISBN of the given_back book : ");
            cin >> bkISBN;
            cin.sync();
            int bkIndex = bookLib->search_book_byISBN(bkISBN);
            bkName = bookLib->getBookName_byIndex(bkIndex);
            cout << "bkName check" << endl;

            bookLib->back_one_book(bkIndex, userName);
            usrLib->append_bw_gb_Turnovers_to_Users(1, bkName, bkISBN, userName);
            usrLib->remove_one_BookBorrowing(usrLib->search_one_User(userName), bkISBN);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
    void help_Users_brwout() {
        string userName, bkISBN, bkName;
        printf("Enter the Normal_User's userName : ");
        cin >> userName;
        cin.sync();
        try {
            int userIndex = usrLib->search_one_User(userName);
            std::string usrGroup = usrLib->get_Group(userIndex);
            if (usrGroup != string("Users")) throw UserGroupError();
            printf("Enter the INDEX of the to_borrow book : ");
            int bkIndex;
            cin >> bkIndex;
            cin.sync();
            int time_long;
            printf("Enter the TIME_LONG you want to borrow : ");
            cin >> time_long;
            cin.sync();
            bkName = bookLib->getBookName_byIndex(bkIndex);
            bkISBN = bookLib->getBookISBN_byIndex(bkIndex);

            bookLib->borrow_one_book(bkIndex, userName);
            usrLib->append_bw_gb_Turnovers_to_Users(0, bkName, bkISBN, userName, time_long);
            usrLib->add_one_BookBorrowing(usrLib->search_one_User(userName), bkISBN);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
    void setRejected_to_Users() {
        string rej_userName;
        printf("Enter the Name of the target Normal_User : ");
        cin >> rej_userName;
        try {
            usrLib->set_normalUser_rejected(rej_userName);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
    void setUNrejected_to_Users() {
        string rej_userName;
        printf("Enter the Name of the target Normal_User : ");
        cin >> rej_userName;
        try {
            usrLib->set_normalUser_UNrejected(rej_userName);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
    void query_oneUsers_borrowing() {
        printf("Enter the Normal_User's Name to check : ");
        string userName;
        cin >> userName;
        cin.sync();
        try {
            int userIndex = usrLib->search_one_User(userName);
            usrLib->List_One_BookBorrowing(userIndex);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
};

class Normal_Users : public Users {
  public:
    void list_my_borrowingBooks() {
        try {
            int userIndex = usrLib->search_one_User(self_UserName);
            usrLib->List_One_BookBorrowing(userIndex);
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
    bool is_rejected() {
        return usrLib->is_normalUser_rejected(self_UserName);
    }
    void borrow_oneBook() {
        int index, time_long;
        printf("Enter the INDEX of the book you want to borrow : ");
        cin >> index;
        printf("Enter the TIME_LONG you want to use for (days, no more than 60) : ");
        cin >> time_long;
        cin.sync();
        bookLib->borrow_one_book(index, self_UserName, time_long);
        string bkName = bookLib->getBookName_byIndex(index);
        string bkISBN = bookLib->getBookISBN_byIndex(index);
        usrLib->append_bw_gb_Turnovers_to_Users(0, bkName, bkISBN, self_UserName, time_long);
        usrLib->add_one_BookBorrowing(usrLib->search_one_User(self_UserName), bkISBN);
        printf("Borrow book [%s] successfully.\n", bkName.c_str());
    }
    void givback_oneBook() {
        std::string bkISBN;
        printf("Enter the ISBN of the book you want to give_back : ");
        cin >> bkISBN;
        try {
            int index = bookLib->search_book_byISBN(bkISBN);
            bookLib->back_one_book(index, self_UserName);
            string bkName = bookLib->getBookName_byIndex(index);
            usrLib->append_bw_gb_Turnovers_to_Users(1, bkName, bkISBN, self_UserName);
            usrLib->remove_one_BookBorrowing(usrLib->search_one_User(self_UserName), bkISBN);
            printf("Give back book [%s] successfully.\n", bkName.c_str());
        } catch (Library_Base_Exception &e) {
            cout << e.what() << endl;
        }
    }
};
