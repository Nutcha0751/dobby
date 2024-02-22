#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "string"
#include "unordered_map"
#include "Calculate.cpp"
#include "EquationManager.h"

using namespace std;

std::vector<string> equations;
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
	virtual void OnAttach() {
		image = std::make_shared<Walnut::Image>("GR.jpg");
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImDrawList* background = ImGui::GetWindowDrawList();
		ImVec2 screen = ImGui::GetCursorScreenPos();
		ImVec2 screenSize = ImGui::GetIO().DisplaySize;
		//background->AddImage(image->GetDescriptorSet(), screen, ImVec2(screen.x + screenSize.x, screenSize.y + screen.y), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImColor(255,255,255,100));
		ImGui::Text("");
		ImGui::Columns(3, "MyLayout", false);
		ImGui::SetColumnWidth(0, (float)screenSize.x * 0.01);
		ImGui::NextColumn();
		ImGui::SetColumnWidth(1, (float)screenSize.x * 0.39);
		ImGui::Text("Equations List");
		for (int i = 0; i < equations.size(); i++) {
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
			if (ImGui::Button("X", ImVec2(50, 30))) {
				DeleteEquation(i);
				EquationManager::SaveEquations(equations);
			}
			ImGui::PopID();
		}
		if (ImGui::Button("+", ImVec2((float)screenSize.x * 0.3, 30)))
		{
			menu = 1;
		}			
		ImGui::NextColumn();
		ImGui::SetColumnWidth(2, (float)screenSize.x * 0.6);
		if (menu == 1) {
			ImGui::Text("Input Equation");
			ImGui::InputText("##", inputEquation, 255);
			if (ImGui::Button("Add")) {
				if (inputEquation[0] != '\0') {
					equations.push_back(inputEquation);
					EquationManager::SaveEquations(equations);
					inputEquation[0] = '\0';
				}
			}
		}
		else if (menu == 2) {
			ImGui::Text(("Equation: " + S).c_str());
			for (auto i = variable.begin(); i != variable.end(); i++) {
				ImGui::InputFloat(i->first.c_str(), &i->second);
			}
			ImGui::Text((resultVariable + " = " + resultValue).c_str());
			if (ImGui::Button("Calculate")) {
				if (S != "") resultValue = to_string(CalcualteEquation(S, variable));
			}
		}
		ImGui::End();

		//ImGui::ShowDemoWindow();
	}
private:
	char inputEquation[255];
	unordered_map<string, float> variable;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
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