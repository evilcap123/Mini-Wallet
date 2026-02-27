#pragma once

#include<string>


class Account{
protected:  
    std::string name;
    std::string mobile;
    double balance;

public:
    Account(std::string n="" , std::string m="", double b = 0);

    void depo(double amnt);
    bool withdraw(double amnt);

    double getBalance() const;
    std::string getMobile() const;
    std::string getName() const;

};