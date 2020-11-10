#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<iomanip>
#include"bank_account.hpp"

using std::stoi; using std::vector; using std::string;

int main(){
    string line = "2015-09-03 Deposit $100";
    string previous_date = "2015-09-02";
    double balance = 10.00;
    double apr = 12.0;
    std::cout << "Deposit: " << process_command(line, previous_date,balance, apr) << std::endl;
}
