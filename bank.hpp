//
//  bank.hpp
//  ATM_Controller
//
//  Created by Zheng Wang on 2/21/21.
//

#ifndef bank_hpp
#define bank_hpp

#include <stdio.h>
#include <unordered_map>
#include "account.hpp"
using namespace std;

class Bank
{
private:
    // stores all of the users: account number - bank account
    unordered_map<string, BankAccount> all_accounts_;
    unordered_map<string, string> accounts_pin_;
public:
    Bank() = default;
    ~Bank() = default;
    void addUser(string accntNumber, string pin, BankAccount account);
    void deleteUser(string accntNumber);
    bool getAccount(string accntNumber, BankAccount*& account);
    bool correctPIN(string accntNumber, string pin);
};

#endif /* bank_hpp */
