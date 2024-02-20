#pragma once
#include <nlohmann/json.hpp>
#include <string>
using namespace std;
using json = nlohmann::json;

namespace Pec {

	class EquationData
	{
		public:
			EquationData(string f) : formula(f) {};
			NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EquationData, formula);
			std::string formula;
	};


}
