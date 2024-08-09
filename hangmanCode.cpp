#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

bool inCheck(vector<int> check, int key) 
{
    for(auto it: check) {
        if(it == key) return true;
    }
    return false;
}

pair<string, string> handleRandom(string mode, vector<int> &check) //Trả về lỗi <error, error> hoặc <hint, word>
{
    fstream fs(mode);
    if(!fs.is_open()) {
        cout << "Error opening file " << mode << endl;
        pair<string, string> error;
        error.first = "Error";
        error.second = "Error";
        return error;
    }
    int n; //Số từ trong file
    srand(time(0));
    fs >> n;
    int ran_num = rand() % n;
    while(inCheck(check, ran_num)) {
        cout << ran_num << endl;
        ran_num = rand() % n;
    }
    check.push_back(ran_num);
    pair<string, string> word;
    for(int i = 0; i <= ran_num; i++) {
        getline(fs, word.first, ',');
        getline(fs, word.second);
    }

    return word;
}

bool checkLetter(string word, char letter){}
void printABC()
{
}

void showHiddenWord() {}

void showHangMan() {
    //show score
}

void showWinLoose()
{
    // loose xong chuyển qua nhập tên
}

void showList() {}

void showInit() 
{
    cout << "+------------------------------------------------+" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                 Enter game mode:               |" << endl;
    cout << "+------------------------------------------------+" << endl;
    int mode;
    bool next = false;
    string s_mode = "";
    while(!next) {
        switch (mode)
        {
        case 1:
            s_mode += "easy";
            !next;
            break;
        case 2:
            s_mode += "normal";
            !next;
            break;
        case 3:
            s_mode += "hard";
            !next;
            break;
        case 4:
            break;
        default:
            break;
        }
    }
    
    //Gọi tiếp hàm vào game chính và chuyền s_mode;
}

void showUI()
{
}

void startGame() 
{

}

int main()
{
    startGame();
    return 0;
}

// handle random + init (Trân)
// source + showHangMan (Huyên)
// showABC + showHidden + checkLetter (Mai)
// showWinLoose + showList + showUI + startGame (My)
