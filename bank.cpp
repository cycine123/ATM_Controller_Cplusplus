//
//  bank.cpp
//  ATM_Controller
//
//  Created by Zheng Wang on 2/21/21.
//

#include "bank.hpp"

void Bank::addUser(string accntNumber, string pin, BankAccount account)
{   // if user has already exists, just replace the account
    all_accounts_.emplace(accntNumber, account);
    accounts_pin_.emplace(accntNumber, pin);
};
void Bank::deleteUser(string accntNumber)
{
    all_accounts_.erase(accntNumber);
};
bool Bank::getAccount(string accntNumber, BankAccount*& account)
{
    auto iter = all_accounts_.find(accntNumber);
    if (iter == all_accounts_.end())
        return false;
    account = &iter->second;
    return true;
};

bool Bank::correctPIN(string accntNumber, string pin)
{
    if (accounts_pin_.find(accntNumber) == accounts_pin_.end())
        return false;
    if (accounts_pin_[accntNumber].compare(pin) == 0)
        return true;
    return false;
}
