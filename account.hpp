//
//  account.hpp
//  ATM_Controller
//
//  This file defines a simplified user bankaccount which may include checking account and saving account
//  Created by Zheng Wang on 2/21/21.
//

#ifndef account_hpp
#define account_hpp

#include <stdio.h>
#include <string>
using namespace std;

class AccountBase
{
private:
    int balance_;
public:
    int getBalance() {return balance_;};
    void setBalance(int balance);
    void depositMoney(int money);
};

class Checking: public AccountBase
{
public:
    // withdrawmoney
    // return false if the money is more than the balance in the account
    Checking(){setBalance(0);};
    Checking(int init_money){setBalance(init_money);};
    ~Checking() = default;
    bool withdrawMoney(int money);
};

class Saving: public AccountBase
{
public:
    Saving(){setBalance(0);};
    Saving(int init_money){setBalance(init_money);};
    ~Saving() = default;
};

class BankAccount
{
private:
    string user_name_;
    string card_number_;
    Checking check_account_;
    Saving save_account_;
    bool has_checking_ = false;
    bool has_saving_ = false;
public:
    BankAccount() = default;
    BankAccount(string uname, string cnum);
    ~BankAccount() = default;
    string getCardNumber() const {return card_number_;};
    string getUserName() const {return user_name_;};
    void setCardNumber(string cnum) {card_number_ = cnum;};
    void setUserName(string uname) {user_name_ = uname;};
    bool createChecking(int money);
    bool createSaving(int money);
    bool hasChecking() const {return has_checking_;};
    bool hasSaving() const {return has_saving_;};
    bool getChecking(Checking*& check_account);
    bool getSaving(Saving*& save_account);
};
#endif /* account_hpp */
