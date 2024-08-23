#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <unordered_map>
#include <iomanip>
using namespace std;

struct account
{
    string name;
    int score;
};
// Notes: chieu rong man hinh: 52

//---------------------------- UTILITY FUNCTIONS -----------------------------
string center(const string &str, const int width)
{
    int len = str.length();
    if (width <= len)
        return str;
    int left_padding = (width - len) / 2;
    int right_padding = width - len - left_padding;
    return string(left_padding, ' ') + str + string(right_padding, ' ');
}
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
bool checkLetter(unordered_map<char, bool> ABCMap, string word, char &c)
{
    c = toupper(c);
    if (ABCMap[c])
    {
        cout << c << " is already used!" << "\nEnter another letter: ";
        cin >> c;
        return checkLetter(ABCMap, word, c);
    }

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
        if (ABCMap[c] == false)
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

// set up lai ABC map sau moi lan choi
unordered_map<char, bool> setUpABCMap(unordered_map<char, bool> ABCMap)
{
    for (auto element : ABCMap)
        element.second = false;
    return ABCMap;
}
//---------------------------- GAMEPLAY FUNCTIONS ----------------------------
// Init screen
int showInit()
{
    system("CLS");
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                       __ __   ____  ____    ____  ___ ___   ____  ____                        |" << endl;
    cout << "|                      |  |  | /    ||    \\  /    ||   |   | /    ||    \\                       |" << endl;
    cout << "|                      |  |  ||  o  ||  _  ||   __|| _   _ ||  o  ||  _  |                      |" << endl;
    cout << "|                      |  _  ||     ||  |  ||  |  ||  \\_/  ||     ||  |  |                      |" << endl;
    cout << "|                      |  |  ||  _  ||  |  ||  |_ ||   |   ||  _  ||  |  |                      |" << endl;
    cout << "|                      |  |  ||  |  ||  |  ||     ||   |   ||  |  ||  |  |                      |" << endl;
    cout << "|                      |__|__||__|__||__|__||___,_||___|___||__|__||__|__|                      |" << endl;
    cout << "|                                                           by: Be Ca Vang                      |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|         _______                     || >> GAME MODE << ||                      _______        |" << endl;
    cout << "|       |/      |                          <1> Easy <1>                         |      \\|       |" << endl;
    cout << "|       |      (_)                        <2> Medium <2>                       (_)      |       |" << endl;
    cout << "|       |      \\|/                         <3> Hard <3>                        /|\\      |       |" << endl;
    cout << "|       |       |                                                               |       |       |" << endl;
    cout << "|       |      / \\                                                             / \\      |       |" << endl;
    cout << "|       |                       >> ENTER GAME MODE TO CONTINUE <<                       |       |" << endl;
    cout << "|      _|___                                                                         ___|_      |" << endl;
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;

    int mode = -1;
    string data;
    do
    {
        cout << "Enter game mode: ";
        getline(cin, data);
        if (data.length() != 1)
            continue;
        mode = int(data[0]);
    } while (mode != 49 && mode != 50 && mode != 51);
    return mode - 48;
}

// Play game screen
void showHangman(int lives)
{

    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << center((lives > 0 ? "HANG MAN" : "YOU LOSE"), 95) << "|" << endl;
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                               _________________                                               |" << endl;
    cout << "|                             |/                " << (lives <= 6 ? "|" : " ") << "                                               |" << endl;
    cout << "|                             |                " << (lives <= 5 ? "(_)" : "   ") << "                                              |" << endl;
    cout << "|                             |                " << (lives <= 4 ? "/" : " ") << (lives <= 3 ? "|" : " ") << (lives <= 2 ? "\\" : " ") << "                                              |" << endl;
    cout << "|                             |                " << (lives <= 1 ? "/ " : "  ") << (lives <= 0 ? "\\" : " ") << "                                              |" << endl;
    cout << "|                             |                                                                 |" << endl;
    cout << "|                             |                                                                 |" << endl;
    cout << "|                             |           +----------+                                          |" << endl;
    cout << "|                             |           | Lives: " << lives << " |                                          |" << endl;
    cout << "+-----------------------------|-----------------------------------------------------------------+" << endl;
}

void printABC(unordered_map<char, bool> &ABCMap)
{
    string temp = "";
    for (auto &pair : ABCMap)
    {
        if (!pair.second) // nếu chưa chọn
            temp = temp + pair.first + " ";
        else
            temp += "_ ";

        if (pair.first == 'P')
        {
            cout << "|" << center(temp, 95) << "|";
            cout << endl;
            temp = "";
        }
        if (pair.first == 'L')
        {
            cout << "|" << center(temp, 95) << "|";
            cout << endl;
            temp = "";
        }
    }

    cout << "|" << center(temp, 95) << "|";
}

void showHiddenWord(string word, string hint, unordered_map<char, bool> &ABCMap)
{
    cout << "|" << center("Hint: " + hint, 95) << "|" << endl;

    string hidden_word = "";
    for (int i = 0; i < word.length(); i++)
        if (word[i] == ' ')
            hidden_word += "  ";
        else
        {
            if (ABCMap[word[i]] == true)
                hidden_word = hidden_word + word[i] + " ";
            else
                hidden_word += "_ ";
        }

    cout << "|" << center(hidden_word, 95) << "|";
}

// WinLose + Get username
bool checkInvalidName(string name)
{
    for (int i = 0; i < name.length(); i++)
    {
        if (name[i] != ' ' && !ispunct(name[i]))
            return false;
    }
    return true;
}
void enterUserName(account &user)
{
    string name;
    do
    {
        cout << "Enter your account name: ";
        getline(cin, name);
    } while (checkInvalidName(name));

    user.name = name;
}

void printRanking(vector<account> highscores, account user)
{
    system("CLS");
    string score = ">> YOUR SCORE: " + to_string(user.score) + " POINTS <<";
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                        ==============================================                         |" << endl;
    cout << "|                        |          TOP 5 HIGHSCORE ACCOUNTS          |                         |" << endl;
    cout << "|                        ==============================================                         |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                ACCOUNT'S NAME                SCORE                            |" << endl;
    cout << "|                                                                                               |" << endl;
    int limit = min(6, int(highscores.size()));
    for (int i = 0; i < limit; i++)
        cout << "|                           " << (i + 1) << ".   " << left << setw(20) << setfill(' ') << highscores[i].name << "          " << left << setw(6) << setfill(' ') << highscores[i].score << "                           |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|" << center(score, 95) << "|" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                        ___END GAME___                                         |" << endl;
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
}

void ranking(vector<account> &highscores, account user)
{
    highscores.push_back(user);
    int sizeOfVector = highscores.size();
    if (sizeOfVector == 1)
        return;
    else
    {
        for (int i = 0; i < sizeOfVector - 1; i++)
        {
            int index = i;
            for (int a = i + 1; a < sizeOfVector; a++)
            {
                if (highscores[a].score > highscores[index].score)
                    index = a;
            }
            swap(highscores[index], highscores[i]);
        }
    }
}

void getRankingList(account user)
{
    vector<account> highscores;
    account temp;
    ifstream fin("ranking.txt");

    string data, line;
    while (getline(fin, data))
    {
        stringstream ss(data);
        getline(ss, line, '/');
        temp.name = line;
        getline(ss, line);
        temp.score = stoi(line);
        highscores.push_back(temp);
    }
    fin.close();

    ranking(highscores, user);

    ofstream fout;
    fout.open("ranking.txt");
    int limit = min(6, int(highscores.size()));

    for (int i = 0; i < limit; i++)
        fout << highscores[i].name << '/' << highscores[i].score << endl;
    fout.close();
    printRanking(highscores, user);
}

bool win(account &user, string word)
{
    char c;
    do
    {
        system("CLS");
        cout << "+-----------------------------------------------------------------------------------------------+" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                           =========================================                           |" << endl;
        cout << "|                           *    YOU WIN! YOU'VE GUESS THE WORD !   *                           |" << endl;
        cout << "|                           =========================================                           |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                           (_) __                 HIDDEN WORD:                                 |" << endl;
        cout << "|                         __/|/                    " << left << setw(45) << setfill(' ') << word << "|" << endl;
        cout << "|                            |                                                                  |" << endl;
        cout << "|                           / \\          Press enter to continue game...                        |" << endl;
        cout << "|                                               Press 'X' to stop game...                       |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "|                                                                                               |" << endl;
        cout << "+-----------------------------------------------------------------------------------------------+" << endl;
        cin.get(c);

    } while (c != '\n' && toupper(c) != 'X');

    if (c == '\n')
        return true;
    else
    {
        cin.ignore();
        enterUserName(user);  // nhap ten
        getRankingList(user); // in top 5 account cao nhat
        return false;
    }
}
void lose(account &user, string word)
{
    system("CLS");

    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                           =========================================                           |" << endl;
    cout << "|                           *    GAME OVER! BETTER LUCK NEXT TIME   *                           |" << endl;
    cout << "|                           =========================================                           |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                               _______                                                         |" << endl;
    cout << "|                              |       |      HIDDEN WORD:                                      |" << endl;
    cout << "|                              |       |                " << left << setw(45) << setfill(' ') << word << right << "|" << endl;
    cout << "|                              |      (_)     YOUR SCORE:                                       |" << endl;
    cout << "|                              |      /|\\           " << left << setw(3) << setfill(' ') << user.score << "POINT                                    |" << endl;
    cout << "|                              |      / \\                                                       |" << endl;
    cout << "|                              |                                                                |" << endl;
    cout << "|                           ___|                                                                |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "|                                                                                               |" << endl;
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;

    enterUserName(user);  // nhap ten
    getRankingList(user); // in top 5 account cao nhat
}

//------------------------------ GAME LOOP -------------------------------------
void startGame()
{
    account user;
    user.score = 0;
    int mode; // chế độ chơi (1 dễ, 2 tb, 3 khó)

    pair<string, string> wordPair; // random từ file
    string hint, word;             // hint và từ cần đoán
    vector<int> check;             // lưu index của mấy từ đã random

    char c; // chữ cái ng dùng nhập

    int lives;               // số mạng hiện tại
    bool isWin;              // thắng chưa? chưa =))
    bool keepPlaying = true; // chơi tiếp không

    // bảng cập nhật thuộc tính của các chữ cái

    // 1. Màn hình Init
    mode = showInit();

    // 2. Random từ
    string modeStr = mode == 1 ? "easy.txt" : mode == 2 ? "medium.txt"
                                                        : "hard.txt";

    while (keepPlaying)
    {
        lives = 7;
        isWin = false;
        unordered_map<char, bool> ABCMap =
            {{'M', false}, {'N', false}, {'B', false}, {'V', false}, {'C', false}, {'X', false}, {'Z', false}, {'L', false}, {'K', false}, {'J', false}, {'H', false}, {'G', false}, {'F', false}, {'D', false}, {'S', false}, {'A', false}, {'P', false}, {'O', false}, {'I', false}, {'U', false}, {'Y', false}, {'T', false}, {'R', false}, {'E', false}, {'W', false}, {'Q', false}};
        wordPair = handleRandom(modeStr, check);
        word = wordPair.second;
        hint = wordPair.first;
        // 3. Bắt đầu đoán từ
        while (lives > 0 && !isWin)
        {
            system("CLS");
            showHangman(lives);
            cout << "|                                                                                               |" << endl;
            showHiddenWord(word, hint, ABCMap);
            cout << endl;
            cout << "|                                                                                               |" << endl;
            printABC(ABCMap);
            cout << endl;
            cout << "|                                                                                               |" << endl;
            cout << "+-----------------------------------------------------------------------------------------------+";

            cout << "\nEnter a letter: ";
            cin >> c;
            c = toupper(c);

            if (checkLetter(ABCMap, word, c))
            {
                ABCMap[c] = true;
            }
            else
            {
                ABCMap[c] = true;
                lives--;
            }

            // hết lives -> LOSE
            if (lives == 0)
            {
                isWin = false;
                break;
            }
            // đoán đúng hết -> WIN
            if (allLettersGuessed(word, ABCMap))
            {
                isWin = true;
                break;
            }
        }

        // My
        // 4. Kết quả thắng thua + lấy tên ng chơi
        if (isWin == true)
        {
            cin.ignore();
            switch (mode)
            {
            case 1:
                user.score += 10;
                break;
            case 2:
                user.score += 15;
                break;
            case 3:
                user.score += 20;
                break;
            default:
                break;
            }
            keepPlaying = win(user, word);
        }
        else
        {
            cin.ignore();
            lose(user, word);
            keepPlaying = false;
        }
    }
}

int main()
{
    startGame();
    return 0;
}