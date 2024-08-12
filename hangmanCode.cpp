#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <unordered_map>
#include <iomanip>
using namespace std;

// Notes: chieu rong man hinh: 52

//---------------------------- UTILITY FUNCTIONS -----------------------------
// Check từ này đã đc đoán ra chưa
bool inCheck(vector<int> check, int key)
{
    for (auto it : check)
    {
        if (it == key)
            return true;
    }
    return false;
}

// Check kí tự có trong từ cần tìm ko
bool checkLetter(string word, char c)
{
    c = toupper(c);

    for (char i : word)
        if (c == i)
            return true;

    return false;
}

// Check tất cả các ký tự đã đc đoán hết chưa
bool allLettersGuessed(string word, unordered_map<char, bool> ABCMap)
{
    for (char c : word)
    {
        if (ABCMap[c] = false)
            return false;
    }
    return true;
}

// Random word
pair<string, string> handleRandom(string mode, vector<int> &check) // Trả về lỗi <error, error> hoặc <hint, word>
{
    fstream fs(mode);
    if (!fs.is_open())
    {
        cout << "Error opening file " << mode << endl;
        pair<string, string> error;
        error.first = "Error";
        error.second = "Error";
        return error;
    }
    int n; // Số từ trong file
    srand(time(0));
    fs >> n;
    int ran_num = rand() % n;
    while (inCheck(check, ran_num))
    {
        cout << ran_num << endl;
        ran_num = rand() % n;
    }
    check.push_back(ran_num);
    pair<string, string> word;
    for (int i = 0; i <= ran_num; i++)
    {
        getline(fs, word.first, ',');
        getline(fs, word.second);
    }

    return word;
}

//---------------------------- GAMEPLAY FUNCTIONS ----------------------------
// Init screen
int showInit()
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
    cin >> mode;
    return mode;
}

// Play game screen
void showHangman(int lives)
{
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                     " << (lives > 0 ? "HANG MAN" : "YOU LOSE") << "                     |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                        " << (lives <= 6 ? "|" : " ") << "                         |" << endl;
    cout << "|                        " << (lives <= 5 ? "0" : " ") << "                         |" << endl;
    cout << "|                       " << (lives <= 4 ? "/" : " ") << (lives <= 3 ? "|" : " ") << (lives <= 2 ? "\\" : " ") << "                        |" << endl;
    cout << "|                       " << (lives <= 1 ? "/" : " ") << " " << (lives <= 0 ? "\\" : " ") << "                        |" << endl;
    cout << "|                   +----------+                   |" << endl;
    cout << "|                   | Lives: " << lives << " |                   |" << endl;
    cout << "+--------------------------------------------------+" << endl;
}

void printABC(unordered_map<char, bool> &ABCMap)
{
    cout << "              ";
    for (auto &pair : ABCMap)
    {
        if (!pair.second) // nếu chưa chọn
            cout << pair.first << " ";
        else
            cout << "              ";

        if (pair.first == 'P')
            cout << endl
                 << "               ";
        if (pair.first == 'L')
            cout << endl
                 << "                 ";
    }
}

void showHiddenWord(string word, unordered_map<char, bool> &ABCMap)
{
    int length = word.length();
    int width = (50 - length * 1.5) / 2; // canh giữa

    cout << setw(width) << setfill(' ');

    for (int i = 0; i < length; i++)
        if (word[i] == ' ')
            cout << "  ";
        else
        {
            if (ABCMap[word[i]] == true)
                cout
                    << word[i] << " ";
            else
                cout << "_ ";
        }
}

// WinLose + Get username
void win()
{
    // My
    // 2 options: về lại init screen / chơi tiếp
}
void lose()
{
    // My
    // có nhập tên ko?
    // gọi hàm ranking
}

void printRanking()
{
    // My
    // show bxh (hàm showList() cũ)
}

//------------------------------ GAME LOOP -------------------------------------
void startGame()
{             // showUI() cũ
              // 0. Variables
    int mode; // chế độ chơi (1 dễ, 2 tb, 3 khó)

    pair<string, string> wordPair; // random từ file
    string hint, word;             // hint và từ cần đoán
    vector<int> check;             // lưu index của mấy từ đã random

    char c; // chữ cái ng dùng nhập
    // vector<char> guessedLetters; // các chữ cái ng dùng nhập rồi

    int lives = 7;      // số mạng hiện tại
    bool isWin = false; // thắng chưa? chưa =))

    int highScore = 0; // điểm cao nhất
    int score = 0;     // điểm hiện tại

    // bảng cập nhật thuộc tính của các chữ cái
    unordered_map<char, bool> ABCMap =
        {{'m', false}, {'n', false}, {'b', false}, {'v', false}, {'c', false}, {'x', false}, {'z', false}, {'l', false}, {'k', false}, {'j', false}, {'h', false}, {'g', false}, {'f', false}, {'d', false}, {'s', false}, {'a', false}, {'p', false}, {'o', false}, {'i', false}, {'u', false}, {'y', false}, {'t', false}, {'r', false}, {'e', false}, {'w', false}, {'q', false}};

    // 1. Màn hình Init
    mode = showInit();

    // 2. Random từ
    string modeStr = mode == 1 ? "easy.txt" : mode == 2 ? "normal.txt"
                                                        : "hard.txt";
    wordPair = handleRandom(modeStr, check);
    word = wordPair.second;
    hint = wordPair.first;

    // 3. Bắt đầu đoán từ
    while (lives > 0 || !isWin)
    {
        showHangman(lives);
        printABC(ABCMap);
        showHiddenWord(word, ABCMap);

        cout << "Enter a letter: ";
        cin >> c;
        c = toupper(c);

        if (checkLetter(word, c))
        {
            ABCMap[c] = true;
        }
        else
        {
            lives--;
        }

        // hết lives -> LOSE
        if (lives == 0)
        {
            isWin = false;
            break;
        }
        // đoán đúng hết -> WIN
        if (allLettersGuessed)
        {
            isWin = true;
            break;
        }
    }

    // My
    // 4. Kết quả thắng thua + lấy tên ng chơi
    if (isWin == true)
    {
        win();
    }
    else
    {
        lose();
    }
}

int main()
{
    startGame();
    return 0;
}
