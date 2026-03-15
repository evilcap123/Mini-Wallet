#include "WalletSystem.h"
#include<iostream>
#include <windows.h>
#include<fstream>
#include<sstream>

 int WalletSys::findUser(const std::string& mobile) {
        for(int i =0 ; i<(int)users.size(); i++){
            if( users[i].getMobile() == mobile) return i;
            
        }
        return -1;
    }

void WalletSys::CreateUser(){
    std::string name , mobile;
    int pin;
    double initialBalance;

    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin , name);
    std::cout<< "Enter mobile: ";
    std::cin>>mobile;

    if(mobile.length()!=10){
        std::cout<<"Enter a valid mobile number: \n";
        return;
    }

    bool allDigits = true;

    for(char c: mobile){
        if(!isdigit(c)){
            allDigits = false;
            break;
        }
    }
    if(!allDigits){
        std::cout<<"Mobile number must only contain digits!!!!\n";
        return;
    }

    if(findUser(mobile)!=-1){
        std::cout<<"User with this mobile number already exits: \n";
        return;
    }

    std::cout <<"Set PIN: ";
    std::cin >>pin;

    if(pin>9999 || pin<1000){
        std::cout<<"PIN must be 4 digits!! \n";
        return;
    }
    std::cout<<"Enter initial Balance: ";
    std::cin>>initialBalance;

    if(initialBalance<=0){
        std::cout<<"Initial balance cannot be less than or equal to 0\n";
        return;
    }

    users.push_back(UpiUser(name , mobile , initialBalance, pin));
    std::cout <<"Wallet Created :)"<< std::endl;

   
}

bool WalletSys::deleteUser(const std::string& mobile){
    int idx = findUser(mobile);
    if(idx == -1){
        std::cout<<"User not found!!!\n";
        return false;
    }

    users.erase(users.begin() + idx);
    saveToFile();
    std::cout<<"User deleted Successfully.\n";
    return true;
}

void WalletSys::saveToFile(){
    std::ofstream fout("users.txt");

    for(const auto& u : users){
        fout<< u.getName() <<"|"
        << u.getMobile() << "|" 
        << u.getPin() << "|"
        <<u.getBalance()<<std::endl;
    }
    std::ofstream txnOut("transactions.txt");

for(const auto& u: users){
    for(const auto& t: u.getTransaction()){
        txnOut << u.getMobile() << "|"
               << t.getType() << "|"
               << t.getOtherUser() << "|"
               << t.getAmount() <<"|"
               << t.getTs()
               <<std::endl;
    }
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
        std::getline(ss, balStr);
        int pin = std::stoi(pinStr);
        double balance = std::stod(balStr);
        users.push_back(UpiUser(name , mobile , balance , pin));
    }
    std::ifstream txnIn("transactions.txt");
    std::string txnLine;

while(std::getline(txnIn , txnLine)){
    if(txnLine.empty()) continue;
    std::stringstream ss(txnLine);
    std::string mobile, type , otherUser , amountStr , timestamp;
    std::getline(ss , mobile,'|');
    std::getline(ss , type,'|');
    std::getline(ss , otherUser,'|');
    std::getline(ss , amountStr,'|');
    std::getline(ss , timestamp);
    double amount = std::stod(amountStr);

    int idx = findUser(mobile);
    if(idx != -1){
        users[idx].addTransaction(Transaction(type , otherUser , amount , timestamp));
    }
}
}



void WalletSys::userLogin(){
    std::string mobile_num;
    int enteredPin;
    const std::string admin_mobile_num = "16212";
    const int admin_pin = 1234;

    std::cout<<"Enter mobile number: ";
    std::cin>>mobile_num;
    std::cout<<"Enter your PIN: ";
    std::cin>>enteredPin;

    if(mobile_num == admin_mobile_num && enteredPin == admin_pin){
        std::cout<<"Admin login successful!!!\n";
        adminDashboard(-1);
        return;
    }

    int index = findUser(mobile_num);

    if(index == -1) {
        std::cout<<"User not found!!\n";
    return;
}

    

    if(users[index].verifyPin(enteredPin)){
        std::cout<<"Login successful! \n";
        userDashboard(index);
    }else{
        std::cout<<"Incorrect PIN :(\n";
    }
}


void WalletSys::userDashboard(int userIdx){
    int choice;
    


    
    do{
        std::string userMobile = users[userIdx].getMobile();
        double userBalance = users[userIdx].getBalance();
        if(userBalance<100){
            std::cout<<"Warning low Balance: Top up recommended!!!\n";
        }

        std::cout << "\n===== USER DASHBOARD =====\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Transfer Money\n";
        std::cout << "3. Transaction History\n";
        std::cout << "4. Deposit Money\n";
        std::cout << "5. Withdraw Money\n";
        std::cout << "6. Change PIN\n";
        std::cout << "7. Logout\n";
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
            int pin;
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
            users[userIdx].showHistory(5);
        }


        else if(choice == 4 || choice == 5){
            int pin;
            double amount;

            std::system("cls");
            std::cout<<"Enter your PIN: ";
            std::cin>>pin;
            Sleep(2000);

            if(!users[userIdx].verifyPin(pin)){
                std::cout<<"Incorrect PIN !!!\n";
                continue;
            }


            std::cout<<"Enter amount: ";
            std::cin>>amount;


            if(choice==4){
                if(users[userIdx].depo(amount)){
                users[userIdx].addTransaction(Transaction("Deposit", "Self", amount) );
                saveToFile();
                }
            }
            else if(choice == 5){
               if (!users[userIdx].withdraw(amount)){
                std::cout<<"Insufficient Balance!!\n";
                continue;
               }
               users[userIdx].addTransaction(Transaction("Withdraw" , "Self" , amount));
               saveToFile();
            }
        }

        else if(choice == 6){
            char ans;
            int pin, newPin;
            
            std::cout<<"Are you sure u want to change your pin(y/n): ";
            std::cin>>ans;

            switch (ans) {

            case 'y':
                std::cout<<"Enter your current PIN: ";
                std::cin>>pin;


                if(!users[userIdx].verifyPin(pin)){
                    std::cout<<"Incorrect PIN: \n";
                    continue;
                }

                std::cout<<"Enter New PIN (4 Digits Max): ";
                std::cin>>newPin;

                if(newPin>9999 || newPin<1000){
                    std::cout<<"PIN must be 4 digits!!\n";
                    continue;
                }

                users[userIdx].setPin(newPin);
                saveToFile();
                break;
            
            default:
                break;
            }
        }

        else if(choice == 7){
            char ans;
            std::cout<<"Are you sure? (y/n): ";
            std::cin>>ans;
            if(ans == 'y' || ans == 'Y'){
                return;
            }
            else if(ans == 'n' || ans == 'N'){
                continue;
            }
            else{
                std::cout<<"Invalid choice: \n";
                continue;
            }
        }

    }while(true);
}

