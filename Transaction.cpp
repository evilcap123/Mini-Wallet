#include "Transaction.h"


std::string Transaction::getType()const{return type;}
std::string Transaction::getOtherUser()const{return otherUser;}
double Transaction::getAmount()const{return amount;}

std::string Transaction::getTs()const{return timestamp;}

std::string Transaction::getCurrentTime()const{
        time_t now = time(0);
        struct tm timeInfo;
        localtime_s(&timeInfo , &now);
        char buf[20];
        strftime(buf , sizeof(buf) , "%Y-%m-%d %H:%M:%S" , &timeInfo);
        return std::string(buf);
    }