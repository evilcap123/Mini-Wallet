#pragma once
#include "UPIUser.h"
#include <vector>

class WalletSys{
private:
    std::vector<UpiUser> users;

public:
    void CreateUser();
    int findUser(const std::string& mobile);

    void saveToFile();
    void LoadFromFile();

    void showMenu();
};