#include "AgendaService.hpp"
#include <algorithm>

#include <iostream>
using namespace std;

AgendaService::AgendaService() {
    m_storage = Storage::getInstance();
}

AgendaService::~AgendaService() {
    m_storage->sync();
}

bool AgendaService::userLogIn(const std::string userName,
    const std::string password) {
    std::list<User> ret = m_storage->queryUser([=](const User &t) {
        return userName == t.getName() && password == t.getPassword();
    });
    return !ret.empty();
}

bool AgendaService::userRegister(const std::string userName, const std::string
    password, const std::string email, const std::string phone) {
    std::list<User> ret = m_storage->queryUser([=](const User &t) {
        return userName == t.getName();
    });
    if (!ret.empty()) return false;
    m_storage->createUser(User(userName, password, email, phone));
    return true;
}

bool AgendaService::deleteUser(const std::string userName, const std::string password) {
    try {
        cout << "checking User exist and its password..." << endl;
        std::list<User> ret = m_storage->queryUser([=](const User &t) {
            return userName == t.getName() && password == t.getPassword();
        });
        if (ret.empty()) return false;
        cout << "User exist OK" << endl;
        cout << "search for toDelMeetings by Title ..." << endl;
        std::list<Meeting> toDelMeetings = listAllMeetings(userName);
        for (auto f : toDelMeetings) cout << f.getTitle() << endl;
        cout << " all printed out ." << endl;
        cout << "start deleting the User" << endl;
        int r = m_storage->deleteUser([=](const User &t) {
            return ret.front().getName() == t.getName();
        });
        cout << "delete User OK" << endl;
        m_storage->deleteMeeting([=](const Meeting &m) {
            for (auto each : toDelMeetings)
                if (each.getTitle() == m.getTitle()) return true;
            return false;
            });
        cout << "delete Meeting OK " << endl;
        return r ? true : false;
    }
    catch (...) {
        return false;
    }
}
 
std::list<User> AgendaService::listAllUsers(void) const {
    return m_storage->queryUser([](const User &t) {
        return true;
    });
}

bool AgendaService::createMeeting(const std::string userName,
    const std::string title, const std::string startDate,
    const std::string endDate, const std::vector<std::string> participator) {
//  cout << "start cheking User exist ..." << endl;
    std::list<User> ret = m_storage->queryUser([=](const User &t) {
        return userName == t.getName();
    });
    if (ret.empty()) return false;
//  cout << "check User exist   OK" << endl;
    // query for time
//  cout << "start checking Time base Legal ...." << endl;
    Date stD = Date::stringToDate(startDate);
    Date enD = Date::stringToDate(endDate);
    cout << Date::isValid(stD) << Date::isValid(enD) << (stD < enD) << endl;
    if (!(Date::isValid(stD) && Date::isValid(enD) &&
        stD < enD)) return false;
//  cout << "check Time basic Legal  OK" << endl;
    // query for pre-exist title
//  cout << "start checking pre-exist title ..." << endl;
    std::list<Meeting> ret_M = m_storage->queryMeeting([=](const Meeting &m) {
        return title == m.getTitle();
    });
    if (!ret_M.empty()) return false;
//  cout << "check pre-exist title OK" << endl;
    // query for all-participator exists
//  cout << "start checking all participators exist ..." << endl;
    for (auto eachName : participator)
        if (eachName == userName) return false;
    ret.clear();
    ret = m_storage->queryUser([=](const User &t) -> bool {
        if (userName == t.getName()) return true;
        for (auto eachName2 : participator)
            if (eachName2 == t.getName()) return true;
        return false;
    });
    if (ret.size() != participator.size() + 1) return false;
//  cout << "check all participators exist  OK" << endl;
//  cout << "start checking all participators time ..." << endl;
    for (auto it : ret)
        for (auto co_meeting : listAllMeetings(it.getName()))
            if ((stD < co_meeting.getEndDate()) &&
                (enD > co_meeting.getStartDate())) return false;
//  cout << "check all participators time   OK" << endl;
    m_storage->createMeeting(Meeting(userName, participator, stD,
        enD, title));
//  cout << "create done" << endl;
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
    const std::string title) const {
    return m_storage->queryMeeting([=](const Meeting &m) -> bool {
        if (title != m.getTitle()) return false;
        if (userName == m.getSponsor()) return true;
        for (auto eachName : m.getParticipator())
            if (eachName == userName) return true;
        return false;
    });
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
    const std::string startDate, const std::string endDate) const {
    try {
        std::list<User> ret = m_storage->queryUser([=](const User &t) {
            return userName == t.getName();
        });
        if (ret.empty()) throw 0; 
        Date stD = Date::stringToDate(startDate);
        Date enD = Date::stringToDate(endDate);
        if (!(Date::isValid(stD) && Date::isValid(enD) &&
            stD < enD)) throw 0;
        std::list<Meeting> corre_Meetings = listAllMeetings(userName);
        std::list<Meeting> ret_Meetings;
        for (auto each : corre_Meetings)
            if ((stD <= each.getEndDate()) && (enD >= each.getStartDate()))
                ret_Meetings.push_back(each);
        return ret_Meetings;
    }
    catch (...) {
        return std::list<Meeting>();  // ?????
    }
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string userName)
    const {
    std::list<User> ret = m_storage->queryUser([=](const User &t) {
        return userName == t.getName();
    });
    if (ret.empty()) return std::list<Meeting>(); 
    return m_storage->queryMeeting([=](const Meeting &m) -> bool {
        if (m.getSponsor() == userName) return true;
        for (auto each : m.getParticipator())
            if (each == userName) return true;
        return false;
    });
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string
    userName) const {
    return m_storage->queryMeeting([=](const Meeting &m) {
        return userName == m.getSponsor();
    });
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string
    userName) const {
    return m_storage->queryMeeting([=](const Meeting &m) -> bool {
        for (auto each : m.getParticipator())
            if (userName == each && userName != m.getSponsor()) return true;
        return false;
    });
}

bool AgendaService::deleteMeeting(const std::string userName, const std::string
    title) {
    return m_storage->deleteMeeting([=](const Meeting &m) {
        return m.getSponsor() == userName && m.getTitle() == title;
    }) ? true : false;
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
    return m_storage->deleteMeeting([=](const Meeting &m) {
        return m.getSponsor() == userName;
    }) ? true : false;
}

void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    m_storage->sync();
}

