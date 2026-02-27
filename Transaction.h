#pragma once

#include<string>

class Transaction{
public: 
    std::string type;
    std::string otherUser;
    double amount;

    Transaction(std::string t="" , std::string o="" , double amnt = 0):type(t) , otherUser(o) , amount(amnt){}

    
};