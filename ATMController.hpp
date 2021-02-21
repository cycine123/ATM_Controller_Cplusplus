//
//  ATMController.h
//  ATM_Controller
//
//  This file contains the class ATMController which mimics the flow:
//  Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw
// 
//  Created by Zheng Wang on 2/21/21.
//

#ifndef ATMController_h
#define ATMController_h


#include <iostream>
#include <unordered_map>
#include "bank.hpp"
#include "cashBin.hpp"
using namespace std;

#define TIMES_FOR_PIN     5


class ATMController
{
private:
    Bank* bank_ = nullptr;
    CashBin* cash_bin_ = nullptr;
    
    bool valid_card_ = false;
    
    void insertCard(string& card, BankAccount*& user_account);
    void inputPIN(string card, bool& correct_pin, int& pin_times);
    void selectAccount(int& account_type, bool& account_exists, BankAccount*& user_account, Checking*& check_account, Saving*& save_account);
    void selectOperation(int account_type, Checking*& check_account, Saving*& save_account);
public:
    ATMController() = default;
    ATMController(Bank* link_bank, CashBin* cash_bin);
    ~ATMController() = default;
    
    void activeATM();
    
};

#endif /* ATMController_h */
