//
//  cashBin.cpp
//  ATM_Controller
//
//  Created by Zheng Wang on 2/21/21.
//

#include "cashBin.hpp"

bool CashBin::takeOutCash(int money)
{
    if (money > cash_)
    {
        return false;
    }
    cash_ -= money;
    return true;
}
