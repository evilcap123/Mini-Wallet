#include "WalletSystem.h"
#include <iostream>
#include <limits>
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
        if(!(std::cin>> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Invalid input!!\n";
            continue;
        }

        if(choice == 1){
            app.CreateUser();
            app.saveToFile();
        }
        else if(choice == 2){
            app.userLogin();
        }else {
            std::cout<<"Thank you for using Mini Wallet.\n";
            break;
        }
        
    }while(choice!=3);

    return 0;
}