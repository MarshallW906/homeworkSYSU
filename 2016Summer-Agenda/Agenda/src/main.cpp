#include <iostream>
#include <cstdio>
#include "AgendaService.hpp"

using namespace std;

void printSingleUser(User t) {
    cout << "------print single User info --------" << endl;
    cout << t.getName() << endl;
    cout << t.getPassword() <<endl;
    cout << t.getEmail() << endl;
    cout << t.getPhone() << endl;
}
void printUsers(std::list<User> tmp) {
    for (auto each : tmp)
        printSingleUser(each);
}

void printSingleMeeting(Meeting &t) {
    cout << "----------------print single meeting info -------------------" << endl;
    cout << t.getSponsor() << endl;
    for (auto each : t.getParticipator()) cout << each << " + ";
        cout << endl;
    cout << Date::dateToString(t.getStartDate()) << endl;
    cout << Date::dateToString(t.getEndDate()) << endl;
    cout << t.getTitle() << endl;
}

void printMeetings(std::list<Meeting> tmpm) {
    for (auto each: tmpm) printSingleMeeting(each);
}

int main() {
    std::cout << "hahaha" << std::endl;

    Date ret("2011-01-11/00:12");
    cout << Date::dateToString(ret) << endl;
    Date res("2016-01-02/01:01");
    cout << Date::dateToString(res) << endl;
    cout << (ret < res) << endl;

    // test Storage
//  shared_ptr<Storage> p = Storage::getInstance();
//  p->createUser(User("fff","fff","fff","fff"));
    // test AgendaService
    AgendaService test;
    test.startAgenda();
    std::vector<std::string> tmp_parti;
    tmp_parti.push_back("aaa");
    //tmp_parti.push_back("sfe");
//  cout <<(test.createMeeting("as", "adtle","2011-11-11/11:13",
//      "2011-11-11/11:14", tmp_parti) ? 1 : 0)<< endl;
//    printMeetings(test.listAllMeetings("sfe"));
    cout << (test.deleteUser("aaa", "12345") ? 1 : 0) << endl;
    cout << "66666666666666" << endl;
    test.quitAgenda();
    cout << 6666 << endl;
    return 0;
}

// Don't use catch stoi()!!!!

// Don't use catch stoi()!!!!
