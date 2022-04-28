#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <conio.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath>

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

class MyInput {

public:

    double InputData(string text) {

        string xStr = "";
        double x = 0, result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!isNumber) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - �� �����!" << endl << endl;
            }
            else if (result <= 0) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ���� ������ ����!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max) {

        double result;

        while (true) {
            result = InputData(text);

            if (result != (int)result) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ���� �����!" << endl << endl;
            }
            else if (result < min || result > max) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ������ � ���������� [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }



};

class MyRandom {

public:
    double MIN_RANDOM = 10, MAX_RANDOM = 1000;

    bool isRandomData() {
        cout << "������������� ������ ��������� ������� [y/n]?" << endl;

        string answer = GetLine();

        transform(answer.begin(), answer.end(), answer.begin(), tolower);

        return answer == "y" || answer == "";
    }

    double GetRandom(int min, int max) {
        return rand() % (max - min) - min;
    }

};

class Task6 {

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "������ ������ ������ ��������������� ������ ��������� �� ������ �� 3 �������." << endl;
        cout << "���������, ������� ������� ������ ��������� ���� �������." << endl << endl;

        int MIN_DETALS = 1;
        int MAX_DETALS = 1000;

        int MIN_TIME_PROCESSING = 10;
        int MAX_TIME_PROCESSING = 600;

        double timeInMachine1, timeInMachine2, timeInMachine3;
        double timeDetalInAllMachines, timeInAllMachines = 0;

        MyRandom myRandom = *new MyRandom();
        MyInput myInput = *new MyInput();

        
        int countDetals = myInput.InputIntData("������� ����������� ������� ������� ����� ����������: ", MIN_DETALS, MAX_DETALS);

        bool isRandomData = myRandom.isRandomData();

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
        int pos = size - 1; //� ������ �������
        double item, beforeRes = 0, afterRes = 0;

        for (int i = 0; i < size; ++i, --pos) {
            item = atoi(string({ (char) beforeStr[i]}).c_str());
            item = item * pow(2, pos);
            beforeRes += item;
        }

        if (after != 0) {

            string afterStr = AfterTrim(to_string(after));

            size = beforeStr.size();
            pos = 1; //� ������ �������

            for (int i = 2; i < size; ++i, ++pos) {
                item = atoi(string({ (char) afterStr[i] }).c_str());
                item = item * (1 / pow(2, pos));
                afterRes += item;
            }
        }

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
        }/*
        else if (select == "46") {
            Task46 task46 = *new Task46();
            task46.Init();
        }*/
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

