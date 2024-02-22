#pragma once
#include "fstream"
#include "vector"
#include "string"
#include "cstdlib"
static class EquationManager
{
public:
	static std::vector<std::string> LoadEquations() {
		std::ifstream file("equation.txt");
		std::vector<std::string> equations;
		std::string equation;
		while (getline(file, equation)) {
			equations.push_back(equation);
		}
		return equations;
	}

	static void SaveEquations(std::vector<std::string> & equations) {
		std::ofstream file;
		file.open("equation.txt");
		for (int i = 0; i < equations.size(); i++) {
			file << equations[i] << std::endl;
		}
	}
};

