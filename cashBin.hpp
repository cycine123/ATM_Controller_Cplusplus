//
//  cashBin.hpp
//  ATM_Controller
//
//  This file contains the cash bin that is in the ATM machine
//  Assume that there is no cash upper limit in the cash bin
//  Created by Zheng Wang on 2/21/21.
//

#ifndef cashBin_hpp
#define cashBin_hpp

#include <stdio.h>
using namespace std;

class CashBin
{
private:
    int cash_;
public:
    CashBin() = default;
    ~CashBin() = default;
    void pushInCash(int money) {cash_ += money;};
    bool takeOutCash(int money);
    int getCash() const {return cash_;};
};

#endif /* cashBin_hpp */
