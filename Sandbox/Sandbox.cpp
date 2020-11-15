#include "../src/Aegis.h"

#include <deque>
#include <iostream>

#include <glm/glm.hpp>

class Sandbox : public Aegis::Scene
{
public:
	Sandbox()
	{
		ui_layer_ = std::make_unique<Aegis::UILayer>();
		auto dialog_ = ui_layer_->AddWidget<Aegis::Dialog>("You Lose. Try Again?", Aegis::Vec2(300, 300), Aegis::Vec2(400, 400));
		dialog_->SetAcceptedCallback([](){std::cout << "Accepted";});
		dialog_->SetRejectedCallback([](){std::cout << "Rejected";});


	}

	void Update() override
	{
	}
	void OnEvent(Aegis::Event& event) override
	{
	}

	void Render(float delta_time) override
	{
		Aegis::Renderer2D::BeginScene(camera_.view_projection_matrix_);
		
		Aegis::Renderer2D::EndScene();
	}

};

int main()
{
	Aegis::Application::CreateWindow("Sandbox", 1280, 720);
	Aegis::Application::ShowFrameTime(true);
	Aegis::Application::PushScene(std::unique_ptr<Aegis::Scene>(new Sandbox));
	Aegis::Application::Run();
}
