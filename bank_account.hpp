#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cmath>
#include<iomanip>

#ifndef BANK
#define BANK

using std::stoi; using std::vector; using std::string;

// Calculates interest for a month
double interest_for_month(double &balance, double &apr) {
  double Accured = (balance*apr)/1200.00;
  // Rounds to two decimal places
  double interest = std::floor(Accured*100.00)/100.00;
  return interest;
}

// Deposits into balance
void deposit(double &balance, double &amount) {
  std::cout << std::fixed << std::setprecision(2);
  balance += amount;
}

// Bool to return true or false if the amount being with drawn will overdraft your account
bool withdraw(double &balance, double &amount) {
  if(balance >= amount) {
    balance -= amount;
    return true;
  }
  else{
    return false;
  }
}
// Performs the overdraft
void overdraft(double &balance, double &amount) {
    balance = balance - amount - 35.0;
}

// splits the date/command line into usable parts
void split(const std::string &s, vector<std::string> &elems, char sep){
  std::istringstream iss(s);
  std::string item;
  while(getline(iss, item, sep)) {
    elems.push_back(item);
  }
}
// using pointers to assign day, month, year
void string_date_to_int_ptrs(std::string date,int *year,int *month,int *day){ 
  vector<string> temp;
  split(date, temp, '-');
  *day = std::stoi(temp[2]);
  *month = std::stoi(temp[1]);
  *year = std::stoi(temp[0]);
}

// tedious function for no reason but had to be written. Calls the pointer version to prevent repeated code
void string_date_to_ints(std::string date ,int &year,int &month,int &day){ 
  string_date_to_int_ptrs(date, &year, &month, &day);
}


// seperates 2 dates, then compares months and year to depens on which is larger.
double number_of_first_of_months(string date_early,string date_late){
  int year_early = 0, month_early = 0, day_early = 0;
  int year_late = 0, month_late = 0, day_late = 0;
  // Early Months
  string_date_to_ints(date_early, year_early, month_early, day_early);
  // Late Months
  string_date_to_ints(date_late, year_late, month_late, day_late);
  // difference in Months/years
  int diff_mon = 0;
  int diff_year = 0;
  int total_months = 0;
  // checks if months/year is less than the other to prevent negatives
  if(month_late <= month_early){
    diff_mon = month_early - month_late;

    if(year_late > year_early){
      diff_year = year_late - year_early;
      total_months = ((diff_year)*12.0)-(diff_mon);
    }
    else if(year_late == year_early){
      total_months = ((diff_year)*12.0)+(diff_mon);
    }
    else{
      total_months = ((diff_year)*12.0)+(diff_mon);
    }
  }
  else if(month_late > month_early) {
    diff_mon = month_late - month_early;
    if(year_late > year_early){
    diff_year = year_late - year_early;
    total_months = ((diff_year)*12.0)+(diff_mon);
    }
    else if(year_late == year_early){
      total_months = ((diff_year)*12.0)+(diff_mon);
    }
    else {
      total_months = ((diff_year)*12.0)-(diff_mon);
    }
  }
  // total months
  return static_cast<double>(total_months);
}

// calculates compound interest over months using interest for month
double interest_earned(double &balance, double apr, string date_early, string date_late) {
  double temp_bal = balance;
  double tot_int = 0.0;
  int months = number_of_first_of_months(date_early, date_late);
  for(int i = 0; i < months; i++){
    tot_int += interest_for_month(temp_bal, apr);
    temp_bal += interest_for_month(temp_bal, apr);
  }
  return tot_int;
}

//performs deposits and withdrawls from account, also calculates interest and modifies early date for next process
string process_command(string line, string &previous_date,double &balance, double& apr) {
  string date, command;
  double amount;
  vector<string> temp;
  split(line, temp, ' ');
  date = temp[0];
  command = temp[1];
  string amount_temp = temp[2];
  temp[2].erase(0,1);
  amount = std::stod(temp[2]);
  if(previous_date == ""){
    previous_date = date;
  }
  int months = number_of_first_of_months(previous_date, date);
  if(command == "Deposit"){
    if(months != 0){
      if(balance < 0){
        deposit(balance, amount);
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"" << "\nSince " << previous_date <<", interest has accrued " << months << " times.\n$0.00" << " interest has been earned." << "\nBalance: " << balance << "\n";
        previous_date = date;
        return oss.str();
      }
      else if(balance > 0){
        double interest = interest_earned(balance, apr, previous_date, date);
        deposit(balance, amount);
        std::ostringstream oss;
        balance = balance + interest;
        oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"" << "\nSince " << previous_date <<", interest has accrued " << months << " times.\n$" << interest << " interest has been earned." << "\nBalance: " << balance << "\n";
        previous_date = date;
        return oss.str();
      }
    }
    else if(months == 0) {
      deposit(balance, amount);
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"" << "\nBalance: " << balance << "\n";
      previous_date = date;
      return oss.str();
    }
    
  }
  else if(command == "Withdraw") {
    bool withdraw_check;
    double interest = interest_earned(balance, apr, previous_date, date);
    withdraw_check = withdraw(balance, amount);
    if(months == 0) {
      if(withdraw_check == false) {
        overdraft(balance, amount);
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"\nOverdraft!" << "\nBalance: " << balance << "\n";
        previous_date = date;
        return oss.str();
     }
     else if(withdraw_check == true) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"" << "\nBalance: " << balance << "\n";
        previous_date = date;
        return oss.str();
      }
    }
    else if(months != 0) {
      if(withdraw_check == false) {
        double interest = interest_earned(balance, apr, previous_date, date);
        overdraft(balance, amount);
        std::ostringstream oss;
        balance = balance + interest;
        oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"" << "\nSince " << previous_date <<", interest has accrued " << months << " times.\n$" << interest << " interest has been earned." << "\nOverdraft!" <<"\nBalance: " << balance << "\n";
        previous_date = date;
        return oss.str();
      }
      else if(withdraw_check == true) {
        std::ostringstream oss;
        balance = balance + interest;
        oss << std::fixed << std::setprecision(2) << "On " << date << ": Instructed to perform \"" << command << " " << amount_temp << "\"" << "\nSince " << previous_date <<", interest has accrued " << months << " times.\n$" << interest << " interest has been earned." << "\nBalance: " << balance << "\n";
        previous_date = date;
        return oss.str();
        
      }
    }
  }
}

string process_commands(string input, double apr){
  string command;
  string process;
  string final_process;
  std::istringstream iss(input);
  string previous_date = "";
  double balance = 0.0;
  while(std::getline(iss, command)){
    process =  process_command(command, previous_date, balance, apr);
    final_process += process;
  }
  return final_process;
}

#endif
