#define _USE_MATH_DEFINES
#include <math.h>
//#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
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
double Function(string func, double value)
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
    return sign * result;
}
double Calculate(string problem, string function = "")
{
    vector<string> oparationList;
    vector<double> numList;
    string oparation = problem;
    string alphabet = "";

    for (int i = 0; i < oparation.size(); i++)
    {
        if (oparation[i] != ' ')
        {
            if (oparation[i] == '(')
            {
                string func = "";
                if (alphabet.size() > 0)
                {
                    func = alphabet;
                    alphabet = "";
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
                numList.push_back(Calculate(subProblem, func));
                continue;
            }
            alphabet += oparation[i];
        }

        if (oparation[i] == ' ' || i == oparation.size() - 1)
        {
            if (alphabet.size() > 0)
            {
                if (alphabet[0] == '-' && (alphabet[1] >= '0' && alphabet[1] <= '9')) {
                    numList.push_back(stod(alphabet));
                }
                else if (alphabet[0] >= '0' && alphabet[0] <= '9')
                    numList.push_back(stod(alphabet));
                else
                    oparationList.push_back(alphabet);
                alphabet = "";
            }
        }
    }

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        if (oparationList[i] == "^")
        {
            double op = pow(numList[i], numList[i + 1]);
            numList[i] = op;
            numList.erase(numList.begin() + i + 1);
            oparationList.erase(oparationList.begin() + i);
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
        else if (oparationList[i] == "/")
        {
            double op = numList[i] / numList[i + 1];
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

    return Function(function, numList[0]);
}

static vector<string> GetInputVariablesList(string formula)
{
    vector<string> variables;
    string var = "";
    for (auto i : formula)
    {
        if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
        {
            var += i;
        }
        if (i == '(') {
            var = "";
        }
        if (i == ' ' || i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == ')')
        {
            if (var != "")
                variables.push_back(var);
            var = "";
        }
    }
    if (var != "")
        variables.push_back(var);
    return variables;
}

static double CalcualteEquation(string formula, unordered_map<string, double> variables)
{
    formula = formula.substr(formula.find("=") + 1);
    string var = "";
    cout << formula << endl;
    for (int i = 0; i < formula.size(); i++)
    {
        if ((formula[i] >= 'a' && formula[i] <= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z'))
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
                formula.replace(i - var.size(), var.size(), to_string(variables[var]));
                cout << formula << endl;
            }
            var = "";
        }
    }
    if (var != "")
    {
        cout << var << endl;
        formula.replace(formula.size() - var.size(), var.size(), to_string(variables[var]));
        cout << formula << endl;
    }
    double value = Calculate(formula);
    return value;
}