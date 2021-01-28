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
		dialog_->SetAcceptedCallback([&]() {cymbal_sound_->Stop(); });
		dialog_->SetRejectedCallback([&](){ cymbal_sound_->Play(); });

		auto dropdown = ui_layer_->AddWidget<Aegis::Dropdown>("Dropdown 1:", Aegis::AABB(20, 20, 300, 20));
		dropdown->AddItem("1", []() {std::cout << 1 << "\n"; });
		dropdown->AddItem("2", []() {std::cout << 2 << "\n"; });
		dropdown->AddItem("3", []() {std::cout << 3 << "\n"; });

		auto dropdown2 = ui_layer_->AddWidget<Aegis::Dropdown>("Dropdown 2:", Aegis::AABB(20, 50, 300, 20));
		dropdown2->AddItem("1", []() {std::cout << 1 << "\n"; });
		dropdown2->AddItem("2", []() {std::cout << 2 << "\n"; });

		cymbal_sound_ = new Aegis::SoundEffect("assets/audio/bgm.ogg");
		cymbal_sound_->Play();

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

	Aegis::SoundEffect* cymbal_sound_;

};

int main()
{
	Aegis::Application::CreateWindow("Sandbox", 1280, 720);
	Aegis::Application::ShowFrameTime(true);
	Aegis::Application::PushScene(std::unique_ptr<Aegis::Scene>(new Sandbox));
	Aegis::Application::Run();
}
