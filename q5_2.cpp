/*
GenAI: Teach me how to use     istringstream iss(s) and ostringstream oss
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<string> parse_words(const string& s) {
    istringstream iss(s);
    vector<string> out;
    string w;
    while (iss >> w) out.push_back(w);
    return out;
}

vector<int> parse_ints(const string& s) {
    istringstream iss(s);
    vector<int> out;
    int x;
    while (iss >> x) out.push_back(x);
    return out;
}

string translate_with_vector(const vector<string>& words,const vector<int>& nums) {
    ostringstream oss;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i) oss << ' ';
        int k = nums[i];
        if (1 <= k && k <= static_cast<int>(words.size())) oss << words[k - 1];
        else oss << "<UNK>";
    }
    return oss.str();
}



string translate_with_map(const vector<string>& words,const vector<int>& nums) {
    map<int, string> mp;
    for (int i = 1; i <= static_cast<int>(words.size()); ++i) mp[i] = words[i - 1];

    ostringstream oss;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i) oss << ' ';
        auto it = mp.find(nums[i]);
        oss << (it == mp.end() ? "<UNK>" : it->second);
    }
    return oss.str();
}

int main() {
    
    string word_list = "Apple Banana Strawberry Tomato Elephant Umbrella Vanilla House Ice Jaguar";    
    string num_list = "8 2 6 4 7 1 9 5 3 10 2 7 1 6 8";
    vector<string> words = parse_words(word_list);
    vector<int>    nums  = parse_ints(num_list);
    
    string out_vec = translate_with_vector(words, nums);
    string out_map = translate_with_map(words, nums);

    cout << "[Vector] " << out_vec <<endl;
    cout << "[Map   ] " << out_map <<endl;
    system("pause");
    return 0;
}