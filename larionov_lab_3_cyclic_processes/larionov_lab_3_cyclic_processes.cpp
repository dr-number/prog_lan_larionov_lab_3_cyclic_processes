#include <iostream>
#include <Windows.h>
#include <random>
#include <regex>

#define PI 3.14159265

using namespace std;
HANDLE handleConsole;

enum ConsoleColor
{
    Blue = 1,
    Green = 2,
    Red = 4,
    Yellow = 14,
    White = 15
};

string GetLine() {
    string line;
    getline(cin, line);
    cin.clear();
    return line;
}

string RoundStr(float var, int after = 2) {

    string s = to_string(var);
    int size = s.size();

    string result = "";
    bool isAfter = false;
    int afterCount = 0;

    for (int i = 0; i < size; ++i) {

        if (afterCount == after)
            break;

        if (isAfter)
            ++afterCount;

        if (!isAfter && s[i] == ',')
            isAfter = true;

        result += s[i];

    }

    return result;
}

float Round(float var)
{
    // 37.66666 * 100 = 3766.66
    // 3766.66 + .5 = 3767.16 ��� �������� ����������

    // ����� ������ ��� int � �������� 3767
    // ����� ����� �� 100, ������� �������� ������������� � 37,67

    float value = (int)(var * 100 + .5);
    return stod(RoundStr((float)value / 100));

}

class MyInput {

public:

public:
    bool isDouble(string str) {
        return regex_match(str, regex("^[-]?[0-9]*?,?[0-9]*"));
    }

    bool isNum(string str) {
        return regex_match(str, regex("^[-]?[0-9]*"));
    }

    double InputData(string text, int min, int max, int defaultValue = -1) {

        string xStr = "";
        double result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            if (xStr == "" && defaultValue != -1)
                return defaultValue;


            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!(isNumber && isDouble(xStr))) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - �� �����!" << endl << endl;
            }
            else if (result > max || result < min) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ������ � ���������� [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max, int defaultValue = -1) {

        string xStr = "";
        double result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            if (xStr == "" && defaultValue != -1)
                return defaultValue;


            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!(isNumber && isNum(xStr))) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - �� �����!" << endl << endl;
            }
            else if (result > max || result < min) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ������ � ���������� [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

};

class MyQuestion {

public:
    static const string QUESTION_RANDOM_DATA = "������������� ������ ��������� ������� [y/n]?";
    static const string QUESTION_IN_ORDER_DATA = "����� ����� �� ������� [y/n]?";

    bool isQuestion(string textQuestion) {

        cout << textQuestion << endl;
        string answer = GetLine();

        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        return answer == "y" || answer == "";
    }
};

class MyRandom {

public:
    double MIN_RANDOM = 10, MAX_RANDOM = 1000;

    double GetRandom(int min, int max) {

        random_device random_device; // �������� ��������.
        mt19937 generator(random_device()); // ��������� ��������� �����.

        // (����� ������� ���� ���������������� ��������, ����� ����� ������)
        uniform_int_distribution<> distribution(min, max); // ����������� ������������� [min, max]

        return distribution(generator);

        //return rand() % (max - min) - min;
        //return rand() % max + min;
    }

};

class Task6 {
private:
    const int MIN_DETALS = 1;
    const int MAX_DETALS = 1000;

    const int MIN_TIME_PROCESSING = 10;
    const int MAX_TIME_PROCESSING = 600;

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "������ ������ ������ ��������������� ������ ��������� �� ������ �� 3 �������." << endl;
        cout << "���������, ������� ������� ������ ��������� ���� �������." << endl << endl;

        double timeInMachine1, timeInMachine2, timeInMachine3;
        double timeDetalInAllMachines, timeInAllMachines = 0;

        MyRandom myRandom = *new MyRandom();
        MyQuestion myQuestion = *new MyQuestion();
        MyInput myInput = *new MyInput();

        
        int countDetals = myInput.InputIntData("������� ����������� ������� ������� ����� ����������: ", MIN_DETALS, MAX_DETALS);

        bool isRandomData = myQuestion.isQuestion(MyQuestion::QUESTION_RANDOM_DATA);

        for (int i = 0; i < countDetals; ++i) {

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "\n��������� ������ " << (i + 1) << " �� " << countDetals << endl;

            if (isRandomData) {
                timeInMachine1 = myRandom.GetRandom(MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
                timeInMachine2 = myRandom.GetRandom(MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
                timeInMachine3 = myRandom.GetRandom(MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
            }
            else {
                timeInMachine1 = myInput.InputData("������� ����� ��������� ������ �� ������ �1 (� ��������): ");
                timeInMachine2 = myInput.InputData("������� ����� ��������� ������ �� ������ �2 (� ��������): ");
                timeInMachine3 = myInput.InputData("������� ����� ��������� ������ �� ������ �3 (� ��������): ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "\n��������� �� ������ �1 ��������: " << timeInMachine1 << " ���." << endl;
            cout << "��������� �� ������ �2 ��������: " << timeInMachine2 << " ���." << endl;
            cout << "��������� �� ������ �3 ��������: " << timeInMachine3 << " ���." << endl;

            timeDetalInAllMachines = timeInMachine1 + timeInMachine2 + timeInMachine3;

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "C�������� ����� ��������� ������: " << timeDetalInAllMachines << " ���." << endl << endl;

            timeInAllMachines += timeDetalInAllMachines;
        }

        SetConsoleTextAttribute(handleConsole, Blue);
        cout << "��������� ���� ������� ��������: " << timeInAllMachines << " ������" << endl << endl;
    }

};

class Task36 {
private:
    string inputBin(string text) {

        int size;
        string item = "", result = "";
        bool isPoint = false, isCorrect = true;

        while (true) {

            isCorrect = true;
            isPoint = false;

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            result = GetLine();
            size = strlen(result.c_str());

            if (size != 0 && result[0] != ',' && result[size - 1] != ',') {

                for (int i = 0; i < size; ++i) {

                    item = result[i];

                    if (!isPoint && item == ",") {
                        isPoint = true;
                        continue;
                    }

                    if (isPoint && item == ",") {
                        isCorrect = false;
                        break;
                    }

                    if (item != "0" && item != "1") {
                        isCorrect = false;
                        break;
                    }
                }
        }
        else
            isCorrect = false;

            if (!isCorrect) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << result + " - �� �������� �����!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    string BeforeTrim(string str, string symbol = ",") {

        size_t index = str.find(symbol);

        if (index == str.npos)
            return str;

        return str.substr(0, index);
    }

    string AfterTrim(string str, string symbol = "0") {

        while(str[str.size() - 1] == '0')
            str = str.substr(0, str.size() - 1);

        return str;
    }

    double BinToDec(string bin) {

        double before;
        double after = modf(atof(bin.c_str()), &before);

        string beforeStr = BeforeTrim(to_string(before));
      
        int size = beforeStr.size();
        int pos = size - 1;
        double item, beforeRes = 0, afterRes = 0;

        for (int i = 0; i < size; ++i, --pos) {
            item = atoi(string({ (char) beforeStr[i]}).c_str());

            cout << item << " * 2^" << pos;

            if (i != size - 1)
                cout << " + ";
            else
                cout << " = ";

            item = item * pow(2, pos);
            beforeRes += item;
        }

        cout << beforeRes;

        if (after != 0) {

            string afterStr = AfterTrim(to_string(after));

            size = afterStr.size();
            pos = 1;

            for (int i = 2; i < size; ++i, ++pos) {
                item = atoi(string({ (char) afterStr[i] }).c_str());

                cout << item << " * (1 / (2^" << pos << "))";

                if (i != size - 1)
                    cout << " + ";
                else
                    cout << " = ";

                item = item * (1 / pow(2, pos));
                afterRes += item;
            }

            cout << beforeRes << " + " << afterRes;
        }

        cout << endl;
        return beforeRes + afterRes;
    }

public: 
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "��������� ���������� ������������� ��������� �����" << endl << endl;
        string binStr = inputBin("������� ����� � �������� ������� ���������: ");

        SetConsoleTextAttribute(handleConsole, Green);
        cout << "� ���������� ������� ���������: " << BinToDec(binStr) << endl << endl;

    }
};

class Task46 {
private:
    bool IsPrime(int n)
    {
        if (n == 0 || n == 1) 
            return false;

        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                return false;
                break;
            }
        }

        return true;
    }

    int GetReverse(int n) {
        
        string result = "";
        string str = to_string(n);

        int size = str.size();

        for (int i = size - 1; i >= 0; --i)
            result += str[i];

        return atoi(result.c_str());
    }


    bool IsSuperPrimeNumber(int number){
        return IsPrime(number) && IsPrime(GetReverse(number));
    }

public:
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "��������� ������������ �����" << endl << endl;

        int MIN_COUNT = 1;
        int MAX_COUNT = 10000;

        int MIN_NUMBER = 1;
        int MAX_NUMBER = 5000;

        MyInput myInput = *new MyInput();
        int count = myInput.InputIntData("������� ����� ����� ����������: ", MIN_COUNT, MAX_COUNT);

        MyRandom myRandom = *new MyRandom();
        MyQuestion myQuestion = *new MyQuestion();

        bool isInOrderData = myQuestion.isQuestion(myQuestion.QUESTION_IN_ORDER_DATA);
        
        int number = 0;
        int countSuperPrimeNumber = 0;

        for (int i = 0; i < count; ++i) {

            if (isInOrderData)
                number = i;
            else 
                number = myInput.InputIntData("������� ����� ����� (" + to_string(i + 1) + " �� " + to_string(count) + "): ", MIN_NUMBER, MAX_NUMBER);

            if (IsSuperPrimeNumber(number)) {
                SetConsoleTextAttribute(handleConsole, Green);
                cout << number << " - ������������ �����" << endl;
                ++countSuperPrimeNumber;
            }
            else if(!isInOrderData) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << number << " - �� ������������ �����" << endl;
            }

            if (!isInOrderData)
                cout << endl;

        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << countSuperPrimeNumber << " ������ �� " << count << " ��������� ��������" << endl;

        SetConsoleTextAttribute(handleConsole, White);

    }
};


int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    SetConsoleTextAttribute(handleConsole, White);

    cout << "���� 3. ����������� �������������� ��������" << endl;
    cout << "�������� ������ �������. ��. 110�" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\n������� ����� ������" << endl;
        cout << "6)	������ ������ ������ ��������������� ������ ��������� �� ������ �� 3 �������." << endl;
        cout << "���������, ������� ������� ������ ��������� ���� �������." << endl << endl;

        cout << "36) ��������� ���������� ������������� ��������� �����" << endl << endl;

        cout << "46) ��������� ������������ �����" << endl << endl;


        cout << endl << "��� ������ ������� \"0\": ";

        select = GetLine();

        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }/*
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        }*/
        else if (select == "36") {
            Task36 task36 = *new Task36();
            task36.Init();
        }
        else if (select == "46") {
            Task46 task46 = *new Task46();
            task46.Init();
        }
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\n������������ ������!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

