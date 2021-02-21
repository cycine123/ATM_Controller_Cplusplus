//
//  main.cpp
//  ATM_Controller
//  This file is to create some test cases to test out the ATM controller system
//  Created by Zheng Wang on 2/21/21.
//

#include <iostream>
#include <unordered_map>
#include "ATMController.hpp"
#include "cashBin.hpp"

using namespace std;

void setUpBankDataBase(Bank* vbank)
{
    // only checking
    // user name, account number
    BankAccount account1("Gin Tama", "1111");
    account1.createChecking(1000);
    // only saving
    BankAccount account2("Jason Johnson", "2222");
    account2.createSaving(200);
    // both checking and saving
    BankAccount account3("Mayo White", "3333");
    account3.createChecking(10000);
    account3.createSaving(500);
    // no checking or saving
    BankAccount account4("Eren Hunk", "4444");
    // account number, pin number, account
    vbank->addUser("1111", "123456", account1);
    vbank->addUser("2222", "234567", account2);
    vbank->addUser("3333", "345678", account3);
    vbank->addUser("4444", "456789", account4);
}

int main() {
    Bank vBank = Bank();
    // you can change this function to change the bank database
    setUpBankDataBase(&vBank);
    
    CashBin cash_bin = CashBin();
    // you can change this value to specify the cash in the bin
    cash_bin.pushInCash(5000);
    
    ATMController ATM(&vBank, &cash_bin);
    
    ATM.activeATM();
    return 0;
}
