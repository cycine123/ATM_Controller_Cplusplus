# ATM_Controller_Cplusplus
This repo contains the ATM_Controller project

language: c++14
Operating System: macOS 11.1

The ATM controller has a simplified flow: Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw

There is a main.cpp file which contains some test cases and driver code. You can manipulate it to try out different test cases

There are following header files:
- account.hpp
  This file contains a base class for account, definition for checking account, saving account and BankAccount
- bank.hpp
  This file contains a simplified definition for the banking system so the ATM controller can get access to necessary banking information
- cashBin.hpp
  This file contains a simplified definition for the ATM cash bin system so the ATM controller can get access to necessary information
- ATMController.hpp
  This file contains a simplified definition for ATM controller. 


Instruction:

- Download all of the files and save them under your folder of choice
- Open terminal and navigate to the folder where you saved all of the files
- Use the following commands to compile and run the code: 
- g++ -o run *.cpp -std=c++14
- ./run
- Follow the instructions on the terminal to test out the cases. You can look into main.cpp to check the bank database
