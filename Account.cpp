#include "Account.h"
#include<iostream>
Account::Account(std::string n , std::string m , double b): name(n) , mobile(m) , balance(b){}


bool Account::depo(double amnt){
    if(amnt>0) {
        balance+=amnt;
        return true;
}
    else {
        std::cout<<"Deposit amount cannot be less than 0\n";
        return false;
}
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
