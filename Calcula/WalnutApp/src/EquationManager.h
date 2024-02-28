#pragma once
#include "fstream"
#include "vector"
#include "string"
#include "cstdlib"
#include "EquationData.h"
using namespace std;

static class EquationManager {
public:
	static void LoadEquations(vector<EquationData>& equations) {
		equations.clear();
		ifstream file("equation.txt");
		string equation;
		string formula;
		string description;
		string multilinedesc;
		while (getline(file, equation)) {
			sscanf(equation.c_str(), "%[^,],%[^,]", formula.c_str(), description.c_str());
			cout << "Load " << formula.c_str() << "size: " << strlen(formula.c_str());
			multilinedesc = description.c_str();
			int newLine = multilinedesc.find('|');
			while (newLine < multilinedesc.size()) {
				multilinedesc.replace(newLine, 1, "\n");
				newLine = multilinedesc.find('|');
			}
			equations.push_back(EquationData(formula.c_str(), multilinedesc));
		}
	}

	static void SaveEquations(vector<EquationData>& equations) {
		ofstream file;
		file.open("equation.txt");
		for (int i = 0; i < equations.size(); i++) {
			cout << "Save " << equations[i].getFormula() << "size: " << equations[i].getFormula().size();
			
			string desc = equations[i].getDescription();
			int newLine = desc.find('\n');
			while (newLine < desc.size()) {
				desc.replace(newLine, 1, "|");
				newLine = desc.find('\n');
			}
			file <<  equations[i].getFormula() << "," << desc << endl;
		}
	}
};