#include "WalletSystem.h"
#include<iostream>
#include<fstream>

void WalletSys::CreateUser(){
    std::string name , mobile;
    int pin;

    std::cout << "Enter name: ";
    std::cin>>name;
    std::cout<< "Enter mobile: ";
    std::cin>>mobile;
    std::cout <<"Set PIN: ";
    std::cin >>pin;

    users.push_back(UpiUser(name , mobile , pin , 0));
    std::cout <<"Wallet Create :)"<< std::endl;

   
}
 int WalletSys::findUser(const std::string& mobile) {
        for(int i =0 ; i<users.size(); i++){
            if( users[i].getMobile() == mobile) return i;
            
        }
        return -1;
    }


void WalletSys::saveToFile(){
    std::ofstream fout("users.txt");

    for(const auto& u : users){
        fout<< u.getName() <<" "
        << u.getMobile() << " " 
        << u.getPin() << " "
        <<u.getBalance()<<std::endl;
    }
}

void WalletSys::LoadFromFile(){
    std::ifstream fin("users.txt");

    std::string name , mobile;
    int pin;
    double balance;

    while(fin>>name>>mobile>>pin>>balance){
        users.push_back(UpiUser(name , mobile , balance , pin));
    }
}