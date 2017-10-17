#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <json/json.h>

using namespace std;

struct BookInfo {
    std::string Name;
    std::string ISBN;
    std::string author;
    std::string release_date;

    void input() {
        string tmp;
        printf("Enter the Name : ");
        cin >> Name;
        cin.sync();
        printf("Enter the ISBN : ");
        cin >> ISBN;
        cin.sync();
        printf("Enter the author : ");
        cin >> author;
        cin.sync();
        printf("Enter the release_date : ");
        cin >> release_date;
        cin.sync();
    }
};

class Library {
  private:
    std::string fileName_;
    ifstream lib_File_;
    Json::Value lib_root_;
    Json::Reader json_reader_;
    Json::StyledWriter json_writer_;

    std::string Library_Name;
    std::string Library_Location;
    int Num_of_Types;
    int Num_of_All;
    int Num_of_InLibrary;
    int Num_of_Borrowed;
  public:
    static Json::Value createTurnover(int mode, std::string tmpTime, std::string user, int time_long = 30) {
        Json::Value ret;
        ret["op"] = mode ? string("give_back") : string("borrow_out");
        ret["time"] = tmpTime;
        ret["user"] = user;
        ret["time_long"] = mode ? -1 : time_long;
        return ret;
    }
    Library(std::string fileName) : fileName_(fileName) {
        lib_File_.open(fileName);
        if (!json_reader_.parse(lib_File_, lib_root_, false))
            throw JsonReadError();

        Library_Name = lib_root_["Library_Name"].asString();
        Library_Location = lib_root_["Library_Location"].asString();
        Num_of_Types = lib_root_["Books_Num_of_Types"].asInt();
        Num_of_InLibrary = lib_root_["Books_Num_InLibrary"].asInt();
        Num_of_All = lib_root_["Books_Num_All"].asInt();
        Num_of_Borrowed = lib_root_["Books_Num_Borrowed"].asInt();
    }
    void save_to_File() {
        if (lib_File_.is_open()) lib_File_.close();

        string data = json_writer_.write(lib_root_);
        ofstream ofs_File;
        ofs_File.open(fileName_);
        ofs_File << data;
        ofs_File.close();
        printf("Library Data have been stored successfully.\n");
    }
    ~Library() {
        if (lib_File_.is_open()) lib_File_.close();
        save_to_File();
    }

    void List_all_books() {
        printf("%4s %20s %15s %15s %15s %4s %5s\n",
               "No.", "Book Name", "book_ISBN", "author", "release_date", "Num", "InLib");
        for (int i = 0; i < Num_of_Types; i++)
            printf("%4d %20s %15s %15s %15s %4d %4d\n",
                   i,
                   lib_root_["Books"][i]["book_Name"].asString().c_str(),
                   lib_root_["Books"][i]["book_ISBN"].asString().c_str(),
                   lib_root_["Books"][i]["author"].asString().c_str(),
                   lib_root_["Books"][i]["release_date"].asString().c_str(),
                   lib_root_["Books"][i]["book_Num"].asInt(),
                   lib_root_["Books"][i]["book_inLibrary"].asInt());
    }
    void List_inLib_books() {
        printf("%4s %20s %15s %15s %15s %4s %5s\n",
               "No.", "Book Name", "book_ISBN", "author", "release_date", "Num", "InLib");
        for (int i = 0; i < Num_of_Types; i++) {
            if (lib_root_["Books"][i]["book_inLibrary"] != 0) {
                printf("%4d %20s %15s %15s %15s %4d %4d\n",
                       i,
                       lib_root_["Books"][i]["book_Name"].asString().c_str(),
                       lib_root_["Books"][i]["book_ISBN"].asString().c_str(),
                       lib_root_["Books"][i]["author"].asString().c_str(),
                       lib_root_["Books"][i]["release_date"].asString().c_str(),
                       lib_root_["Books"][i]["book_Num"].asInt(),
                       lib_root_["Books"][i]["book_inLibrary"].asInt());
            }
        }
    }

    int borrow_one_book(int index, std::string user, int time_long = 30) throw(IndexOverflow) {
        if (index >= Num_of_Types) throw IndexOverflow();
        lib_root_["Books"][index]["book_inLibrary"] = lib_root_["Books"][index]["book_inLibrary"].asInt() - 1;
        lib_root_["Books"][index]["book_Borrowed"] = lib_root_["Books"][index]["book_Borrowed"].asInt() + 1;
        lib_root_["Books_Num_InLibrary"] = --Num_of_InLibrary;
        lib_root_["Books_Num_Borrowed"] = ++Num_of_Borrowed;;
        lib_root_["Books"][index]["Turnovers"].append(createTurnover(0, getTime(), user, time_long));
        return 0;
    }
    bool back_one_book(int index, std::string user) throw(IndexOverflow) {
        if (index >= Num_of_Types) throw IndexOverflow();
        lib_root_["Books"][index]["book_inLibrary"] = lib_root_["Books"][index]["book_inLibrary"].asInt() + 1;
        lib_root_["Books"][index]["book_Borrowed"] = lib_root_["Books"][index]["book_Borrowed"].asInt() - 1;
        lib_root_["Books_Num_InLibrary"] = ++Num_of_InLibrary;
        lib_root_["Books_Num_Borrowed"] = --Num_of_Borrowed;;
        lib_root_["Books"][index]["Turnovers"].append(createTurnover(1, getTime(), user));
        return 0;
    }

    int create_new_book(struct BookInfo &bkInfo, int num) throw(ISBNDuplicated) {
        int index = search_book_byISBN(bkInfo.ISBN);
        if (index != Num_of_Types) throw ISBNDuplicated();

        lib_root_["Books_Num_All"] = Num_of_All += num;
        lib_root_["Books_Num_of_Types"] = ++Num_of_Types;
        lib_root_["Books_Num_InLibrary"] = Num_of_InLibrary += num;

        Json::Value tmpBkStatus;
        tmpBkStatus["book_Name"] = bkInfo.Name;
        tmpBkStatus["book_ISBN"] = bkInfo.ISBN;
        tmpBkStatus["author"] = bkInfo.author;
        tmpBkStatus["release_date"] = bkInfo.release_date;

        tmpBkStatus["book_Num"] = num;
        tmpBkStatus["book_inLibrary"] = num;
        tmpBkStatus["book_Borrowed"] = 0;
        // tmpBkStatus["book_Available"] = true;
        Json::Value tmpTover(Json::arrayValue);
        tmpBkStatus["Turnovers"] = tmpTover;

        lib_root_["Books"].append(tmpBkStatus);

        return 0;
    }
    int delete_one_book(int index) throw(IndexOverflow) {
        if (index >= Num_of_Types) throw IndexOverflow();
        int tmp_bookNum = lib_root_["Books"][index]["book_Num"].asInt();
        int tmp_bookInLib = lib_root_["Books"][index]["book_inLibrary"].asInt();
        int tmp_bookBorrowed = lib_root_["Books"][index]["book_Borrowed"].asInt();

        lib_root_["Books_Num_All"] = Num_of_All -= tmp_bookNum;
        lib_root_["Books_Num_of_Types"] = --Num_of_Types;
        lib_root_["Books_Num_InLibrary"] = Num_of_InLibrary -= tmp_bookInLib;
        lib_root_["Books_Num_Borrowed"] = Num_of_Borrowed -= tmp_bookBorrowed;

        Json::Value tmpRm;
        lib_root_["Books"].removeIndex(index, &tmpRm);
        return 0;
    }
    int add_one_bookNum(int index, int num) throw(BookNumInvalid) {
        int book_num = lib_root_["Books"][index]["book_Num"].asInt();
        int book_num_available = lib_root_["Books"][index]["book_inLibrary"].asInt();
        if (num < 0) throw BookNumInvalid();

        lib_root_["Books_Num_All"] = Num_of_All += num;
        lib_root_["Books_Num_InLibrary"] = Num_of_InLibrary += num;

        lib_root_["Books"][index]["book_inLibrary"] = book_num_available + num;
        lib_root_["Books"][index]["book_Num"] = book_num + num;
        return book_num + num;
    }
    int sub_one_bookNum(int index, int num) throw(BookNumInvalid) {
        int book_num = lib_root_["Books"][index]["book_Num"].asInt();
        int book_num_available = lib_root_["Books"][index]["book_inLibrary"].asInt();
        if (book_num_available < num) throw BookNumInvalid();

        lib_root_["Books_Num_All"] = Num_of_All -= num;
        lib_root_["Books_Num_InLibrary"] = Num_of_InLibrary -= num;

        lib_root_["Books"][index]["book_inLibrary"] = book_num_available - num;
        lib_root_["Books"][index]["book_Num"] = book_num - num;
        return book_num - num;
    }
    // sub_one_bookNum() is not completed, because don't know what it want to do
    int search_book_byName(std::string bkName, int* res) {
        int i, resCount;
        for (i = 0, resCount = 0; i < Num_of_Types; i++) {
            std::string tmpName = lib_root_["Books"][i]["book_Name"].asString();
            if (tmpName.find(bkName) != tmpName.npos) res[resCount++] = i;
        }
        return resCount;
    }
    int search_book_byISBN(std::string bkISBN) {
        for (int i = 0; i < Num_of_Types; i++)
            if (lib_root_["Books"][i]["book_ISBN"].asString() == bkISBN) return i;
        return Num_of_Types;
    }

    void print_CertainBooks(int *indexArray, int num) {
        if (num == 1 && indexArray[0] == Num_of_Types) {
            printf("Didn't find books with the input ISBN\n");
            return;
        }
        printf("%4s %20s %15s %15s %15s %4s %5s\n",
               "No.", "Book Name", "book_ISBN", "author", "release_date", "Num", "InLib");
        for (int i = 0; i < num; i++)
            printf("%4d %20s %15s %15s %15s %4d %4d\n",
                   indexArray[i],
                   lib_root_["Books"][indexArray[i]]["book_Name"].asString().c_str(),
                   lib_root_["Books"][indexArray[i]]["book_ISBN"].asString().c_str(),
                   lib_root_["Books"][indexArray[i]]["author"].asString().c_str(),
                   lib_root_["Books"][indexArray[i]]["release_date"].asString().c_str(),
                   lib_root_["Books"][indexArray[i]]["book_Num"].asInt(),
                   lib_root_["Books"][indexArray[i]]["book_inLibrary"].asInt());
    }
    std::string getBookName_byIndex(int index) {
        if (index >= Num_of_Types) throw IndexOverflow();
        return lib_root_["Books"][index]["book_Name"].asString();
    }
    std::string getBookISBN_byIndex(int index) {
        if (index >= Num_of_Types) throw IndexOverflow();
        return lib_root_["Books"][index]["book_ISBN"].asString();
    }
};

