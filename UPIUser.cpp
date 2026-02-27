#include"UPIUser.h"
#include<iostream>


UpiUser::UpiUser(std::string n, std::string m, double b , int p):Account(n , m , b), pin(p){}

bool UpiUser::verifyPin(int enteredPin) const{
    return pin==enteredPin;
}
void UpiUser::addTransaction(const Transaction& t){
    history.push_back(t);
}

void UpiUser::showHistory()const{
    for(const auto& t : history){
        std::cout<< t.type <<" | " << t.otherUser <<" | "<< t.amount << std::endl;
    }
}

int UpiUser::getPin() const{
    return pin;
}