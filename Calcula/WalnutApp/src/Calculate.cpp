#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
using namespace std;

void ToLowerCase(string &s)
{
    string r = "";
    for (auto i : s)
    {
        r += tolower(i);
    }
    s = r;
}
static double Function(string func, double value)
{
    ToLowerCase(func);
    int sign = 1;
    double result = value;
    if (func.size() > 0) if (func[0] == '-') { 
        sign = -1; 
        func.replace(0, 1, "");
    }
    if (func == "sin" || func == "sine") result = sin(value * M_PI / 180.0L);
    else if (func == "cos" || func == "cosine") result = cos(value * M_PI / 180.0L);
    else if (func == "tan" || func == "tangent") result = tan(value * M_PI / 180.0L);
    else if (func == "cosec" || func == "cosecant" || func == "csc") result = 1.0L / sin(value * M_PI / 180.0L);
    else if (func == "sec" || func == "secant") result = 1.0L / cos(value * M_PI / 180.0L);
    else if (func == "cot" || func == "cotan" || func == "cotangent") result = 1.0L / tan(value * M_PI / 180.0L);
    else if (func == "ln") result = log(value);
    else if (func == "log") result = log10(value);
    else if (func == "arcsin" || func == "asin") result = asin(value) * 180.0L / M_PI;
    else if (func == "arccos" || func == "acos") result = acos(value) * 180.0L / M_PI;
    else if (func == "arctan" || func == "atan") result = atan(value) * 180.0L / M_PI;
    else if (func == "arcsec" || func == "asec") result = acos(1.0L / value) * 180.0L / M_PI;
    else if (func == "arccsc" || func == "acsc") result = asin(1.0L / value) * 180.0L / M_PI;
    else if (func == "arccot" || func == "acot") { 
        result = atan(1.0L / value);
        if (value < 0) result += M_PI;   
        result *=  180.0L / M_PI;
    }
    return sign * result;
}

vector<string> allOparations = { "+", "-", "*", "/", "^" };
bool isOparation(string alphabet) {
    //cout << "Alphabet: " << alphabet << endl;
    for (auto i : allOparations) {
        //cout << "Check: " << i << endl;
        if (alphabet == i) return 1;
    }
    return 0;
}
bool isOparation(char alphabet) {
    //cout << "Alphabet: " << alphabet << endl;
    for (auto i : allOparations) {
        //cout << "Check: " << i << endl;
        if (alphabet == i[0]) return 1;
    }
    return 0;
}

enum readType {
    None, Oparation, Number
};
/*
static string Read(string problem, unsigned& index) {
    string read = "";
    while (problem[index] == ' ') index++;
    switch (problem[index]) {
        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
            do {
                read += problem[index];
                index++;
                if (index >= problem.size()) break;
            } while (problem[index] >= '0' && problem[index] <= '9');
            break;
        case '+':case '*':case '/':case '^':
            read += problem[index];
            index++;
            break;
        case '-':
            read += '-';
            index++;
            while (problem[index] >= '0' && problem[index] <= '9') {
                read += problem[index];
                index++;
                if(index >= problem.size())break;
            }
            break;
        case '(':
            int open = 1;
            int close = 0;
            index++;
            for (int i = index; i < problem.size(); i++) {
                if (problem[i] == '(') open++;
                if (problem[i] == ')') close++;
                if (open == close) break;
                read += problem[i];
                index++;
            }
            index++;
            break;
    }
    cout << read << endl;
    return read;
}
static double CalculateV2(string problem, string function = "", string* result = 0) {
    vector<string> alphabet;
    unsigned index = 0;
    alphabet.push_back(Read(problem, index));
}*/

static double TryStod(const string& str, string* result = 0) {

    double d;
    try {
        d = std::strtod(str.c_str(),0);
    }
    catch (const std::invalid_argument&) {
        std::cerr << "Argument is invalid\n";
        *result = "Wrong Format";
        throw;
    }
    catch (const std::out_of_range&) {
        std::cerr << "Argument is out of range for a double\n";
        *result = "Wrong Format";
        throw;
    }
    return d;
}

static double Calculate(string problem, string function = "", string* result = 0)
{
    vector<string> oparationList;
    vector<double> numList;
    string oparation = problem;
    string alphabet = "";
    int lastAdd = 0;
    for (int i = 0; i < oparation.size(); i++)
    {   
        if (*result == "Wrong Format") return -1;
        cout << i << " " << alphabet << endl;
        cout << oparation[i] << endl;
        if (oparation[i] != ' ')
        {
            if (oparation[i] == '(')
            {
                if (i > 2) if (oparation[i - 1] == ')')
                {
                    oparationList.push_back("*");
                    lastAdd = 1;
                }
                /*
                if (isOparation(alphabet)) {
                    oparationList.push_back(alphabet);
                    alphabet = "";
                }*/
                string func = "";
                if (alphabet.size() > 0)
                {
                    if (isOparation(alphabet) && alphabet != "-") {
                        oparationList.push_back(alphabet);
                        lastAdd = 1;
                    }
                    else if (alphabet == "-") {
                        if (lastAdd == 2) {
                            oparationList.push_back("+");
                            func = "-";
                            alphabet = "";
                            lastAdd = 1;
                        }
                        else {
                            func = "-";
                            alphabet = "";
                            lastAdd = 1;
                        }
                    }
                    else {
                        func = alphabet;
                        alphabet = "";
                    }
                }
                i++;
                string subProblem = "";
                int subParenthesis = 0;
                while (oparation[i] != ')' || subParenthesis > 0)
                {
                    if (oparation[i] == '(')
                        subParenthesis++;
                    if (oparation[i] == ')')
                        subParenthesis--;
                    subProblem += oparation[i];
                    i++;
                }
                numList.push_back(Calculate(subProblem, func, result));
                lastAdd = 2;
                if(result) if (*result == "Wrong Format") return -1;
                continue;
            }
            if (alphabet != "")
            {
                if (alphabet[0] >= '0' && alphabet[0] <= '9' || (alphabet[0] == '-' && oparation[i] != '-')) {
                    if (isOparation(string("") + oparation[i])) {
                         numList.push_back(TryStod(alphabet, result));
                         lastAdd = 2;
                         alphabet = "";
                    }
                }
                if (alphabet == "-") {
                    
                }else if (isOparation(alphabet)) {
                     oparationList.push_back(alphabet);
                        lastAdd = 1;
                        alphabet = "";
                    
                }
            }
            alphabet += oparation[i];
            if(alphabet == "--") alphabet = "";
        }

        if (oparation[i] == ' ' || i == oparation.size() - 1)
        {
            if (alphabet.size() > 0)
            {
                if (alphabet[0] == '-') {
                    if (alphabet.size() == 1) {
                        oparationList.push_back("+");
                        lastAdd = 1;
                    }
                    else {
                        int i = 1;
                        while (alphabet[i] == '-') i++;
                        numList.push_back(pow(-1, i) * TryStod(alphabet.substr(i), result));
                        lastAdd = 2;
                        alphabet = "";
                    }
                }
                else if (alphabet[0] >= '0' && alphabet[0] <= '9') 
                {
                    numList.push_back(TryStod(alphabet, result));
                    lastAdd = 2;
                    alphabet = "";
                }
                else 
                {
                    oparationList.push_back(alphabet);
                    lastAdd = 1;
                    alphabet = "";
                }
                
            }
        }
    }

    for (int i = 0; i < numList.size(); i++) cout << numList[i] << endl;

    if (numList.size() < 2 && oparationList.size() > 0) {
        *result = "Wrong Format";
        return -1;
    }

    if (numList.size() != oparationList.size() + 1) {
        *result = "Wrong Format";
        return -1;
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        cout << oparationList[i] << endl;
        if (oparationList[i] == "^")
        {
            double op = pow(numList[i], numList[i + 1]);
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
    }
    for (int i = 0; i < oparationList.size(); i++)
    {
        if (oparationList[i] == "/")
        {
            double op = numList[i] / numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
            i--;
        }
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        if (oparationList[i] == "*")
        {
            double op = numList[i] * numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        if (oparationList[i] == "+")
        {
            double op = numList[i] + numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
        else if (oparationList[i] == "-")
        {
            double op = numList[i] - numList[i + 1];
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
        }
    }

    if(result) if (numList.size() > 1 || oparationList.size() > 0) *result = "Wrong Format";
    return Function(function, numList[0]);
}
static vector<string> GetInputVariablesList(string formula)
{
    int equalSymbol = formula.find('=');
    vector<string> variables;
    variables.push_back(formula.substr(0, equalSymbol));
    string var = "";
    for (int k = equalSymbol + 1; k < formula.size(); k++)
    {
        char i = formula[k];
        if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || i == '_' || i == ':')
        {
            var += i;
        }
        if (i == '(') {
            var = "";
        }
        if (i == ' ' || i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == ')')
        {
            if (var != "") {
                if (var != "c:e" && var != "c:pi") {
                    variables.push_back(var);
                }
            }
            var = "";
        }
        if (var != "") if (i >= '0' && i <= '9') var += i;
    }
    if (var != "") {
        if (var != "c:e" && var != "c:pi") {
            variables.push_back(var);
        }
    }
    return variables;
}
static double CalcualteEquation(string formula, unordered_map<string, double> variables, string *result = 0)
{
    formula = formula.substr(formula.find("=") + 1);
    string var = "";
    cout << formula << endl;
    for (int i = 0; i < formula.size(); i++)
    {
        if ((formula[i] >= 'a' && formula[i] <= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z') || formula[i] == '_' || formula[i] == ':')
        {
            var += formula[i];
        }
        if (formula[i] == '(') {
            var = "";
        }
        if (formula[i] == ' ' || formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^' || formula[i] == ')')
        {
            if (var != "")
            {
                cout << var << endl;
                if(var == "c:e") formula.replace(i - var.size(), var.size(), to_string(M_E));
                else if (var == "c:pi") formula.replace(i - var.size(), var.size(), to_string(M_PI));
                else formula.replace(i - var.size(), var.size(), to_string(variables[var]));
                cout << formula << endl;
            }
            var = "";
        }
        if (var != "") if (formula[i] >= '0' && formula[i] <= '9') var += formula[i];
    }
    if (var != "")
    {
        cout << var << endl;
        if (var == "c:e") formula.replace(formula.size() - var.size(), var.size(), to_string(M_E));
        else if (var == "c:pi") formula.replace(formula.size() - var.size(), var.size(), to_string(M_PI));
        else formula.replace(formula.size() - var.size(), var.size(), to_string(variables[var]));
        cout << formula << endl;
    }
    double value = Calculate(formula,"", result);
    return value;
}
/*
unordered_map<string, double> constances { 
    ("c:e", M_E), ("c:pi", M_PI)
};*/