#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

int compute_diff(std::string cm_pass, std::string provided_password) {
    int character_diff = 0;
    if(provided_password.size() < cm_pass.size()) {
        for(int i = 0; i < static_cast<int>(provided_password.size()); i++) {
            if(provided_password[i] != cm_pass[i]) {
                character_diff++;
            }
        }
        character_diff += cm_pass.size() - provided_password.size();
    }

    else {
        for(int i = 0; i < static_cast<int>(cm_pass.size()); i++) {
            if(cm_pass[i] != provided_password[i]) {
                character_diff++;
            }
        }
    character_diff += provided_password.size() - cm_pass.size();
    }
    return character_diff;
}
int main(){
    //load file
    std::ifstream common_passwords;
    common_passwords.open ("common_passwords.txt");
    //variables
    std::string provided_password;
    std::string cm_pass;
    std::vector<std::string> sorted_similar_words;
    std::map<int, std::vector<std::string>> cm_map;
    int diff = 0;
    //user input word and relay back
    std::cout << "Give me a password: "; std::cin >> provided_password;
    std::cout << "You provided a password of " << provided_password << std::endl;

    while(!common_passwords.eof()){
        if(common_passwords >> cm_pass){
            diff = compute_diff(cm_pass, provided_password);
            if(cm_map.find(diff) == cm_map.end()){
                std::vector<std::string> temp;
                temp.push_back(cm_pass);
                cm_map.insert({diff, temp});
            }

            else {
                cm_map[diff].push_back(cm_pass);
            }
        }
        
  }
  std::cout << "The most similar passwords to " << provided_password << " are:" << std::endl;
  for(auto element : cm_map.begin()->second) {
    sorted_similar_words.push_back(element);
  }

  std::sort(sorted_similar_words.begin(),sorted_similar_words.end());
  for(auto sorted_element : sorted_similar_words) {
    std::cout << sorted_element << ", ";
  }

  std::cout << std::endl;
  std::cout << "All of which are " << cm_map.begin()->first << " character(s) different." << std::endl;
}
