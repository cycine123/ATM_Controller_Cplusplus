//
//  ATMController.cpp
//  ATM_Controller
//
//  Created by Zheng Wang on 2/21/21.
//

#include <stdio.h>
#include "ATMController.hpp"

ATMController::ATMController(Bank* link_bank, CashBin* cash_bin)
{
    bank_ = link_bank;
    cash_bin_ = cash_bin;
}

// This function actives the ATM flow
void ATMController::activeATM()
{
    // ask the user to insert a card
    string card = "";
    BankAccount* user_account = nullptr;
    while (!valid_card_)
    {
        insertCard(card, user_account);
    }
    
    // ask the user to input the PIN number
    bool correct_pin = false;
    int pin_times = 0;
    while (!correct_pin && valid_card_)
    {
        if (TIMES_FOR_PIN - pin_times <= 0)
        {
            cout << "YOU TRIED TOO MANY TIMES, FORCE QUIT" << endl;
            valid_card_ = false;
            break;
        }
        inputPIN(card, correct_pin, pin_times);
    }
    
    // select an account
    bool account_exists = false;
    int account_type = 0;
    Checking* check_account = nullptr;
    Saving* save_account = nullptr;
    bool proceed = true;
    while (!account_exists && valid_card_ && user_account && proceed)
    {
        selectAccount(account_type, account_exists, user_account, check_account, save_account);
        if (!account_exists)
        {
            cout << "DO YOU WANT TO SELECT A DIFFERENT ACCOUNT AND PROCEED? (Y/N)" << endl;
            string conti;
            cin >> conti;
            if (conti.compare("N") == 0 || conti.compare("n") == 0)
                proceed = false;
        }
    }
    
    // select an operation
    bool done_operation = false;
    while (!done_operation && valid_card_ && account_exists && (account_type == 1 || account_type == 2) )
    {
        selectOperation(account_type, check_account, save_account);
        cout << "HAVE YOU FINISHED OPERATION? (Y/N)" << endl;
        string done;
        cin >> done;
        if (done.compare("Y") == 0 || done.compare("y") == 0)
            done_operation = true;
    }
    cout << "THANKS FOR USING VBANK ATM" << endl;
    cout << "DEACTIVATING..." << endl;
    valid_card_ = false;
}

// This function asks the user to insert a card and check if it is valid
void ATMController::insertCard(string& card, BankAccount*& user_account)
{
    cout << "WELCOME TO VBANK ATM, PLEASE INSERT A CARD" << endl;
    cin >> card;
    
    // check whether this card is in the bank database
    if (!bank_->getAccount(card, user_account))
    {
        cout << "INVALID CARD, PLEASE TRY AGAIN" << endl;
    } else
        valid_card_ = true;
}

// This function asks the user to input pin number and check whether the pin is correct or not
void ATMController::inputPIN(string card, bool& correct_pin, int& pin_times)
{
    string pin;
    cout << "PLEASE INPUT PIN. YOU CAN TRY " << TIMES_FOR_PIN-pin_times << " TIME(S)" << endl;
    cin >> pin;
    pin_times++;
    // check the correctness of the pin number
    correct_pin = bank_->correctPIN(card, pin);
    if (!correct_pin)
    {
        cout << "WRONG PIN" << endl;
    }
}

// This function asks the user to select an account
// If this user doesn't have any account, return
void ATMController::selectAccount(int& account_type, bool& account_exists, BankAccount*& user_account, Checking*& check_account, Saving*& save_account)
{
    bool has_checking = user_account->hasChecking();
    bool has_saving = user_account->hasSaving();
    if (has_checking && has_saving)
    {
        cout << "PLEASE SELECT AN ACCOUNT (1: CHECKING; 2: SAVING)" << endl;
    }
    else if (has_checking)
    {
        cout << "PLEASE SELECT AN ACCOUNT (1: CHECKING)" << endl;
    }
    else if (has_saving)
    {
        cout << "PLEASE SELECT AN ACCOUNT (2: SAVING)" << endl;
    }
    else
    {
        cout << "YOU DON'T HAVE ANY TYPE OF ACCOUNT WITH VBANK. "
        << "IF YOU WANT TO OPEN ONE, PLEASE GO TO A LOCAL BRANCH" << endl;
        return;
    }
    cin >> account_type;
    switch(account_type)
    {
        case 1:
            if (has_checking)
            {
                account_exists = true;
                user_account->getChecking(check_account);
            }
            else
            {
                cout << "YOU DON'T HAVE CHECKING ACCOUNT WITH VBANK. "
                << "IF YOU WANT TO OPEN ONE, PLEASE GO TO A LOCAL BRANCH" << endl;
            }
            break;
        case 2:
            if (has_saving)
            {
                account_exists = true;
                user_account->getSaving(save_account);
            }
            else
            {
                cout << "YOU DON'T HAVE SAVING ACCOUNT WITH VBANK. "
                << "IF YOU WANT TO OPEN ONE, PLEASE GO TO A LOCAL BRANCH" << endl;
            }
            break;
        default:
            cout << "INVALID ACCOUNT TYPE" << endl;
    }
}

// This function asks the user to select an operation
void ATMController::selectOperation(int account_type, Checking*& check_account, Saving*& save_account)
{
    int operation = 0;
    // you cannot withdraw money from saving account
    switch(account_type)
    {
        case 1:
            cout << "SELECT AN OPERATION (1. VIEW BALANCE; 2. DEPOSIT; 3. WITHDRAW)" << endl;
            break;
        case 2:
            cout << "SELECT AN OPERATION (1. VIEW BALANCE; 2. DEPOSIT)" << endl;
            break;
        default:
            cout << "INVALID ACCOUNT TYPE" << endl;
            return;
    }
    
    cin >> operation;
    int money = 0;
    switch(operation)
    {
        case 1:
            cout << "THE BALANCE IN YOUR ACCOUNT IS: " << endl;
            if (account_type == 1 && check_account)
            {
                cout << check_account->getBalance() << endl;
            } else if (account_type == 2 && save_account)
            {
                cout << save_account->getBalance() << endl;
            }
            break;
        case 2:
            cout << "PLEASE INPUT THE DEPOSIT MONEY" << endl;
            cin >> money;
            if (account_type == 1 && check_account)
            {
                check_account->depositMoney(money);
                cout << "THE BALANCE IN THE CHECKING IS" << endl;
                cout << check_account->getBalance() << endl;
            } else if (account_type == 2 && save_account)
            {
                save_account->depositMoney(money);
                cout << "THE BALANCE IN THE SAVING IS" << endl;
                cout << save_account->getBalance() << endl;
            }
            break;
        case 3:
            if (account_type == 1 && check_account)
            {
                cout << "PLEASE INPUT THE WITHDRAW MONEY" << endl;
                cin >> money;
                if (cash_bin_->getCash() < money)
                {
                    cout << "WITHDRAW FAILED BECAUSE THERE IS NOT ENOUGH MONEY IN THE CASH BIN. PLEASE GO TO A LOCAL BRANCH" << endl;
                } else if (!check_account->withdrawMoney(money))
                {
                    cout << "WITHDRAW FAILED BECAUSE OF NOT ENOUGH MONEY" << endl;
                }
                cout << "THE BALANCE IN THE CHECKING IS" << endl;
                cout << check_account->getBalance() << endl;
            } else if (account_type == 2)
            {
                cout << "YOU CANNOT WITHDRAW MONEY FROM SAVING ACCOUNT" << endl;
            }
            break;
        default:
            cout << "INVALID OPERATION" << endl;
    }
    
}


