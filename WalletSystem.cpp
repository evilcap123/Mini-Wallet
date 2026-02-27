#include "WalletSystem.h"
#include<iostream>
#include "windows.h"
#include<fstream>
#include<sstream>

void WalletSys::CreateUser(){
    std::string name , mobile;
    int pin;
    double initialBalance;

    std::cout << "Enter name: ";
    std::cin>>name;
    std::cout<< "Enter mobile: ";
    std::cin>>mobile;
    std::cout <<"Set PIN: ";
    std::cin >>pin;

    std::cout<<"Enter initial Balance: ";
    std::cin>>initialBalance;

    if(initialBalance<=0){
        std::cout<<"Initial balance cannot be less than or equal to 0\n";
        return;
    }

    users.push_back(UpiUser(name , mobile , initialBalance, pin));
    std::cout <<"Wallet Created :)"<< std::endl;

   
}
 int WalletSys::findUser(const std::string& mobile) {
        for(int i =0 ; i<(int)users.size(); i++){
            if( users[i].getMobile() == mobile) return i;
            
        }
        return -1;
    }


void WalletSys::saveToFile(){
    std::ofstream fout("users.txt");

    for(const auto& u : users){
        fout<< u.getName() <<"|"
        << u.getMobile() << "|" 
        << u.getPin() << "|"
        <<u.getBalance()<<std::endl;
    }
}

void WalletSys::LoadFromFile(){
    std::ifstream fin("users.txt");

    std::string line;
    while(std::getline(fin, line)){
        if(line.empty()) continue;
        std::stringstream ss(line);
        std::string name, mobile, pinStr, balStr;
        std::getline(ss, name, '|');
        std::getline(ss, mobile, '|');
        std::getline(ss, pinStr, '|');
        std::getline(ss, balStr, '|');
        int pin = std::stoi(pinStr);
        double balance = std::stod(balStr);
        users.push_back(UpiUser(name, mobile, balance, pin));
    }
}

void WalletSys::userLogin(){
    std::string mobile_num;
    int enteredPin;

    std::cout<<"Enter mobile number: ";
    std::cin>>mobile_num;

    

    int index = findUser(mobile_num);

    if(index == -1) {
        std::cout<<"User not found!!\n";
    return;
}
    
    std::cout<<"Enter your PIN: ";
    std::cin>>enteredPin;

    if(users[index].verifyPin(enteredPin)){
        std::cout<<"Login successful! \n";
        userDashboard(index);
    }else{
        std::cout<<"Incorrect PIN :(\n";
    }
}


void WalletSys::userDashboard(int userIdx){
    int choice , pin;
    std::string userMobile = users[userIdx].getMobile();
    do{
        std::cout << "\n===== USER DASHBOARD =====\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Transfer Money\n";
        std::cout << "3. Transaction History\n";
        std::cout << "4. Logout\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;


        if(choice == 1){
            std::cout<<"Your Balance: "<<users[userIdx].getBalance()<<std::endl;
        }
        else if(choice == 2){
            std::string receiverMobile;
            double amount;

            std::cout<<"Enter receiver Mobile: ";
            std::cin>>receiverMobile;

            int receiverIdx = findUser(receiverMobile);

            if(receiverIdx==-1){
                std::cout<<"Receiver not found!!!\n";
                continue;
            }

            if(users[userIdx].getMobile() == receiverMobile){
                std::cout<<"Cannot Transfer money to yourself (duh)\n";
                continue;
            }

            
            std::cout<<"Enter amount: ";
            std::cin>>amount;

            if(amount <= 0){
                std::cout<<"Transferring amount cannot be less than or equal to 0!!\n";
                continue;
            }

            std::system("cls");
            std::cout<<"Enter your pin: ";
            std::cin>>pin;
            Sleep(3000);
            std::system("cls");

            if(!users[userIdx].verifyPin(pin)){
                std::cout<<"Incorrect pin: \n";
                continue;
            }

            if(!users[userIdx].withdraw(amount)){
                std::cout<<"Insufficient balance: !!\n";
                continue;
            }

            users[receiverIdx].depo(amount);

            users[userIdx].addTransaction(Transaction("Sent" , receiverMobile , amount));
            users[receiverIdx].addTransaction(Transaction("Received" , userMobile , amount));

            std::cout<<"Transfer Successful!!!!!\n";

            saveToFile();

        }

        else if(choice==3){
            users[userIdx].showHistory();
        }
    }while(choice!=4);
}