
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

string getCurrentTime() {
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y,%m,%d,%X,%A,%z", localtime(&t));
    string ret(tmp);
    return ret;
}

struct BIL {
    double Consumption;
    string Location;

    void input() {
        cout << "Input the Consumption & the Location , split by spaces : " << endl;
        cin >> Consumption >> Location;
    }
};

class Turnover {
    public:
        int type;  // 0 for income, 1 for payment
        string time;

        BIL bill;

        string otherCardNo;
        double ioc;  // for other cards' transfer

        double tmpBalance;

        Turnover() {}
        Turnover(int tp, BIL &bill, double tBalance) {
            type = tp;
            this->bill = bill;
            tmpBalance = tBalance;
            time = getCurrentTime();
        }  // type = 1;
        Turnover(int tp, string &other, double ioc, double tBalance) {
            type = tp;
            if (tp == 0) {
                otherCardNo = other;
                this->ioc = ioc;
            }
            if (tp == 2) {
                otherCardNo = other;
                this->ioc = ioc;
            }
            if (tp == 3) {
                otherCardNo = other;
                this->ioc = ioc;
            }
            tmpBalance = tBalance;
            time = getCurrentTime();
        }  // type = 0 or type = 2 of type = 3;

        void setTime(string Time) { time = Time; }
        void setType(int Type) { type = Type; }
        void setConsumption(int ConsumptionT) { bill.Consumption = ConsumptionT; }
        void setLocation(string LocationT) { bill.Location = LocationT; }
        void setIOcome(string otherCN, double ioc, double tmpBalance) {
            otherCardNo = otherCN;
            this->ioc = ioc;
            this->tmpBalance = tmpBalance;
        }
        void setTBalance(double tmpBalance) { this->tmpBalance = tmpBalance; }

        void print() {
            switch (type) {
                case 0:
                cout <<  time <<  " income : " << ioc << " , from : " << otherCardNo << "tempBalance : " << tmpBalance << endl;
                // printf("%s income + %lf from %s\n", time, income, otherCardInfo.cardNo);
                break;
                case 1:
                cout << time << " payment : " << bill.Consumption << " At : " << bill.Location << "tempBalance : " << tmpBalance << endl;
                // printf("%s payment - %lf at %s\n", time, consumption, location);
                break;
                case 2:
                cout << time << " outcome : " << ioc << " , to : " << otherCardNo << "tempBalance : " << tmpBalance << endl;
                break;
                case 3:
                cout << time << " Transfer to Campus_card (No.) " << otherCardNo << "Money : " << ioc  << "tempBalance : " << tmpBalance <<  endl;
            }
        }
};

class Depo_userinfo {
    public:
        string cardNo;
        string releaseDate; // yyyymmdd
        string userName;
        double balance;
        double overdraftLimit;
        vector<Turnover> turnovers;

        Depo_userinfo() { balance = 0; }
        Depo_userinfo(string No, string rlD, string usrD, double balance, double overdraftLimit) {
            cardNo = No;
            releaseDate = rlD;
            userName = usrD;
            this->balance = balance;
            this->overdraftLimit = overdraftLimit;
        }
        void setDepo(string No, string rlD, string usrD, double balance, double overdraftLimit) {
            cardNo = No;
            releaseDate = rlD;
            userName = usrD;
            this->balance = balance;
            this->overdraftLimit = overdraftLimit;
        }

        void transferToCampus(double money, string stuNo) {
            balance -= money;
            Turnover temp(3, stuNo, money, balance);
            turnovers.push_back(temp);
        }
        void income(string &other, double inc) {
            balance += inc;
            Turnover temp(2, other, inc, balance);
            turnovers.push_back(temp);
        }
        void transferMoney(string &other, double outc) {
            balance -= outc;
            Turnover temp(2, other, outc, balance);
            turnovers.push_back(temp);
        }

        void printTurnovers() {
            vector<Turnover>::iterator it;
            for (it = turnovers.begin(); it != turnovers.end(); it++)
                it->print();
        }
        void printBasisInfo() {
            cout << cardNo << " " << releaseDate << " " << userName << " balance : " << balance << " overdraftLimit : " << overdraftLimit << endl;
        }

        virtual void pay(BIL bill) {
            if (balance + overdraftLimit >= bill.Consumption) {
                balance -= bill.Consumption;
                // trans location to turnovers
                Turnover temp(1, bill, balance);
                turnovers.push_back(temp);
            }
        }

        void set(string No, string rlD, string usrD, double balance, double overdraftLimit) {
            cardNo = No;
            releaseDate = rlD;
            userName = usrD;
            this->balance = balance;
            this->overdraftLimit = overdraftLimit;
        }
        void setCardNo(string No) {
            cardNo = No;
        }
        void setReleaseDate(string rlD) {
            releaseDate = rlD;
        }
        void setUserName(string usrD) {
            userName = usrD;
        }
        void setBalance(int balance) {
            this->balance = balance;
        }
};

class card {
    public:
        virtual double pay(BIL bill) = 0;
        virtual void query(void) = 0; // return type undertermined
};

class campus_card : public card {
    public:
        double cbalance;
        string studentNo; // 8 digits
        string stuName;
        string school;
        vector<Turnover> turnovers;
        campus_card() { cbalance = 0; }

        void setCamp(string stuNo, string stuN, string sch, double balance) {
            studentNo = stuNo;
            stuName = stuN;
            school = sch;
            cbalance = balance;
        }
        void input() {
            cout << "Enter the studentNo, studentName, school: " << endl;
            cin >> studentNo >> stuName >> school;
            cout << "Successfully registered. The initial balance of the campus card is 0, and must be transferred in from the binding deposit_cards." << endl;
        }
        void printStuInfo() {
            cout << studentNo << ' ' << stuName << ' ' << school << endl << " balance : " << cbalance << endl;
        }
        void getMoneyFromDepo(double money, string otherCardNo) {
            cbalance += money;
            Turnover temp(0, otherCardNo, money, cbalance);
            turnovers.push_back(temp);
        }

        void printTurnovers() {
            vector<Turnover>::iterator it;
            for (it = turnovers.begin(); it != turnovers.end(); it++)
                it->print();
        }
        virtual double pay(BIL bill) {
            cbalance -= bill.Consumption;
            Turnover temp(1, bill, cbalance);
            turnovers.push_back(temp);
            return cbalance;
        }
        virtual void query(void) {
            int mode;
            cout << " Enter 1 for the basic information,  2 for turnovers : " << endl;
            cin >> mode;
            switch(mode) {
                case 1:
                printStuInfo();
                break;
                case 2:
                printTurnovers();
                break;
            }
        }
};

class deposit_card : public card {
    public:
        vector<Depo_userinfo> cards;
        void inputDepo_cards() {
            char choice;
            while (1) {
                string tmp_No, tmp_rlD, tmp_usrN;
                double tmp_bal, tmp_odl;
                cout << "Enter the new Deposit card's No, releaseDate, userName, balance, overdraftLimit, split by space(s) : " << endl;
                cin >> tmp_No >> tmp_rlD >> tmp_usrN >> tmp_bal >> tmp_odl;
                Depo_userinfo temp(tmp_No, tmp_rlD, tmp_usrN, tmp_bal, tmp_odl);
                cards.push_back(temp);

                cout << "Enter 'n' to exit the Deposit cards Adding, Enter any key to continue Adding : ";
                cin >> choice;
                if (choice == 'n') return;
                else continue;
            }
        }

        virtual double pay(BIL bill) {
            vector<Depo_userinfo>::iterator it;
            for (it = cards.begin(); it != cards.end(); it++) {
                if (it->balance >= bill.Consumption) {
                    it->pay(bill);
                    cout << " Successful. Pay by the card : (No.) " << it->cardNo << endl;
                    return it->balance;
                    // Turnovered in inner pay()
                }
            }
            if (it == cards.end()) {
                cout << " Try to use the Deposit_cards' overdraftLimit..." << endl;
                for (it = cards.begin(); it != cards.end(); it++) {
                    if (it->balance + it->overdraftLimit >= bill.Consumption) {
                        it->pay(bill);
                        cout << " Successful. Pay by the card : (No.) " << it->cardNo << endl;
                        return it->balance;
                        // Turnovered in inner pay()
                    }
                }
            }
            if (it == cards.end()) {
                cout << "error : Payment failed.  All the corresponding cards don't have enough balance !" << endl;
                return 0.0;
            }
        }
        virtual void printTurnovers() {
            for (vector<Depo_userinfo>::iterator it = cards.begin(); it != cards.end(); it++) {
                cout << it->cardNo << "  :  " << it->userName << " : " << endl;
                it->printTurnovers();
                cout << endl;
            }
        }
        void listDepocards() {
            for (int i = 0; i < cards.size(); i++) {
                cout << i << ' ';
                cards[i].printBasisInfo();
            }
        }
        virtual void query(void) {
            int mode;
            cout << " Enter 1 for the basic information,  2 for turnovers : " << endl;
            cin >> mode;
            switch(mode) {
                case 1:
                listDepocards();
                break;
                case 2:
                printTurnovers();
                break;
            }
        }
};

class binding_card : public campus_card, public deposit_card {
    public:
        binding_card() {}
        vector<Turnover>& CampTurns() { return campus_card::turnovers; }
        vector<Depo_userinfo>& DepoCards() { return cards; }
        virtual double pay(BIL bill) {
            if (cbalance >= bill.Consumption) {
                cout << " Pay it from Campus_card. " << endl;
                campus_card::pay(bill);
                return cbalance;
            }
            else {
                cout << "error :  Campus_card doesn't have enough balance. " << endl;
                cout << " Try to Pay it from Deposit_cards .. " << endl;
                deposit_card::pay(bill);
                return 0;
            }
        }
        virtual void query(void) {
            int mode;
            cout << "Enter 1 to list the infomation of campus_card, 2 for deposit_card : " << endl;
            cin >> mode;
            switch(mode) {
                case 1:
                campus_card::query();
                break;
                case 2:
                deposit_card::query();
                break;
            }
        }
        void transferIn() {
            for (vector<Depo_userinfo>::iterator it = cards.begin(); it != cards.end(); it++) {
                static int i = 0;
                cout << i << " ";
                it->printBasisInfo();
                i++;
            }
            cout << "Choose one card and Enter the conresponding number : ";
            int choice;
            cin >> choice;

            cout << "The chosen card's balance is : " << cards[choice].balance << endl;
            cout << "Enter the sum of money : ";
            double money;
            cin >> money;

            cards[choice].transferToCampus(money, studentNo);
            campus_card::getMoneyFromDepo(money, cards[choice].cardNo);

            cout << "Transfer Completed. " << endl;
        }
};

void readFromFiles(vector<binding_card> &cards) {
    ifstream file("info.db", ios::in);
    if (!file.is_open()) {
        cout << "info.db doesn't exist." << endl;
        return;
    }
    cout << "OPEN file succeeded." << endl;
    char mode;
    int type;
    string stuNo, stuName, school;
    double cbalance;
    double tmpBalance;

    int C_No = -1, D_No;
    string cardNo, releaseDate, userName;
    double balance, overdraftLimit;

    double Consumption;
    string time, Location;

    string otherCardNo;
    double ioc;

    while (!file.eof()) {
        binding_card Temp_c;
        Depo_userinfo Temp_d;
        Turnover Temp_t;
        file >> mode;
        // cout << "Mode = " << mode << endl;
        if (mode == 'Q') {
            file.close();
            cout << "info.db Loaded Successfully." << endl;
            return;
        }
        switch(mode) {
            case 'C':
            C_No++;
            D_No = -1;
            file >> stuNo >> stuName >> school >> cbalance;
            Temp_c.setCamp(stuNo, stuName, school, cbalance);
            cards.push_back(Temp_c);
            // stored to memory
            break;
            case 'D':
            D_No++;
            file >> cardNo >> releaseDate >> userName >> balance >> overdraftLimit;
            Temp_d.setDepo(cardNo, releaseDate, userName, balance, overdraftLimit);
            cards[C_No].cards.push_back(Temp_d);
            // stored to memory
            break;
            case 'T':
            file >> time >> type;
            if (type == 1) {
                file >> Consumption >> Location >> tmpBalance;
                Temp_t.setConsumption(Consumption);
                Temp_t.setLocation(Location);
                Temp_t.setTBalance(tmpBalance);
                // stored to turnovers, type 1
            } else {
                file >> otherCardNo >> ioc >> tmpBalance;
                Temp_t.setIOcome(otherCardNo, ioc, tmpBalance);
                // stored to turnovers, type 0, 2, 3
            }
            Temp_t.setTime(time);
            Temp_t.setType(type);
            if (D_No == -1) cards[C_No].CampTurns().push_back(Temp_t);
            else cards[C_No].cards[D_No].turnovers.push_back(Temp_t);
            break;
        }
    }
    cout << "info.db loaded successfully." << endl;
    file.close();
}

void listAll(vector<binding_card> &cards) {
    for (vector<binding_card>::iterator bindit = cards.begin(); bindit != cards.end(); bindit++) {
        bindit->printStuInfo();
        bindit->campus_card::printTurnovers();
        bindit->deposit_card::printTurnovers();
        cout << endl;
    }
}

void saveToFile(vector<binding_card> &cds) {
    ofstream outpFile("infoTest.db", ios::trunc);
    for (vector<binding_card>::iterator bindit = cds.begin(); bindit != cds.end(); bindit++) {
        outpFile << "C ";
        outpFile << bindit->studentNo << ' ' << bindit->stuName << ' ' << bindit->school << ' ' << bindit->cbalance << endl;
        if (bindit->CampTurns().size() != 0) {
            for (vector<Turnover>::iterator turnit = bindit->CampTurns().begin(); turnit != bindit->CampTurns().end(); turnit++) {
                outpFile << "T ";
                outpFile << turnit->time << ' ' << turnit->type << ' ';
                if (turnit->type == 1) outpFile << turnit->bill.Consumption << ' ' << turnit->bill.Location << ' ' << turnit->tmpBalance << endl;
                else outpFile << turnit->otherCardNo << ' ' << turnit->ioc << ' ' << turnit->tmpBalance << endl;
            }
        }

        for (vector<Depo_userinfo>::iterator depoIt = bindit->DepoCards().begin(); depoIt != bindit->DepoCards().end(); depoIt++) {
            outpFile << "D ";
            outpFile << depoIt->cardNo << ' ' << depoIt->releaseDate << ' ' << depoIt->userName << ' ' << depoIt->balance << ' ' << depoIt->overdraftLimit << endl;
            for (vector<Turnover>::iterator turnit = depoIt->turnovers.begin(); turnit != depoIt->turnovers.end(); turnit++) {
                outpFile << "T ";
                outpFile << turnit->time << ' ' << turnit->type << ' ';
                if (turnit->type == 1) outpFile << turnit->bill.Consumption << ' ' << turnit->bill.Location << ' ' << turnit->tmpBalance << endl;
                else outpFile << turnit->otherCardNo << ' ' << turnit->ioc << ' ' << turnit->tmpBalance << endl;
            }
        }
        outpFile << endl;
    }
    outpFile << 'Q' << endl;
    outpFile.close();
}

int main() {
    cout << "Tesing FILE I/O. Start reading some file. " << endl;
    vector<binding_card> cards;
    readFromFiles(cards);
    //  read file MUST be called at the very fisrt of the program.

    cout << "Testing the functions of the class {binding_card} respectively : " << endl;
    cout << endl << "Test for the basic information's input : " << endl;
    binding_card test;
    test.input();
    test.inputDepo_cards();
    test.query();

    cout << endl << "Test for the payment. just one time." << endl;
    BIL tmpBill;
    tmpBill.input();
    test.pay(tmpBill);

    cout << endl << "Now let the Campus_card get some money from the corresponding deposit_cards." << endl;
    cout << endl << "Choose one deposit_card : " << endl;
    test.transferIn();

    cout << endl << "Now let some corresponding deposit_card get income from some other deposit_card" << endl;
    test.listDepocards();
    int choice;
    cin >> choice;
    string tmpOtherCardNo;
    cout << "Enter the otherCardNo and the sum of money, split by spaces : ";
    double ioc;
    cin >> tmpOtherCardNo >> ioc;
    test.cards[choice].income(tmpOtherCardNo, ioc);

    cout << endl << "Now let some corresponding deposit_card transferMoney() to some other deposit_card" << endl;
    test.listDepocards();
    cin >> choice;
    cout << "Enter the otherCardNo and the sum of money, split by spaces : ";
    cin >> tmpOtherCardNo >> ioc;
    test.cards[choice].transferMoney(tmpOtherCardNo, ioc);

    test.query();

    cards.push_back(test);
    listAll(cards);
    saveToFile(cards);
    return 0;
}
