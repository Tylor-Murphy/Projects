#include<iostream>
#include<string>
using std::cout; using std::endl; using std::cin;
using std::string; 

int get_line_sum(string s) {
    int sum = 0;
    int len = s.length();
    for (int i = 0; i < len; i++) {
        sum += s[i] - '0';
    } return sum;
}
char get_next_state(string s, string rules) {
    char c;
    // sets c to be the character in the index
    if (rules.find(s) != string::npos) {
        c = rules[rules.find(s)+7];
    } 
    else {
        c = '0';
  } 
  return c;
}
void update_line(string &s, string rules) {
    int len = s.length();
    string t = "";
    for (int i = 0; i < len; i++) {
        string sub;
        // wraps around from front to back
        if (i == 0) {
            sub += s[len-1];
            sub += s[0];
            sub += s[1];
        } 
        // wraps around from back to front
        else if (i == len-1) {
            sub += s[len-2];
            sub += s[len-1];
            sub += s[0];
        } 
        // goes through middle of string
        else {
            sub = s.substr(i-1,3);
    }
    t += get_next_state(sub, rules);
  }
  s = t;
}
string run_cellular_automata(string rules, int number_of_lines, string s) {
    string run = R"()";
    for (int i = 0; i < number_of_lines; i++) {
        // .append adds to the end of a string
        run.append(s); 
        run.append(" sum = ");
        run.append(std::to_string(get_line_sum(s)));
        run.append("\n");
        update_line(s, rules);
  }
  return run;
}
int main() {
    string line;
    string rules = R"()";
    getline(cin, line, '.');
    rules.append(line);
    int number_of_lines; cin >> number_of_lines;
    string start_line; cin >> start_line;
    cout << run_cellular_automata(rules, number_of_lines, start_line)
    << endl;
}
