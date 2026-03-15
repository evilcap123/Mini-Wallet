#pragma once
#include "UPIUser.h"
#include <vector>

class WalletSys{
private:
    std::vector<UpiUser> users;

public:
    void CreateUser();
    int findUser(const std::string& mobile);

    void userDashboard(int index);
    void userLogin();

    void adminDashboard(int index);
    bool deleteUser(const std::string& mobile);
    
    void saveToFile();
    void LoadFromFile();

    
};