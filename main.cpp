#include "WalletSystem.h"
#include <iostream>

int main(){
    WalletSys app;

    app.LoadFromFile();

    int choice;

    do{
        std::cout<< "\n====== MINI WALLET ======\n";
        std::cout<< "1. Create Wallet\n";
        std::cout<< "2. Login\n";
        std::cout<< "3. Exit\n";
        std::cout<< "Enter choice:   ";
        std::cin>>choice;

        if(choice == 1){
            app.CreateUser();
            app.saveToFile();
        }
        else if(choice == 2){
            app.userLogin();
        }
        
    }while(choice!=3);

    return 0;
}