#include "AgendaUI.hpp"
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

void printFirstUI(void) {
    cout << endl;
    cout << "----------------------- Agenda -------------------------" << endl;
    cout << "Action :"<< endl;
    cout << "l   - log in Agenda by user name and password" << endl;
    cout << "r   - register an Agenda account" << endl;
    cout << "q   - quit Agenda" << endl;
    cout << "--------------------------------------------------------" << endl;
}

void printUserUI(void) {
    cout << endl;
    cout << "----------------------- Agenda -------------------------" << endl;
    cout << "Action :"<< endl;
    cout << "o   - log out Agenda" << endl;
    cout << "dc  - delete Agenda account" << endl;
    cout << "lu  - list all Agenda user" << endl;
    cout << "cm  - create a meeting" << endl;
    cout << "la  - list all meetings" << endl;
    cout << "las - list all sponsor meetings" << endl;
    cout << "lap - list all participate meetings" << endl;
    cout << "qm  - query meeting by title" << endl;
    cout << "qt  - query meeting by time interval" << endl;
    cout << "dm  - delete meeting by title" << endl;
    cout << "da  - delete all meetings" << endl;
    cout << "--------------------------------------------------------" << endl;
}

void printSingleUser(User t) {
    cout << setiosflags(ios::left) << setw(12) << t.getName(); 
    cout << setiosflags(ios::left) << setw(16) << t.getEmail();
    cout << setiosflags(ios::left) << setw(15) << t.getPhone() << endl;
}
void printUsers(std::list<User> tmp) {
    cout << setiosflags(ios::left) << setw(12) << "name" << setw(16) << "email"
        << setw(15) << "phone" << endl;
    for (auto each : tmp)
        printSingleUser(each);
}
void printSingleMeeting(Meeting &t) {
    cout << setiosflags(ios::left) << setw(15) << t.getTitle();
    cout << setiosflags(ios::left) << setw(12) << t.getSponsor();
    cout << setiosflags(ios::left) << setw(18) <<
        Date::dateToString(t.getStartDate());
    cout << setiosflags(ios::left) << setw(18) <<
        Date::dateToString(t.getEndDate());
    std::ostringstream ostr;
    for (auto each : t.getParticipator()) ostr << each << ",";
    cout << ostr.str().substr(0, ostr.str().size() - 1) << endl;
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    cout << setiosflags(ios::left) << setw(15) << "title";
    cout << setiosflags(ios::left) << setw(12) << "sponsor";
    cout << setiosflags(ios::left) << setw(18) << "start time";
    cout << setiosflags(ios::left) << setw(18) << "end time";
    cout << setiosflags(ios::left) << "participators" << endl;
    for (auto each: t_meetings) printSingleMeeting(each);
}


AgendaUI::AgendaUI() {
    m_userName = "";
    m_userPassword = "";
}

void AgendaUI::OperationLoop(void) {
    startAgenda();
    string t_operation;
    bool quit = false;
    while (!quit) {
        quit = false;
        if (m_userName == "" && m_userPassword == "") {
            printFirstUI();
            cout << endl << "Agenda : ~$ ";
            t_operation = getOperation();
            if (t_operation == "q") quit = true;
            if (t_operation == "l") userLogIn();
            if (t_operation == "r") userRegister();
        } else {
            printUserUI();
            cout << endl << "Agenda@" << m_userName << " : # ";
            quit = executeOperation(getOperation());
        }
    }
}
// cin.ignore(numeric_limits::max(), '\n');
// cin.clear();

void AgendaUI::startAgenda(void) {
    m_agendaService.startAgenda();
}

void AgendaUI::quitAgenda(void) {
    m_agendaService.quitAgenda();
}

std::string AgendaUI::getOperation() {
    string op;
    getline(cin, op);
    cin.clear();
    return op;
}

bool AgendaUI::executeOperation(std::string t_operation) {
    if (t_operation == "o") {
        m_userName = "";
        m_userPassword = "";
    }
    if (t_operation == "dc") deleteUser();
    if (t_operation == "lu") listAllUsers();
    if (t_operation == "cm") createMeeting();
    if (t_operation == "la") listAllMeetings();
    if (t_operation == "las") listAllSponsorMeetings();
    if (t_operation == "lap") listAllParticipateMeetings();
    if (t_operation == "qm") queryMeetingByTitle();
    if (t_operation == "qt") queryMeetingByTimeInterval();
    if (t_operation == "dm") deleteMeetingByTitle();
    if (t_operation == "da") deleteAllMeetings();
    return false;
}

void AgendaUI::userLogIn(void) {
    try {
        cout << "[log in] [user name] [password]" << endl;
        cout << "[log in] ";
        string op = getOperation();
        int splitIndex;
        if ((splitIndex = op.find(' ')) == string::npos) throw 0;
        if (!((op.find('&') == string::npos) &&
            (op.find('\"') == string::npos) &&
            (op.find(',') == string::npos))) throw 0;
        if (m_agendaService.userLogIn(op.substr(0, splitIndex),
            op.substr(splitIndex + 1, op.size() - splitIndex - 1))) {
            m_userName = op.substr(0, splitIndex);
            m_userPassword = op.substr(splitIndex + 1,
                op.size() - splitIndex - 1);
            cout << "[log in] succeed!" << endl;
            return;
        }
        throw 0;
    }
    catch (...) {
        m_userName = "";
        m_userPassword = "";
        cout << "[error] log in fail!" << endl << endl;
    }
}

void AgendaUI::userRegister(void) {
    try {
        cout << "[register] [user name] [password] [email] [phone]" << endl;
        cout << "[register] ";
        string op = getOperation();
        if (!((op.find('&') == string::npos) &&
            (op.find('"') == string::npos) &&
            (op.find(',') == string::npos))) throw 0;
        int k = 0, splitIndex[10];
        for (auto it = op.begin(); it != op.end(); it++)
            if (' ' == *it) splitIndex[k++] = it - op.begin();
        if (k != 3) throw 0;
        if (m_agendaService.userRegister(op.substr(0, splitIndex[0]),
            op.substr(splitIndex[0] + 1, splitIndex[1] - splitIndex[0] - 1),
            op.substr(splitIndex[1] + 1, splitIndex[2] - splitIndex[1] - 1),
            op.substr(splitIndex[2] + 1, op.size() - splitIndex[2] - 1))) {
            cout << "[register] succeed!" << endl;
            return;
        }
        throw 0;
    }
    catch (...) {
        cout << "[error] register fail!" << endl << endl;
    }    
}

void AgendaUI::userLogOut(void) {
    m_userName = "";
    m_userPassword = "";
}

void AgendaUI::deleteUser(void) {
    if (m_agendaService.deleteUser(m_userName, m_userPassword))
        cout << "[delete agenda account] succeed!" << endl << endl;
    else
        cout << "[Unknown error] delete failed." << endl << endl;
}

void AgendaUI::listAllUsers(void) {
    cout << "[list all users]" << endl << endl;
    printUsers(m_agendaService.listAllUsers());
}

void AgendaUI::createMeeting(void) {
    cout << "[create meeting] [the number of participators]" << endl;
    cout << "[create meeting] ";
    try {
        int num;
        cin >> num;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::vector<std::string> tmp_partis;
        for (int i = 0; i < num; i++) {
            cout << "[create meeting] [please enter the participator "
                << i + 1 << " ]" << endl;
            cout << "[create meeting] ";
            string partner;
            cin >> partner;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!((partner.find('&') == string::npos) &&
                (partner.find('"') == string::npos) &&
                (partner.find(',') == string::npos))) throw 0;
            tmp_partis.push_back(partner);
        }
        cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] " <<
            "[end time(yyyy-mm-dd/hh:mm)]" << endl;
        cout << "[create meeting] ";
        string opp = getOperation();
        if (!((opp.find('&') == string::npos) &&
            (opp.find('"') == string::npos) &&
            (opp.find(',') == string::npos))) throw 0;
        int k = 0, splitIndex[10];
        for (auto it = opp.begin(); it != opp.end(); it++)
            if (' ' == *it) splitIndex[k++] = it - opp.begin();
        if (k != 2) throw 0;
        string startDate(opp.substr(splitIndex[0] + 1,
            splitIndex[1] - splitIndex[0] - 1));
        string endDate(opp.substr(splitIndex[1] + 1,
            opp.size() - splitIndex[1] - 1));
        string t_title(opp.substr(0, splitIndex[0]));
        if (m_agendaService.createMeeting(m_userName, t_title,
            startDate, endDate, tmp_partis))
            cout << "[create meeting] succeed!" << endl << endl;
        else
            throw 0;
    }
    catch (...) {
        cout << "[create meeting] error!" << endl << endl;
    }
}

void AgendaUI::listAllMeetings(void) {
    cout << "[list all meetings]" << endl << endl;
    printMeetings(m_agendaService.listAllMeetings(m_userName));
}

void AgendaUI::listAllSponsorMeetings(void) {
    cout << "[list all sponsor meetings]" << endl << endl;
    printMeetings(m_agendaService.listAllSponsorMeetings(m_userName));
}

void AgendaUI::listAllParticipateMeetings(void) {
    cout << "[list all participator meetings]" << endl << endl;
    printMeetings(m_agendaService.listAllParticipateMeetings(m_userName));
}

void AgendaUI::queryMeetingByTitle(void) {
    cout << "[query meeting] [title]:" << endl;
    cout << "[query meeting] ";
    std::string t_title;
    cin >> t_title;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    printMeetings(m_agendaService.meetingQuery(m_userName, t_title));
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] " <<
        "[end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meetings] ";
    string t_startDate, t_endDate;
    cin >> t_startDate >> t_endDate;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    printMeetings(m_agendaService.meetingQuery(m_userName,
        t_startDate, t_endDate));
}

void AgendaUI::deleteMeetingByTitle(void) {
    cout << endl << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    string del_title;
    cin >> del_title;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (m_agendaService.deleteMeeting(m_userName, del_title))
        cout << "[delete meeting by title] succeed!" << endl << endl;
    else
        cout << "[error] delete meeting fail!" << endl << endl;
}

void AgendaUI::deleteAllMeetings(void) {
    m_agendaService.deleteAllMeetings(m_userName);
    cout << endl << "[delete all meetings] succeed!" << endl << endl;
}

