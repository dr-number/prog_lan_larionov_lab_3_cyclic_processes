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
    // 3766.66 + .5 = 3767.16 для значения округления

    // затем вводим тип int в значение 3767
    // затем делим на 100, поэтому значение преобразуется в 37,67

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

    double InputData(string text, int min, int max, double defaultValue = -1) {

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
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (result > max || result < min) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно лежать в промежутке [" << min << "; " << max << "]!" << endl << endl;
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
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (result > max || result < min) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно лежать в промежутке [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

};

class MyQuestion {

public:
    const string QUESTION_RANDOM_DATA = "Сгенерировать данные случайным образом [y/n]?";
    const string QUESTION_IN_ORDER_DATA = "Взять числа по порядку [y/n]?";
    const string QUESTION_SHOW_CALC = "Показывать ход вычислений [y/n]?";

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

        random_device random_device; // Источник энтропии.
        mt19937 generator(random_device()); // Генератор случайных чисел.

        // (Здесь берется одно инициализирующее значение, можно брать больше)
        uniform_int_distribution<> distribution(min, max); // Равномерное распределение [min, max]

        return distribution(generator);

        //return rand() % (max - min) - min;
        //return rand() % max + min;
    }

};

class MyPrint {
public:
    void PrintInfo(string type, string info, string moreInfo = "") {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << type << " ";

        SetConsoleTextAttribute(handleConsole, Green);
        cout << info;

        if (moreInfo != "") {
            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << " " << moreInfo;
        }

        cout << endl;
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

        cout << "Каждая деталь должна последовательно пройти обработку на каждом из 3 станков." << endl;
        cout << "Вычислять, сколько времени займет обработка всех деталей." << endl << endl;

        double timeInMachine1, timeInMachine2, timeInMachine3;
        double timeDetalInAllMachines, timeInAllMachines = 0;

        MyRandom myRandom = *new MyRandom();
        MyQuestion myQuestion = *new MyQuestion();
        MyInput myInput = *new MyInput();

        
        int countDetals = myInput.InputIntData("Введите колличество деталей которое нужно обработать: ", MIN_DETALS, MAX_DETALS);

        bool isRandomData = myQuestion.isQuestion(myQuestion.QUESTION_RANDOM_DATA);

        for (int i = 0; i < countDetals; ++i) {

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "\nОбработка детали " << (i + 1) << " из " << countDetals << endl;

            if (isRandomData) {
                timeInMachine1 = myRandom.GetRandom(MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
                timeInMachine2 = myRandom.GetRandom(MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
                timeInMachine3 = myRandom.GetRandom(MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
            }
            else {
                timeInMachine1 = myInput.InputData("Введите время обработки детали на станке №1 (в секундах): ", MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
                timeInMachine2 = myInput.InputData("Введите время обработки детали на станке №2 (в секундах): ", MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
                timeInMachine3 = myInput.InputData("Введите время обработки детали на станке №3 (в секундах): ", MIN_TIME_PROCESSING, MAX_TIME_PROCESSING);
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "\nОбработка на станке №1 занимает: " << timeInMachine1 << " сек." << endl;
            cout << "Обработка на станке №2 занимает: " << timeInMachine2 << " сек." << endl;
            cout << "Обработка на станке №3 занимает: " << timeInMachine3 << " сек." << endl;

            timeDetalInAllMachines = timeInMachine1 + timeInMachine2 + timeInMachine3;

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "Cуммарное время обработки детали: " << timeDetalInAllMachines << " сек." << endl << endl;

            timeInAllMachines += timeDetalInAllMachines;
        }

        SetConsoleTextAttribute(handleConsole, Blue);
        cout << "Обработка всех деталей занимает: " << timeInAllMachines << " секунд" << endl << endl;
    }

};

class Task16 {
private:
    const double DEFAULT_E = 0.00001;
    const double MIN_E = 0.000000001;
    const double MAX_E = 0.999999999;

    const int DEFAULT_K = 2;
    const int MIN_K = DEFAULT_K;
    const int MAX_K = 10000;

    const int DEFAULT_PRINT_PERIOD = 100;
    const int MIN_PRINT_PERIOD = DEFAULT_PRINT_PERIOD;
    const int MAX_PRINT_PERIOD = 1000;

    int GetN(int k, double e, bool isPrint, int periodPrint = 10) {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        int result = k;
        double x = 1;

        double check;
        bool isPeriodPrint;
        bool isCheck;

        for (int n = 1;;k++, n++)
        {
            x *= 1 - (1 / pow(k, 2));

            check = abs(x - 0.5);
            isCheck = check < e;

            isPeriodPrint = (n % periodPrint == 0 || isCheck);

            if (isPrint && isPeriodPrint) {
                SetConsoleTextAttribute(handleConsole, White);
                cout << "1 - " << k << "^-2 = " << x << " - 0.5 = " << x - 0.5;
            }

            if (isCheck) {

                if (isPrint) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    
                    if(check < e)
                        cout << " < ";
                    else if (check == e)
                        cout << " = ";
                        
                    cout << e << endl;
                }

                result = k;
                break;
            }
            else if (isPrint && isPeriodPrint) {
                SetConsoleTextAttribute(handleConsole, Red);
                check == e ? cout << " = " : cout << " > ";
            }

            if (isPrint && isPeriodPrint)
                cout << e << endl;
        }

        return result;
    }

public:
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "16) Вычислить, сколько сомножителей надо взять в произведении, чтобы равенство выполнялось с указанной точностью" << endl << endl;
        
        cout << "(бесконечность) " << endl;
        cout << "     ###" << endl;
        cout << "     # #  = (1 - 1 / k^2) = 0.5" << endl;
        cout << "     # #" << endl << endl;

        MyInput myInput = *new MyInput();
        
        int k = myInput.InputIntData("Введите значение k [по умолчанию " + to_string(DEFAULT_K) + "]: ", MIN_K, MAX_K, DEFAULT_K);
        double e = myInput.InputData("Введите точность вычислений [по умолчанию " + to_string(DEFAULT_E) + "]: ", MIN_E, MAX_E, DEFAULT_E);

        MyQuestion myQuestion = *new MyQuestion();
        bool isShowCalc = myQuestion.isQuestion(myQuestion.QUESTION_SHOW_CALC);

        int printPeriod = DEFAULT_PRINT_PERIOD;

        if(isShowCalc)
            printPeriod = myInput.InputIntData("Введите переодичность вывода промежуточных результатов [по умолчанию " + to_string(DEFAULT_PRINT_PERIOD) + "]: ", MIN_PRINT_PERIOD, MAX_PRINT_PERIOD, DEFAULT_PRINT_PERIOD);

        cout << "\nИсходные данные:" << endl;

        MyPrint myPrint = *new MyPrint();
        myPrint.PrintInfo("k:", to_string(k));
        myPrint.PrintInfo("Точность вычислений:", to_string(e));

        if(isShowCalc)
            myPrint.PrintInfo("Переодичность вывода промежуточных результатов:", to_string(printPeriod));

        cout << endl;

        myPrint.PrintInfo("\nНужно взять:", to_string(GetN(k, e, isShowCalc, printPeriod)), "сомножителей");

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
                cout << endl << result + " - не двоичное число!" << endl << endl;
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

        if (after == 0 && before == 0)
            return 0;

        string beforeStr = BeforeTrim(to_string(before));
      
        int size = beforeStr.size();
        int pos = size - 1;
        double item, beforeRes = 0, afterRes = 0;

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (after != 0) {
            SetConsoleTextAttribute(handleConsole, White);
            cout << "\n\nЦелая часть: ";
        }

        if (before != 0) {
            for (int i = 0; i < size; ++i, --pos) {
                item = atoi(string({ (char)beforeStr[i] }).c_str());

                SetConsoleTextAttribute(handleConsole, Yellow);
                cout << item << " * 2^" << pos;

                if (i != size - 1) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    cout << " + ";
                }
                else {
                    SetConsoleTextAttribute(handleConsole, Blue);
                    cout << " =\n";

                    int pos2 = size - 1;
                    double item2;
                    int tmp;

                    for (int i = 0; i < size; ++i, --pos2) {
                        item2 = atoi(string({ (char)beforeStr[i] }).c_str());

                        tmp = item2 * pow(2, pos2);

                        if (tmp != 0) {

                            if (i != 0) {
                                SetConsoleTextAttribute(handleConsole, Green);
                                cout << " + ";
                            }

                            SetConsoleTextAttribute(handleConsole, Yellow);
                            cout << tmp;

                        }

                        if (i == size - 1) {
                            SetConsoleTextAttribute(handleConsole, Blue);
                            cout << " = ";
                        }

                    }

                }

                item = item * pow(2, pos);
                beforeRes += item;
            }

            SetConsoleTextAttribute(handleConsole, Green);
            cout << beforeRes;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Green);
            cout << 0;
        }

        double result = beforeRes;

        if (after != 0) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << "\n\nДробная часть: ";

            string afterStr = AfterTrim(to_string(after));

            size = afterStr.size();
            pos = 1;

            for (int i = 2; i < size; ++i, ++pos) {
                item = atoi(string({ (char) afterStr[i] }).c_str());

                SetConsoleTextAttribute(handleConsole, Yellow);
                cout << item << " * 2^-" << pos;

                if (i != size - 1) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    cout << " + ";
                }
                else {
                    SetConsoleTextAttribute(handleConsole, Blue);
                    cout << " = ";

                    double item2;
                    int pos2 = 1;

                    for (int i = 2; i < size; ++i, ++pos2) {
                        item2 = atoi(string({ (char)afterStr[i] }).c_str());

                        SetConsoleTextAttribute(handleConsole, Yellow);
                        cout << item2 * (1 / pow(2, pos2));

                        if (i != size - 1) {
                            SetConsoleTextAttribute(handleConsole, Green);
                            cout << " + ";
                        }
                        else {
                            SetConsoleTextAttribute(handleConsole, Blue);
                            cout << " = ";
                        }
                    }
                }

                item = item * (1 / pow(2, pos));

                afterRes += item;
            }

            result = beforeRes + afterRes;

            if (after != 0) {

                SetConsoleTextAttribute(handleConsole, White);
                cout << "\n\nИтоговый результат: ";

                SetConsoleTextAttribute(handleConsole, Green);
                cout << beforeRes;

                SetConsoleTextAttribute(handleConsole, Yellow);
                cout << " + ";

                SetConsoleTextAttribute(handleConsole, Green);
                cout << afterRes;

                SetConsoleTextAttribute(handleConsole, Blue);
                cout << " = ";

                SetConsoleTextAttribute(handleConsole, Green);
                cout << result;
            }
        }

        cout << endl;
        return result;
    }

public: 
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "Вычислить десятичное представление двоичного числа" << endl << endl;
        string binStr = inputBin("Введите число в двоичной системе счисления: ");

        SetConsoleTextAttribute(handleConsole, Green);
        cout << "\nВ десятичной системе счисления: " << BinToDec(binStr) << endl << endl;

    }
};

class Task26 {
private:
    const double DEFAULT_X = 45;
    const double MIN_X = 1;
    const double MAX_X = 10000;

    const double DEFAULT_E = 0.00001;
    const double MIN_E = 0.000000001;
    const double MAX_E = 0.999999999;

    double RowCos(double x)
    {
        int n = 0;
        double result = 1, a = 1;

        for (int i = 1; i <= 10; i++)
        {
            a = -(a * pow(x, 2)) / ((2 * n + 2) * (2 * n + 1));
            result += a;
            n++;
        }

        return result;
    }
public:
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        MyQuestion myQuestion = *new MyQuestion();
        double x, e;

        if (myQuestion.isQuestion(myQuestion.QUESTION_RANDOM_DATA) {
            MyRandom myRandom = *new MyRandom();
        }
        else {
            MyInput myInput = *new MyInput();
            x = myInput.InputData("Введите x в градусах [по умолчанию " + to_string(DEFAULT_X) + "]: ", MIN_X, MAX_X, DEFAULT_X);
            e = myInput.InputData("Введите погрешность вычислений [по умолчанию " + to_string(DEFAULT_E) + "]: ", MIN_X, MAX_X, DEFAULT_E);
        }

        MyPrint myPrint = *new MyPrint();

    }
};

class Task46 {
private:
    const int MIN_COUNT = 1;
    const int MAX_COUNT = 10000;

    const int MIN_NUMBER = 1;
    const int MAX_NUMBER = 5000;

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

        cout << "Вычислить сверхпростые числа" << endl << endl;

        MyInput myInput = *new MyInput();
        int count = myInput.InputIntData("Сколько чисел нужно обработать: ", MIN_COUNT, MAX_COUNT);

        MyRandom myRandom = *new MyRandom();
        MyQuestion myQuestion = *new MyQuestion();

        bool isInOrderData = myQuestion.isQuestion(myQuestion.QUESTION_IN_ORDER_DATA);
        
        int number = 0;
        int countSuperPrimeNumber = 0;

        for (int i = 0; i < count; ++i) {

            if (isInOrderData)
                number = i;
            else 
                number = myInput.InputIntData("Введите целое число (" + to_string(i + 1) + " из " + to_string(count) + "): ", MIN_NUMBER, MAX_NUMBER);

            if (IsSuperPrimeNumber(number)) {
                SetConsoleTextAttribute(handleConsole, Green);
                cout << number << " - сверхпростое число" << endl;
                ++countSuperPrimeNumber;
            }
            else if(!isInOrderData) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << number << " - не сверхпростое число" << endl;
            }

            if (!isInOrderData)
                cout << endl;

        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << countSuperPrimeNumber << " числел из " << count << " оказались простыми" << endl;

        SetConsoleTextAttribute(handleConsole, White);

    }
};

class Task56 {
private:
    const int MIN_N = 10;
    const int MAX_N = 10000;
    const int DEFAULT_N = 30;

    double GetPart(int n, bool isPrint) {

        double E = exp(n);
        double P = pow(2, n);
        double division = E * P;
        double result = 1 / division;

        if (isPrint) {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "a(" << n << ") = ";

            SetConsoleTextAttribute(handleConsole, White);

            cout << " 1 / (e^" << n << " * 2^" << n << ") = ";
            cout << " 1 / (" << E << " * " << P << ") = ";
            cout << " 1 / " << division << " = ";
        }

        return result;
    }

public:
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "Вычислить разности между первым и остальными элементами исходной последовательности" << endl << endl;

        cout << "a(n) = 1 / (e^n * 2^n)" << endl;

        MyQuestion myQuestion = *new MyQuestion();

        int n;

        bool isShowCalc = myQuestion.isQuestion(myQuestion.QUESTION_SHOW_CALC);
        
       
        MyInput myInput = *new MyInput();
        n = myInput.InputIntData("Введите количество элементов последовательности (n) [по умолчанию " + to_string(DEFAULT_N) + "]: ", MIN_N, MAX_N, DEFAULT_N);
        

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "\nПервый элемент последовательности: " << endl;

        double part1 = GetPart(1, isShowCalc);
        SetConsoleTextAttribute(handleConsole, Blue);

        cout << part1 << endl << endl;

        double item;

        for (int i = 2; i <= n; ++i) {

            item = GetPart(i, isShowCalc);

            if (isShowCalc) {
                SetConsoleTextAttribute(handleConsole, Green);
                cout << item << endl;
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Разность: ";

            SetConsoleTextAttribute(handleConsole, Blue);
            cout << part1;
            
            SetConsoleTextAttribute(handleConsole, Green);
            cout << " - " << item << " = ";

            SetConsoleTextAttribute(handleConsole, White);
            cout << part1 - item << endl << endl;
        }
    }
};

int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    SetConsoleTextAttribute(handleConsole, White);

    cout << "Тема 3. Циклические вычислительные процессы" << endl;
    cout << "Ларионов Никита Юрьевич. гр. 110з" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\nВведите номер задачи" << endl;
        cout << "6)	Каждая деталь должна последовательно пройти обработку на каждом из 3 станков." << endl;
        cout << "Вычислять, сколько времени займет обработка всех деталей." << endl << endl;

        cout << "16) Вычислить, сколько сомножителей надо взять в произведении, чтобы равенство выполнялось с указанной точностью" << endl << endl;

        cout << "26) Разложить в ряд cos(x) с заданной погрешностью" << endl << endl;

        cout << "36) Вычислить десятичное представление двоичного числа" << endl << endl;

        cout << "46) Вычислить сверхпростые числа" << endl << endl;

        cout << "56) Вычислить разности между первым и остальными элементами исходной последовательности" << endl << endl;

        cout << endl << "Для выхода введите \"0\": ";

        select = GetLine();

        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        }
        else if (select == "26") {
            Task26 task26 = *new Task26();
            task26.Init();
        }
        else if (select == "36") {
            Task36 task36 = *new Task36();
            task36.Init();
        }
        else if (select == "46") {
            Task46 task46 = *new Task46();
            task46.Init();
        }
        else if (select == "56") {
            Task56 task56 = *new Task56();
            task56.Init();
        }
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\nНекорректные данные!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

