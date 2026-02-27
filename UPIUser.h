#pragma once
#include "Account.h"
#include "Transaction.h"
#include <vector>

class UpiUser:public Account{
private:
    int pin;
    std::vector<Transaction> history;

public:
    UpiUser(std::string n= "" , std::string m="" , double b = 0 , int p=0);

    bool verifyPin(int enteredPin) const;
    void addTransaction(const Transaction& t);
    void showHistory()const;

    int getPin()const;
};