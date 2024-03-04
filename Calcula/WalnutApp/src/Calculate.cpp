#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <sstream>

using namespace std;

std::string to_string_exact(double x) {
    std::stringstream str;
    str << fixed << setprecision(15) << x;
    return str.str();
}

std::string to_scientific_form(double x) {
    if (x == 0) return "0";
    int power = 0;
    while (abs(x) < 1) {
        x  *= 10;
        power--;
    }

    while (abs(x) >= 10) {
        x /= 10;
        power++;
    }
    std::stringstream str;
    if (power != 0) str << fixed << setprecision(15) << x << "e" << power;
    else str << fixed << setprecision(15) << x;
    return str.str();
}

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

static double Factorial(double value) {
    double fvalue = tgamma(value);
    return fvalue;
}

vector<string> allOparations = { "+", "-", "*", "/", "^" };

static bool isOparation(string alphabet) {
    //cout << "Alphabet: " << alphabet << endl;
    for (auto i : allOparations) {
        //cout << "Check: " << i << endl;
        if (alphabet == i) return 1;
    }
    return 0;
}

static bool isOparation(char alphabet) {
    //cout << "Alphabet: " << alphabet << endl;
    for (auto i : allOparations) {
        //cout << "Check: " << i << endl;
        if (alphabet == i[0]) return 1;
    }
    return 0;
}

vector<string> allFunction = {"sin", "sine", "cos", "cosine", "tan", "tangent", "cosec", "cosecent"
, "csc", "sec", "secant", "cot", "cotan", "cotangent", "ln", "log", "arcsin", "asin", "arccos", "acos", "arctan", "atan", "arccos", "acos"
, "arctan", "atan", "arcsec", "asec", "arccsc", "acsc", "arccot", "acot"};

static bool isFunctionName(string text) {
    for (auto i : allFunction) {
        if (text == i) return 1;
    }
    return 0;
}

enum readType {
    None, Oparation, Number
};

static double TryStod(const string& str, string* result = 0) {

    double d;
    try {
        cout << std::fixed << std::setprecision(14);
        d = std::strtod(str.c_str(),NULL);
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

bool debug = false;

void printDebug(string text) {
    if(debug) cout << text << endl;
}

static double Calculate(string problem, string function = "", string* result = 0, bool debugProb = true)
{
    vector<string> oparationList;
    vector<double> numList;
    string oparation = problem;
    string alphabet = "";
    int lastAdd = 0;
    debug = debugProb;
    printDebug("Calculate: " + problem);
    printDebug("Function: " + function);
    for (int i = 0; i < oparation.size(); i++)
    {   
        if(result != 0) if (*result == "Wrong Format") return -1;

        if (oparation[i] != ' ')
        {
            if (oparation[i] == '(')
            {
                if (i > 2) if (oparation[i - 1] == ')' || oparation[i - 1] == '!')
                {
                    oparationList.push_back("*");
                    printDebug("166 push *");
                    lastAdd = 1;
                }

                string func = "";
                string testNum = "";
                double number = TryStod(alphabet, &testNum);
                if (alphabet.size() > 0)
                {
                    if (isFunctionName(alphabet)) {
                        func = alphabet;
                        alphabet = "";
                    }
                    else if (isOparation(alphabet) && alphabet != "-") {
                        oparationList.push_back(alphabet);
                        printDebug("177 push " + alphabet);
                        alphabet = "";
                        lastAdd = 1;
                    }
                    else if (alphabet == "-") {
                        if (lastAdd == 2) {
                            oparationList.push_back("+");
                            printDebug("183 push +");
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
                    else if (testNum == "") {
                        if (lastAdd == 2 && number < 0) {
                            oparationList.push_back("+");
                            printDebug("197 push +");
                            numList.push_back(number);
                            printDebug("199 push " + to_string(number));
                            oparationList.push_back("*");
                            printDebug("201 push *");
                            alphabet = "";
                            lastAdd = 1;
                        }
                        else {
                            numList.push_back(number);
                            printDebug("207 push " + to_string(number));
                            oparationList.push_back("*");
                            printDebug("209 push *");
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
                double v = Calculate(subProblem, func, result, true);
                numList.push_back(v);
                if(debugProb) debug = true;
                printDebug("235 push " + to_string(v));
                lastAdd = 2;
                if(result) if (*result == "Wrong Format") return -1;
                continue;
            }

            if (oparation[i] == '!') {
                if (alphabet != "") {
                    double v = Factorial((TryStod(alphabet, result)) + 1);
                    if (result) if (*result == "Wrong Format") return -1;
                    numList.push_back(v);
                    printDebug("245 push " + to_string(v));
                    lastAdd = 2;
                }
                else if (lastAdd == 2) {
                    double o = numList[numList.size() - 1];
                    double v = Factorial(1 + o);;
                    numList[numList.size() - 1] = v;
                    printDebug("252 change " + to_string(o) + " to " + to_string(v));
                    lastAdd = 2;
                }               
                alphabet = "";
            }
            if (alphabet != "")
            {
                if (alphabet[0] >= '0' && alphabet[0] <= '9' || (alphabet[0] == '-' && oparation[i] != '-')) {
                    if (isOparation(string("") + oparation[i])) {
                        double v = TryStod(alphabet, result);
                        numList.push_back(v);
                        printDebug("263 push " + to_string(v));
                        lastAdd = 2;
                        alphabet = "";
                    }
                    else if(oparation[i] >= 'a' && oparation[i] <= 'z') {
                        double v = TryStod(alphabet, result);
                        numList.push_back(v);
                        printDebug("505 push " + to_string(v));
                        oparationList.push_back("*");
                        printDebug("505 push *");
                        lastAdd = 1;
                        alphabet = "";
                    }
                }
                if (alphabet == "-") {
                    
                }else if (isOparation(alphabet)) {
                     oparationList.push_back(alphabet);
                     printDebug("275 push " + alphabet);
                        lastAdd = 1;
                        alphabet = "";
                    
                }
            }
            alphabet += oparation[i];
            printDebug("296 " + alphabet);
            if(alphabet == "!")alphabet = "";
            if(alphabet == "--") alphabet = "";
        }

        if (oparation[i] == ' ' || i == oparation.size() - 1)
        {
            if (alphabet.size() > 0)
            {
                if (alphabet[0] == '-') {
                    if (alphabet.size() == 1) {
                        oparationList.push_back("+");
                        printDebug("100 push +");
                        lastAdd = 1;
                    }
                    else {
                        int i = 1;
                        while (alphabet[i] == '-') i++;
                        double v = pow(-1, i) * TryStod(alphabet.substr(i), result);
                        if (lastAdd == 2) {
                            oparationList.push_back("+");
                            printDebug("101 push +");
                        }
                        numList.push_back(v);
                        printDebug("101 push " + to_string(v));
                        lastAdd = 2;
                        alphabet = "";
                    }
                }
                else if (alphabet[0] >= '0' && alphabet[0] <= '9') 
                {
                    double v = TryStod(alphabet, result);
                    numList.push_back(v);
                    printDebug("102 push " + to_string(v));
                    lastAdd = 2;
                    alphabet = "";
                }
                else 
                {
                    oparationList.push_back(alphabet);
                    printDebug("103 push " + alphabet);
                    lastAdd = 1;
                    alphabet = "";
                }
                
            }
        }
    }



    //for (int i = 0; i < numList.size(); i++) cout << numList[i] << endl;

    if (numList.size() < 2 && oparationList.size() > 0) {
        if (result) *result = "Wrong Format";
        return -1;
    }

    if (numList.size() != oparationList.size() + 1) {
        if (result)*result = "Wrong Format";
        return -1;
    }

    printDebug("Calculating..");

    for (int i = oparationList.size() - 1; i >= 0; i--)
    {
        //cout << oparationList[i] << endl;
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
        if ((var == "e" || var == "E") && i == '-') { 
            var += i; 
            continue;
        }
        if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || i == '_' || i == ':')
        {
            var += i;
        }
        if (i == ' ' || i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == ')' || i == '(' || i == '!')
        {
            if (var != "") {
                if (var != "" && var != "c:e" && var != "c:pi" && !isFunctionName(var)) {
                    cout << "var: " << var << endl;
                    //---------------------
                    if(var.size() > 1)
                    if (var[0] == 'e' || var[0] == 'E') {
                        bool isNum = true;
                        for (int i = 1; i < var.size(); i++) {
                            if (i == 1 && var[1] == '-') continue;
                            if (!(var[i] >= '0' && var[i] <= '9')) { 
                                isNum = false; 
                                break;
                            }
                        }
                        if(isNum) var = "e:" + var;
                    }
                        //------------------------
                    variables.push_back(var);
                }
            }
            var = "";
        }
        if (var != "") if (i >= '0' && i <= '9') var += i;
        
    }
    if (var != "") {

            if (var != "" && var != "c:e" && var != "c:pi" && !isFunctionName(var)) {
                //---------------------
                if (var[0] == 'e' || var[0] == 'E') {
                    bool isNum = true;
                    for (int i = 1; i < var.size(); i++) {
                        if (i == 1 && var[1] == '-') continue;
                        if (!(var[i] >= '0' && var[i] <= '9')) {
                            isNum = false;
                            break;
                        }
                    }
                    if (isNum) var = "e:" + var;
                }
                //------------------------
                variables.push_back(var);
            }
        
    }
    return variables;
}

static double CalcualteEquation(string formula, unordered_map<string, double> variables = {}, string* result = 0)
{
    formula = formula.substr(formula.find("=") + 1);
    string var = "";
    cout << formula << endl;
    for (int i = 0; i < formula.size(); i++)
    {
        if ((var == "e" || var == "E") && formula[i] == '-') {
            var += formula[i];
            continue;
        }
        if ((formula[i] >= 'a' && formula[i] <= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z') || formula[i] == '_' || formula[i] == ':')
        {
            var += formula[i];
        }
        if (formula[i] == ' ' || formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^' || formula[i] == ')' || formula[i] == '(' || formula[i] == '!')
        {
            if (var != "")
            {
                //cout << var << endl;
                if(var == "c:e") formula.replace(i - var.size(), var.size(), "(" + to_string_exact(M_E) + ")");
                else if (var == "c:pi") formula.replace(i - var.size(), var.size(), "(" + to_string_exact(M_PI) + ")");
                else if(!isFunctionName(var)){ 
                    //---------------------
                    string key = var;
                    if (var.size() > 1)
                    if (var[0] == 'e' || var[0] == 'E') {
                        bool isNum = true;
                        for (int i = 1; i < var.size(); i++) {
                            if (i == 1 && var[1] == '-') continue;
                            if (!(var[i] >= '0' && var[i] <= '9')) {
                                isNum = false;
                                break;
                            }
                        }
                        if (isNum) key = "e:" + var;
                    }
                    //------------------------
                    string thingToReplace = to_string_exact(variables[key]);
                    //string thingToReplace = //to_string(variables[var]);
                    formula.replace(i - var.size(), var.size(), "(" + thingToReplace + ")");
                }
                //cout << formula << endl;
            }
            var = "";
        }
        if (var != "") if (formula[i] >= '0' && formula[i] <= '9') var += formula[i];
    }
    if (var != "")
    {
        //cout << var << endl;
        if (var == "c:e") formula.replace(formula.size() - var.size(), var.size(), "(" + to_string_exact(M_E) + ")");
        else if (var == "c:pi") formula.replace(formula.size() - var.size(), var.size(), "(" + to_string_exact(M_PI) + ")");
        else { 
            //---------------------
            string key = var;
            if (var[0] == 'e' || var[0] == 'E') {
                bool isNum = true;
                for (int i = 1; i < var.size(); i++) {
                    if (i == 1 && var[1] == '-') continue;
                    if (!(var[i] >= '0' && var[i] <= '9')) {
                        isNum = false;
                        break;
                    }
                }
                if (isNum) key = "e:" + var;
            }
            //------------------------
            string thingToReplace = to_string_exact(variables[key]);
            //if (formula[formula.size() - 2] >= '0' && formula[formula.size() - 2] <= '9')
                formula.replace(formula.size() - var.size(), var.size(), "(" + thingToReplace + ")");
            //else formula.replace(formula.size() - var.size(), var.size(), thingToReplace);
        }
        //cout << formula << endl;
    }
    double value = Calculate(formula,"", result);
    return value;
}

static unordered_map<string, double> ConvertInputVariable(unordered_map<string, string> variableString, int inception = 0, string* report = 0) {
    unordered_map<string, double> result;
    cout << "Convert\n";
    for (const auto& variable : variableString)
    {
        cout << variable.first << " " << variable.second << endl;
 
        if (!inception) {
            unordered_map<string, string> varr;
            auto varList = GetInputVariablesList(variable.second);
            if (varList.size() > 0) {
                for(int i = 1; i < varList.size(); i++){
                    auto vv = varList[i];
                    cout << "vvvv: " << vv << endl;
                    if (vv.substr(0, 2) != "c:" && vv.substr(0, 2) != "e:")
                    {
                        *report = "Has Variable";
                        return {};
                    }
                    varr[vv] = vv;
                }           
            }
            auto varNum = ConvertInputVariable(varr, 1);
            
            double valuee = CalcualteEquation(variable.second, varNum);
            result[variable.first] = valuee;
        }
        else {
            string x = variable.second;
            if (variable.first.size() > 2) if (variable.first[0] == 'e' && variable.first[1] == ':') x = variable.first.substr(2);
            if (x[0] == 'e') x = "1" + x;
            cout << "x: " << x << endl;
            if (variable.second == "c:e") result[variable.first] = M_E;
            else if (variable.second == "c:pi")  result[variable.first] = M_PI;
            else result[variable.first] = TryStod(x);
        }
    }
    return result;
}