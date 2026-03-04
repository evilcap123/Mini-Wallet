#include"UPIUser.h"
#include<iostream>
#include<algorithm>


UpiUser::UpiUser(std::string n, std::string m, double b , int p):Account(n , m , b), pin(p){}

bool UpiUser::verifyPin(int enteredPin) const{
    return pin==enteredPin;
}
void UpiUser::addTransaction(const Transaction& t){
    history.push_back(t);
}

void UpiUser::showHistory(int n)const{
    if(history.empty()){
        std::cout<<"No transactions yet.\n";
        return;
    }
    
    int count = (n == -1) ? history.size() : std::min(n , (int)history.size());

    int start = (int)history.size() - count;
    std::cout << "--------------------------------------------\n";
    std::cout << "Date/Time           | Type     | User       | Amount\n";
    std::cout << "--------------------------------------------\n";
    
    for(int i = start ; i< (int)history.size() ; i++){
        std::cout<< history[i].getTs()  <<" | " 
        << history[i].getType() <<" | "
        << history[i].getOtherUser()<<" | "
        << history[i].getAmount()<<" | "
        << std::endl;
    }
    std::cout<<"--------------------------------------------\n";
}

int UpiUser::getPin() const{
    return pin;
}

void UpiUser::setPin(int newPin){
    pin = newPin;
}

const std::vector<Transaction>& UpiUser::getTransaction()const{
    return history;
}