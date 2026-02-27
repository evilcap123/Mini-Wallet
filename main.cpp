#include "WalletSystem.h"
#include <iostream>

int main(){
    WalletSys app;

    app.LoadFromFile();

    int choice;

    do{
        std::cout<< "\n====== MINI WALLET ======\n";
        std::cout<< "1. Create Wallet\n";
        std::cout<< "2. Exit\n";
        std::cout<< "Enter choice: ";
        std::cin>>choice;

        if(choice == 1){
            app.CreateUser();
            app.saveToFile();
        }
    }while(choice!=2);

    return 0;
}