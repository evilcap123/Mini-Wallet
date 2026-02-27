#include "Account.h"

Account::Account(std::string n , std::string m , double b): name(n) , mobile(m) , balance(b){}


void Account::depo(double amnt){
    if(amnt>0) balance+=amnt;
}

bool Account::withdraw(double amnt){
    if(amnt > balance || amnt <= 0) return false;

    balance-=amnt;
    return true;
}

double Account::getBalance()const{
    return balance;
}

std::string Account::getName()const{
    return name;
}

std::string Account::getMobile()const{
    return mobile;
}
