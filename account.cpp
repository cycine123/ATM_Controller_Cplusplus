//
//  account.cpp
//  ATM_Controller
//
//  Created by Zheng Wang on 2/21/21.
//

#include "account.hpp"

void AccountBase::setBalance(int balance)
{
    if (balance >= 0)
        balance_ = balance;
}

void AccountBase::depositMoney(int money)
{
    if (money >= 0)
        balance_ += money;
}


bool Checking::withdrawMoney(int money)
{
    if (money > getBalance())
    {
        return false;
    }
    setBalance(getBalance()-money);
    return true;
}

BankAccount::BankAccount(string uname, string cnum)
{
    user_name_ = uname;
    card_number_ = cnum;
}

bool BankAccount::createChecking(int money)
{
    if (money < 0)
        return false;
    has_checking_ = true;
    check_account_.setBalance(money);
    return true;
}
bool BankAccount::createSaving(int money)
{
    if (money < 0)
        return false;
    has_saving_ = true;
    save_account_.setBalance(money);
    return true;
}

bool BankAccount::getChecking(Checking*& check_account)
{
    check_account = &check_account_;
    return has_checking_;
}

bool BankAccount::getSaving(Saving*& save_account)
{
    save_account = &save_account_;
    return has_saving_;
}
