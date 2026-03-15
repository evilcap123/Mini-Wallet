#include "WalletSystem.h"
#include<iostream>
#include <windows.h>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<limits>
#include<cctype>






namespace{
    enum class Msg{Info , Success , Warning , Error , Title};

    void setColor(Msg type){
         HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (type) {
            case Msg::Info:    SetConsoleTextAttribute(h, 11); break; // cyan
            case Msg::Success: SetConsoleTextAttribute(h, 10); break; // green
            case Msg::Warning: SetConsoleTextAttribute(h, 14); break; // yellow
            case Msg::Error:   SetConsoleTextAttribute(h, 12); break; // red
            case Msg::Title:   SetConsoleTextAttribute(h, 13); break; // magenta
        }

    }

    void resetColor(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 7);

    }
    void clearScreen(){
    std::system("cls");
    }

    void pauseScreen(){
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }


    void printTitle(const std::string& title){
        setColor(Msg::Title);
    std::cout << "\n=========================================\n";
        std::cout << " " << title << "\n";
    std::cout << "=========================================\n";
        resetColor();
    }


    void printMenuItem(int n , const std::string& text){
        std::cout<< n << ") " << text << "\n";
    }

    void printStatus(const std::string& text , Msg type){
        setColor(type);
        std::cout<< text <<"\n";
        resetColor();
    }
    int readInt(const std::string& prompt){
        int value;
         while(true){
            std::cout<< prompt;
            if (std::cin>> value) return value;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printStatus("Invalid number. Please try again.", Msg::Error);
        }
    }
    double readDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) return value;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printStatus("Invalid amount. Please try again.", Msg::Error);
        }
    }
    int readChoice(int min , int max){
        while(true){
            int choice = readInt("Select option: ");
            if( choice >= min && choice <= max) return choice;
            printStatus("Option out of range. Try again:!!!." , Msg::Error);
        }
    }
}





 int WalletSys::findUser(const std::string& mobile) {
        for(int i =0 ; i<(int)users.size(); i++){
            if( users[i].getMobile() == mobile) return i;
            
        }
        return -1;
    }

void WalletSys::CreateUser(){
    clearScreen();
    printTitle("CREATE WALLET");
    std::string name , mobile;
    int pin;
    double initialBalance;

    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin , name);
    std::cout<< "Enter mobile: ";
    std::cin>>mobile;

    if(mobile.length()!=10){
        printStatus("Enter a valid 10-digit mobile number.", Msg::Error);
        pauseScreen();
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
        printStatus("Mobile number must contain only digits.", Msg::Error);
        pauseScreen();
        return;
    }

    if(findUser(mobile)!=-1){
        printStatus("User with this mobile already exists.", Msg::Error);
        pauseScreen();
        return;
    }

    pin = readInt("Set PIN (4 digits): ");

    if(pin>9999 || pin<1000){
        printStatus("PIN must be 4 digits.", Msg::Error);
        pauseScreen();
        return;
    }

    initialBalance = readDouble("Enter initial balance: ");


    if(initialBalance<=0){
         printStatus("Initial balance must be greater than 0.", Msg::Error);
        pauseScreen();
        return;
    }

    users.push_back(UpiUser(name , mobile , initialBalance, pin));
    printStatus("Wallet created successfully.", Msg::Success);
    pauseScreen();

   
}

bool WalletSys::deleteUser(const std::string& mobile){
    int idx = findUser(mobile);
    if(idx == -1){
        printStatus("User not found.", Msg::Error);
        return false;
    }

    users.erase(users.begin() + idx);
    saveToFile();
     printStatus("User deleted successfully.", Msg::Success);
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
    clearScreen();
    printTitle("LOGIN");

    std::string mobile_num;
    int enteredPin;
    const std::string admin_mobile_num = "16212";
    const int admin_pin = 1234;

    std::cout<<"Enter mobile number: ";
    std::cin>>mobile_num;

    enteredPin = readInt("Enter your PIN: ");

    if(mobile_num == admin_mobile_num && enteredPin == admin_pin){
        printStatus("Admin Login Successfully.", Msg::Success);
        pauseScreen();
        adminDashboard(-1);
        return;
    }

    int index = findUser(mobile_num);

    if(index == -1) {
        printStatus("User not found.", Msg::Error);
        pauseScreen();
    return;
}

    

    if(users[index].verifyPin(enteredPin)){
        printStatus("Login successful.", Msg::Success);
        pauseScreen();
        userDashboard(index);
    }else{
        printStatus("Incorrect PIN.", Msg::Error);
        pauseScreen();
    }
}


void WalletSys::userDashboard(int userIdx){
    int choice;
    


    
    do{
        clearScreen();
        printTitle("USER DASHBOARD");

        std::string userMobile = users[userIdx].getMobile();
        double userBalance = users[userIdx].getBalance();
        std::cout << "User: " << users[userIdx].getName()
                  << " | Mobile: " << userMobile
                  << " | Balance: " << std::fixed << std::setprecision(2)
                  << userBalance << "\n\n";

        if(userBalance<100){
            printStatus("Low balance: Top up recommended.", Msg::Warning);
        }

        printMenuItem(1, "Check Balance");
        printMenuItem(2, "Transfer Money");
        printMenuItem(3, "Transaction History");
        printMenuItem(4, "Deposit Money");
        printMenuItem(5, "Withdraw Money");
        printMenuItem(6, "Change PIN");
        printMenuItem(7, "Logout");

        choice = readChoice(1, 7);

        

        if (choice == 1) {
            std::cout << "Your Balance: "
                      << std::fixed << std::setprecision(2)
                      << users[userIdx].getBalance() << '\n';
            pauseScreen();
        }


        else if(choice == 2){
            std::string receiverMobile;
            double amount;

            std::cout<<"Enter receiver Mobile: ";
            std::cin>>receiverMobile;

            int receiverIdx = findUser(receiverMobile);

            if(receiverIdx==-1){
                printStatus("Receiver not found.", Msg::Error);
                pauseScreen();
                continue;
            }

            if(users[userIdx].getMobile() == receiverMobile){
                printStatus("Cannot transfer money to yourself.", Msg::Error);
                pauseScreen();
                continue;
            }

            
            amount = readDouble("Enter amount: ");


            if(amount <= 0){
                 printStatus("Transfer amount must be greater than 0.", Msg::Error);
                pauseScreen();
                continue;
            }


            int pin = readInt("Enter your PIN: ");

            if(!users[userIdx].verifyPin(pin)){
                printStatus("Incorrect PIN.", Msg::Error);
                pauseScreen();
                continue;
            }

            if(!users[userIdx].withdraw(amount)){
                printStatus("Insufficient balance.", Msg::Error);
                pauseScreen();
                continue;
            }

            users[receiverIdx].depo(amount);

            users[userIdx].addTransaction(Transaction("Sent" , receiverMobile , amount));
            users[receiverIdx].addTransaction(Transaction("Received" , userMobile , amount));

            
            saveToFile();
            printStatus("Transfer successful.", Msg::Success);
            pauseScreen();

        }


        else if(choice==3){
            users[userIdx].showHistory(5);
             pauseScreen();

        }


        else if(choice == 4 || choice == 5){
            int pin = readInt("Enter your PIN: ");
            

            

            if(!users[userIdx].verifyPin(pin)){
                printStatus("Incorrect PIN.", Msg::Error);
                pauseScreen();
                continue;
            }


            double amount = readDouble("Enter Amount: ");

            if (amount <= 0) {
                printStatus("Amount must be greater than 0.", Msg::Error);
                pauseScreen();
                continue;
            }

            if(choice==4){
                if(users[userIdx].depo(amount)){
                users[userIdx].addTransaction(Transaction("Deposit", "Self", amount) );
                saveToFile();
                printStatus("Deposit successful.", Msg::Success);

                }
            }
            else{
               if (!users[userIdx].withdraw(amount)){
                    printStatus("Insufficient balance.", Msg::Error);
                    pauseScreen();                continue;
               }
               users[userIdx].addTransaction(Transaction("Withdraw" , "Self" , amount));
               saveToFile();
               printStatus("Withdrawal Successful.", Msg::Success);
            }
            pauseScreen();
        }

        else if(choice == 6){
            char ans;
            int pin, newPin;
            
            std::cout<<"Are you sure u want to change your pin(y/n): ";
            std::cin>>ans;

            switch (ans) {

            case 'y':
            case 'Y':
                pin = readInt("Enter your current PIN: ");

                if(!users[userIdx].verifyPin(pin)){
                    printStatus("Incorrect PIN.", Msg::Error);
                        pauseScreen();
                    continue;
                }

                newPin = readInt("Enter New PIN (4 digits): ");

                if(newPin>9999 || newPin<1000){
                    printStatus("PIN must be 4 digits.", Msg::Error);
                        pauseScreen();
                    continue;
                }

                users[userIdx].setPin(newPin);
                saveToFile();
                printStatus("PIN changed successfully.", Msg::Success);
                    pauseScreen();
                break;
            
                case 'n':
                case 'N':
                    break;

            default:
            printStatus("Invalid choice.", Msg::Error);
                    pauseScreen();
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
                printStatus("Invalid choice.", Msg::Error);
                pauseScreen();
                continue;
            }
        }

    }while(true);
}

void WalletSys::adminDashboard(int index){
    (void)index;
    int choice;

    do{
        clearScreen();
        printTitle("ADMIN DASHBOARD");

        printMenuItem(1, "View all users");
        printMenuItem(2, "Delete user");
        printMenuItem(3, "Logout");

        choice = readChoice(1, 3);


        if(choice == 1){
            if(users.empty()){
                printStatus("No users found.", Msg::Warning);
                pauseScreen();
                continue;
            }
            std::cout<<"\n--- Registered Users ---\n";
            for(int i = 0 ; i< (int)users.size(); i++){
                std::cout<< i+1 << ". "
                    << users[i].getName() << " | "
                    << users[i].getMobile() << " | "
                    << std::fixed << std::setprecision(2) <<users[i].getBalance() << " | "
                    <<"\n";
            }
            pauseScreen();
        }
        else if(choice ==2){
            std::string mobile;
            std::cout<<"Enter mobile number to delete: ";
            std::cin>>mobile;
            deleteUser(mobile);
            pauseScreen();
        }
        else if(choice == 3){
            printStatus("Admin logged out.", Msg::Info);
            pauseScreen();
            return;
        }
        
    }while(true);
}

