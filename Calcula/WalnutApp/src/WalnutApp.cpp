#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "string"
#include "unordered_map"

using namespace std;

class ExampleLayer : public Walnut::Layer
{
public:
	string S;
	std::shared_ptr<Walnut::Image> image;
	string resultValue;
	string resultVariable;

	virtual void OnAttach() {
		image = std::make_shared<Walnut::Image>("GR.jpg");
	}
	virtual void OnUIRender() override
	{
		
		ImGui::Begin("Hello");
		ImDrawList* background = ImGui::GetWindowDrawList();
		ImVec2 screen = ImGui::GetCursorScreenPos();
		ImVec2 screenSize = ImGui::GetIO().DisplaySize;
		background->AddImage(image->GetDescriptorSet(), screen, ImVec2(screen.x + screenSize.x, screenSize.y + screen.y));
		ImGui::Text(("Equation: " + S).c_str());
		for (auto i = variable.begin(); i != variable.end(); i++) {
			ImGui::InputFloat(i->first.c_str(), &i->second);
		}
		for (int i = 0; i < 4; i++) 
			if (ImGui::Button(eq[i].c_str()))
			{
				S = eq[i];
				variable.clear();
				if (i == 0) {
					variable["s"] = 0;
					variable["t"] = 0;
					resultVariable = "v";
				}
			};
		ImGui::Text((resultVariable + " = " + resultValue).c_str());
		if (ImGui::Button("Calculate")) {
			resultValue = to_string(variable["s"] / variable["t"]);
		}
		ImGui::End();

		//ImGui::ShowDemoWindow();
	}
private:
	string eq[4] = {"v = s / t", "s = v * t", "t = s / v", "E = m * c * c"};
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
	});
	return app;
}