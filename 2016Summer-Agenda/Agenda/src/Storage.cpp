#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>

std::shared_ptr<Storage> Storage::m_instance = nullptr;

Storage::Storage():m_dirty(false) {
    readFromFile();
}

bool Storage::readFromFile(void) {
    std::ifstream userIn(Path::userPath);
    std::ifstream meetingIn(Path::meetingPath);
    if (userIn.fail() || meetingIn.fail()) return false;
    std::string line;
    int commaIndex[4], k;
    while (std::getline(userIn, line)) {
        k = 0;
        for (auto it = line.begin(); it != line.end(); it++)
            if (',' == *it) commaIndex[k++] = it - line.begin();
        m_userList.push_back(User(line.substr(1, commaIndex[0] - 2),
            line.substr(commaIndex[0] + 2, commaIndex[1] - commaIndex[0] - 3),
            line.substr(commaIndex[1] + 2, commaIndex[2] - commaIndex[1] - 3),
            line.substr(commaIndex[2] + 2, line.size() - commaIndex[2] - 3)));
    }
    std::string str_partis;
    while (std::getline(meetingIn, line)) {
        k = 0;
        for (auto it = line.begin(); it != line.end(); it++)
            if (',' == *it) commaIndex[k++] = it - line.begin();
        std::vector<std::string> tmp_partis;
        Meeting tmpMeeting(line.substr(1, commaIndex[0] - 2),
            tmp_partis,
            line.substr(commaIndex[1] + 2, commaIndex[2] - commaIndex[1] - 3),
            line.substr(commaIndex[2] + 2, commaIndex[3] - commaIndex[2] - 3),
            line.substr(commaIndex[3] + 2, line.size() - commaIndex[3] - 3));
        str_partis = line.substr(commaIndex[0] + 2,
            commaIndex[1] - commaIndex[0] - 3);
        int lastIndex = -1;
        for (int i = 0; i < str_partis.size(); i++)
            if ('&' == str_partis[i]) {
                tmp_partis.push_back(str_partis.substr(lastIndex + 1,
                    i - lastIndex - 1));
                lastIndex = i;
            }
        tmp_partis.push_back(str_partis.substr(lastIndex + 1,
            str_partis.size() - lastIndex - 1));
        tmpMeeting.setParticipator(tmp_partis);
        m_meetingList.push_back(tmpMeeting);
    }
    userIn.close();
    meetingIn.close();
    m_dirty = false;
    return true;
}

bool Storage::writeToFile(void) {
    try {
        if (!m_dirty) return true;
        std::ofstream userOut(Path::userPath, std::ios::trunc);
        std::ofstream meetingOut(Path::meetingPath, std::ios::trunc);
        if (userOut.fail() || meetingOut.fail()) return false;
        for (auto &each : m_userList)
            userOut << "\"" << each.getName() << "\"" << "," << "\""
                << each.getPassword() << "\"" << "," << "\"" << each.getEmail()
                << "\"" << "," << "\"" << each.getPhone() << "\"" << std::endl;
        std::string outPartis;
        for (auto each : m_meetingList) {
            meetingOut << "\"" << each.getSponsor() << "\"" << "," << "\"";
            outPartis = "";
            for (auto eachparti : each.getParticipator()) outPartis += eachparti + "&";
            meetingOut << outPartis.substr(0, outPartis.size() - 1) + "\",\""
                << Date::dateToString(each.getStartDate()) + "\",\""
                << Date::dateToString(each.getEndDate())
                << "\",\"" + each.getTitle() << "\"" << std::endl;
        }
        userOut.close();
        meetingOut.close();
        m_dirty = false;
        return true;
    }
    catch (...) {
        return false;
    }
}
// Path::userPath
// Path::meetingPath

std::shared_ptr<Storage> Storage::getInstance(void) {
    if (m_instance == nullptr)
        m_instance = std::shared_ptr<Storage>(new Storage());
    return m_instance;
}

Storage::~Storage() {
    sync();
    Storage::m_instance = nullptr;
}
// writeToFile() or sync();

void Storage::createUser(const User & t_user) {
    m_userList.push_back(t_user);
    m_dirty = true;
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter)
    const {
    std::list<User> ret;
    for (auto &each : m_userList)
        if (filter(each)) ret.push_back(each);
    return ret;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
    std::function<void(User &)> switcher) {
    int ret_num = 0;
    for (auto &each : m_userList)
        if (filter(each)) {
            switcher(each);
            ret_num++;
            m_dirty = true;
        }
    return ret_num;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int del_num = 0;
    for (auto it = m_userList.begin(); it != m_userList.end();)
        if (filter(*it)) {
            it = m_userList.erase(it);
            del_num++;
            m_dirty = true;
        }
        else
            it++;
    return del_num;
}

void Storage::createMeeting(const Meeting & t_meeting) {
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)>
    filter) const {
    std::list<Meeting> ret;
    for (auto &each : m_meetingList)
        if (filter(each)) ret.push_back(each);
    return ret;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
    std::function<void(Meeting &)> switcher) {
    int up_num = 0;
    for (auto &each : m_meetingList)
        if (filter(each)) {
            switcher(each);
            up_num++;
            m_dirty = true;
        }
    return up_num;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int del_num = 0;
    for (auto it = m_meetingList.begin(); it != m_meetingList.end();)
        if (filter(*it)) {
            it = m_meetingList.erase(it);
            del_num++;
            m_dirty = true;
        } else {
            it++;
        }
    return del_num;
}

bool Storage::sync(void) {
    if (m_dirty) return writeToFile();
    return true;
}

