#include <cstdio>
#include <stdexcept>
#include "Date.hpp"

#include <iostream>
#include <cstdio>

using namespace std;

static int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
    m_year = m_month = m_day = m_hour = m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
    m_year = t_year;
    m_month = t_month;
    m_day = t_day;
    m_hour = t_hour;
    m_minute = t_minute;
}

Date::Date(std::string dateString) {
    *this = stringToDate(dateString);
}

int Date::getYear(void) const {
    return m_year;
}
void Date::setYear(const int t_year) {
    this->m_year = t_year;
}

int Date::getMonth(void) const {
    return m_month;
}
void Date::setMonth(const int t_month) {
    this->m_month = t_month;
}

int Date::getDay(void) const {
    return m_day;
}
void Date::setDay(const int t_day) {
    this->m_day = t_day;
}

int Date::getHour(void) const {
    return m_hour;
}
void Date::setHour(const int t_hour) {
    this->m_hour = t_hour;
}

int Date::getMinute(void) const {
    return m_minute;
}
void Date::setMinute(const int t_minute) {
    this->m_minute = t_minute;
}

bool isLeapYear(const int yyyy) {
    return (yyyy % 400 == 0) || (yyyy % 100 != 0 && yyyy % 4 == 0);
}

bool Date::isValid(const Date t_date) {
    monthDays[2] = 28;
    if (t_date.getYear() < 1000 || t_date.getYear() > 9999) return false;
    if (isLeapYear(t_date.getYear())) monthDays[2] = 29;
    if (t_date.getMonth() < 1 || t_date.getMonth() > 12) return false;
    if (t_date.getDay() < 1  || t_date.getDay() > monthDays[t_date.getMonth()])
        return false;
    if (t_date.getHour() < 0 || t_date.getHour() > 23) return false;
    if (t_date.getMinute() < 0 || t_date.getMinute() > 59) return false;
    return true;
}

static bool isNumber(const std::string str) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] < '0' || str[i] > '9') return false;
    return true;
}

Date Date::stringToDate(const std::string t_dateString) {
    if (t_dateString.length() != 16) return Date(0, 0, 0, 0, 0);
    if (!(t_dateString[4] == '-' && t_dateString[7] == '-' &&
        t_dateString[10] == '/' && t_dateString[13] == ':'))
        return Date(0, 0, 0, 0, 0);
    try {
        if (!(isNumber(t_dateString.substr(0, 4)) &&
            isNumber(t_dateString.substr(5, 2)) &&
            isNumber(t_dateString.substr(8, 2)) &&
            isNumber(t_dateString.substr(11, 2)) &&
            isNumber(t_dateString.substr(14, 2)))) throw 0;
        return Date(stoi(t_dateString.substr(0, 4)),
            stoi(t_dateString.substr(5, 2)),
            stoi(t_dateString.substr(8, 2)), stoi(t_dateString.substr(11, 2)),
            stoi(t_dateString.substr(14, 2)));
    }
    catch(...) {
        return Date(0, 0, 0, 0, 0);
    }
}

std::string Date::dateToString(Date t_date) {
    char t_ret[17];
    if (Date::isValid(t_date))
        snprintf(t_ret, sizeof(t_ret), "%04d-%02d-%02d/%02d:%02d",
            t_date.getYear(),
            t_date.getMonth(), t_date.getDay(), t_date.getHour(),
            t_date.getMinute());
    else
        snprintf(t_ret, sizeof(t_ret), "0000-00-00/00:00");
    return std::string(t_ret);
}

Date &Date::operator=(const Date &t_date) {
    this->m_year = t_date.getYear();
    this->m_month = t_date.getMonth();
    this->m_day = t_date.getDay();
    this->m_hour = t_date.getHour();
    this->m_minute = t_date.getMinute();
    return *this;
}

bool Date::operator== (const Date &t_date) const {
    return (m_year == t_date.getYear()) && (m_month == t_date.getMonth()) &&
        (m_day == t_date.getDay()) && (m_hour == t_date.getHour()) &&
        (m_minute == t_date.getMinute());
}

bool Date::operator> (const Date &t_date) const {
    return dateToString(*this) > dateToString(t_date);
}

bool Date::operator< (const Date &t_date) const {
    return !(((*this) == t_date) || ((*this) > t_date));
}

bool Date::operator>= (const Date &t_date) const {
    return ((*this) > t_date) || ((*this) == t_date);
}

bool Date::operator<= (const Date &t_date) const {
    return !((*this) > t_date);
}

