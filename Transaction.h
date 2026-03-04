#pragma once

#include<string>
#include<ctime>


class Transaction{
protected: 
    std::string type;
    std::string otherUser;
    double amount;
    std::string timestamp;

public:

    std::string getCurrentTime() const;


    Transaction(std::string t="" , std::string o="" , double amnt = 0 , std::string ts = ""):type(t) , otherUser(o) , amount(amnt) , timestamp(ts.empty() ? getCurrentTime():ts){}

    std::string getTs()const;
    std::string getType()const;
    std::string getOtherUser()const;
    double getAmount()const;

    
};