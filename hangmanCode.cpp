#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Notes: chieu rong man hinh: 52

//---------------------------- UTILITY FUNCTIONS -----------------------------
// Check từ này đã đc đoán ra chưa
bool inCheck(vector<int> check, int key) 
{
    for(auto it: check) {
        if(it == key) return true;
    }
    return false;
}

// Check kí tự có trong từ cần tìm ko
bool checkLetter(string word, char c) {
    // Mai
    //
}

// Check tất cả các ký tự đã đc đoán hết chưa
bool allLettersGuessed(string word, vector<char> guessedLetters) {
    for (char c : word) {
        bool found = false;
        for (char guessed : guessedLetters) {
            if (c == guessed) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

// Random word
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

//---------------------------- GAMEPLAY FUNCTIONS ----------------------------
// Init screen 
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
}

// Play game screen
void showHangman(int lives) {
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                     " << (lives > 0 ? "HANG MAN" : "YOU LOSE") << "                     |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                        " << (lives <= 6 ? "|" : " ") << "                         |" << endl;
    cout << "|                        " << (lives <= 5 ? "0" : " ") << "                         |" << endl;
    cout << "|                       " << (lives <= 4 ? "/" : " ") << (lives <= 3 ? "|" : " ") << (lives <= 2 ? "\\" : " ") << "                        |" << endl;
    cout << "|                       " << (lives <= 1 ? "/" : " ") << " " << (lives <= 0 ? "\\" : " ") << "                        |" << endl;
    cout << "|                   +----------+                   |" << endl;
    cout << "|                   | Lives: "<< lives << " |                   |" << endl;
    cout << "+--------------------------------------------------+" << endl;    
}

void printABC(vector<char> &guessedLetters) {
    // Mai
    // show available letter
}

void showHiddenWord(string word, vector<char> guessedLetters) {
    // Mai
    // nhớ handle trường hợp từ có nhiều chữ cái giống nhau (aPPle, bANANA...)
} 

// WinLose + Get username
void win() {
    // My
    // 2 options: về lại init screen / chơi tiếp
}
void lose() {
    // My
    // có nhập tên ko?
    // gọi hàm ranking
}

void printRanking() {
    // My
    // show bxh (hàm showList() cũ)
}

//------------------------------ GAME LOOP -------------------------------------
void startGame() { // showUI() cũ
// 0. Variables
    int mode; // chế độ chơi (1 dễ, 2 tb, 3 khó)

    pair<string, string> wordPair; // random từ file 
    string hint, word; // hint và từ cần đoán
    vector<int> check; // lưu index của mấy từ đã random

    char c; // chữ cái ng dùng nhập
    vector<char> guessedLetters; // các chữ cái ng dùng nhập rồi

    int lives = 7; // số mạng hiện tại
    bool isWin = false; // thắng chưa? chưa =))

    int highScore = 0; // điểm cao nhất
    int score = 0; // điểm hiện tại


// 1. Màn hình Init
    showInit();

// 2. Random từ
    string modeStr = mode == 1 ? "easy.txt" : mode == 2 ? "normal.txt" : "hard.txt";
    wordPair = handleRandom(modeStr, check);
    word = wordPair.second;
    hint = wordPair.first;

// 3. Bắt đầu đoán từ
    while(lives > 0 && !isWin) {
        showHangman(lives);
        printABC(guessedLetters); 
        showHiddenWord(word,guessedLetters);

        cout << "Enter a letter: ";
        cin >> c;
        c = toupper(c);

        if(checkLetter) {
            guessedLetters.push_back(c);
        }
        else {
            lives--;
        }

        // hết lives -> LOSE
        if(lives == 0) {
            isWin = false;
            break;
        }
        // đoán đúng hết -> WIN
        if(allLettersGuessed) {
            isWin = true;
            break;
        }
    }

// My
// 4. Kết quả thắng thua + lấy tên ng chơi
    if(isWin == true) {
        win();
    }
    else {
        lose();
    }

}

int main() {
    startGame();
    return 0;
}
