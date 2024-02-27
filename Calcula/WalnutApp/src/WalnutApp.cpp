#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "string"
#include "unordered_map"
#include "Calculate.cpp"
#include "EquationManager.h"
#include "LaTexCaller.cpp"

using namespace std;

std::vector<string> equations;
bool isLaTexUsable = false;

static void DeleteEquation(int index) {
	equations.erase(equations.begin() + index);
}

class ExampleLayer : public Walnut::Layer
{
public:
	string S;
	std::shared_ptr<Walnut::Image> image;
	string resultValue;
	string resultVariable;
	int menu = 0;
	float PX;
	float PY;
	float k = 0.3;
	float R = 1;
	unordered_map<unsigned, std::shared_ptr<Walnut::Image>> buttonImage;

	std::shared_ptr<Walnut::Image> GetImage(string equation) {
		unsigned id = Hashing(equation);
		string filename = to_string(id) + ".png";
		if (buttonImage[id]) {
			return buttonImage[id];
		}
		else if(!CheckFile(filename)) {
			GenarateImage(ToLaTexFormat(equation), to_string(id));
		}
		buttonImage[id] = make_shared<Walnut::Image>(filename);
		return buttonImage[id];
	}

	virtual void OnAttach() {
		image = make_shared<Walnut::Image>("PK.jpg");
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Dobby's Calculation");
		ImDrawList* background = ImGui::GetWindowDrawList();
		ImVec2 screen = ImGui::GetWindowViewport()->Pos;
		ImVec2 screenSize = ImGui::GetWindowViewport()->Size;
		background->AddRectFilledMultiColor(screen, ImVec2(screen.x + screenSize.x, screenSize.y / 2 + screen.y), ImColor(255, 255, 204, 255), ImColor(255, 255, 204, 255), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 255));
		background->AddRectFilledMultiColor(ImVec2(screen.x, screenSize.y / 2 + screen.y), ImVec2(screen.x + screenSize.x, screenSize.y + screen.y), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 255), ImColor(255, 229, 204, 255), ImColor(255, 229, 204, 255));
		//background->AddCircleFilled(ImVec2(screen.x + screenSize.x / 2 + PX, screenSize.y / 2 + screen.y + PY), R, ImColor(255, 0, 0, 255));
		background->AddImage(image->GetDescriptorSet(), screen, ImVec2(screen.x + screenSize.x, screenSize.y + screen.y));
		string backgroundImageFile = "PK.jpg";
		
		ImGui::Text("");
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); //text black color
		//ImGui::SliderFloat("P.X", &PX,-900,900);
		//ImGui::SliderFloat("P.Y", &PY, -300, 300);
		
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); //change black button
		//ImGui::SliderFloat("R", &R,1,5);
		ImGui::PopStyleColor();

		ImGui::Columns(3, "MyLayout", false);
		ImGui::SetColumnWidth(0, (float)screenSize.x * 0.01);
		ImGui::NextColumn();
		ImGui::SetColumnWidth(1, (float)screenSize.x * 0.39);
		ImGui::Text("Equations List");
		ImGui::PopStyleColor(); //finish change taxt color

		for (int i = 0; i < equations.size(); i++) {
			if (isLaTexUsable) {
				auto img = GetImage(equations[i]);
				//double width = img->GetWidth() * 50.0 / img->GetHeight();
				double width = img->GetWidth() / (R + 2) ;
				double height = img->GetHeight() / (R + 2);
				float offsetX = ((float)screenSize.x * 0.3 - width) / 2.0;
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { offsetX, 10 });
				if (ImGui::ImageButton(img->GetDescriptorSet(), ImVec2(width, height), {0,0}, {1,1})) {
					menu = 2;
					S = equations[i];
					variable.clear();
					vector<string> var = GetInputVariablesList(S);
					resultVariable = var[0];
					for (int i = 1; i < var.size(); i++) {
						variable[var[i]] = 0;
					}
					resultValue = "";
				}
				ImGui::PopStyleVar();
				ImGui::SameLine();
				ImGui::PushID(i);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				if (ImGui::Button("X", ImVec2(50, height + 20))) {
					DeleteEquation(i);
					EquationManager::SaveEquations(equations);
				}
				ImGui::PopID();
				ImGui::PopStyleColor();
			}
			else {
				if (ImGui::Button(equations[i].c_str(), ImVec2((float)screenSize.x * 0.3, 30)))
				{
					menu = 2;
					S = equations[i];
					variable.clear();

					vector<string> var = GetInputVariablesList(S);
					resultVariable = var[0];
					for (int i = 1; i < var.size(); i++) {
						variable[var[i]] = 0;
					}
					resultValue = "";
				}

				ImGui::SameLine();
				ImGui::PushID(i);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				if (ImGui::Button("X", ImVec2(50, 30))) {
					DeleteEquation(i);
					EquationManager::SaveEquations(equations);
				}
				ImGui::PopID();
				ImGui::PopStyleColor();
			}

		}

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.647f, 0.0f, 0.5f)); //change orange button
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		
		if (ImGui::Button("s = v * t", ImVec2((float)screenSize.x * 0.3, 30))) //default function 1
		{
			menu = 2;
			S = "s = v * t";
			variable.clear();

			vector<string> var = GetInputVariablesList(S);
			resultVariable = var[0];
			for (int i = 1; i < var.size(); i++) {
				variable[var[i]] = 0;
			}
			resultValue = "";
		}
		if (ImGui::Button("s = u + a * t", ImVec2((float)screenSize.x * 0.3, 30))) //default function 1
		{
			menu = 2;
			S = "s = u + a * t";
			variable.clear();

			vector<string> var = GetInputVariablesList(S);
			resultVariable = var[0];
			for (int i = 1; i < var.size(); i++) {
				variable[var[i]] = 0;
			}
			resultValue = "";
		}
		if (ImGui::Button("f = m * x + b", ImVec2((float)screenSize.x * 0.3, 30))) //default function 1
		{
			menu = 2;
			S = "f = m * x + b";
			variable.clear();

			vector<string> var = GetInputVariablesList(S);
			resultVariable = var[0];
			for (int i = 1; i < var.size(); i++) {
				variable[var[i]] = 0;
			}
			resultValue = "";
		}
		

		if (ImGui::Button("+", ImVec2((float)screenSize.x * 0.3, 30)))
		{
			menu = 1;
		}			

		ImGui::NextColumn();
		ImGui::SetColumnWidth(2, (float)screenSize.x * 0.6);
		if (menu == 1) {
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, IM_COL32(0, 255, 0, 255));
			ImGui::Text("Input Equation");
			ImGui::InputTextWithHint("##InputEquation", "Enter Equation", inputEquation, 255);
			if (ImGui::Button("Add")) {
				if (inputEquation[0] != '\0') {
					equations.push_back(inputEquation);
					EquationManager::SaveEquations(equations);
					inputEquation[0] = '\0';
				}
			}
			ImGui::PopStyleColor();
			ImGui::Text("Description of Equation");
			/*ImGui::InputText("##InputDesc", inputDescription, 255);*/
			//if (ImGui::Button("Add Description")) {
			//	if (inputDescription[0] != '\0') {
			//		//equations.push_back(inputDescription);
			//		//DescriptionManager::SaveDescription(description);
			//		//inputDescription[0] = '\0';
			//	}
			//}
		
		}



		else if (menu == 2) {
			ImGui::Text(("Equation: " + S).c_str());
			for (auto i = variable.begin(); i != variable.end(); i++) {
				ImGui::InputDouble(i->first.c_str(), &i->second);
			}
			ImGui::Text((resultVariable + " = " + resultValue).c_str());
			if (ImGui::Button("Calculate")) {
				if (S != "") resultValue = to_string(CalcualteEquation(S, variable));
			}
		}


		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::End();
	}
private:
	char inputEquation[255];
	unordered_map<string, double> variable;
	/*char inputDescription[255];
	unordered_map<string, double> description;*/
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";
	Walnut::Application* app = new Walnut::Application(spec);
	isLaTexUsable = CheckFile("LaTex\\LaTex.exe");
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}

			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Equation")) {
			if (ImGui::MenuItem("Load"))
			{
				equations = EquationManager::LoadEquations();
			}
			if (ImGui::MenuItem("Save"))
			{
				EquationManager::SaveEquations(equations);
			}
			ImGui::EndMenu();
		}
	});
	return app;
}





