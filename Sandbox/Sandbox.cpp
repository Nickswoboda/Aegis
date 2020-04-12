#include "../src/Aegis.h"

#include <deque>
#include <iostream>

#include <glm/glm.hpp>

class Sandbox : public Aegis::Layer
{
public:
	Sandbox()
	{
		smiley_ = std::make_unique<Aegis::Texture>("assets/textures/smiley.png");
		container_ = std::make_unique<Aegis::Texture>("assets/textures/container.jpg");

		fonts_.emplace_back(std::make_shared<Aegis::Font>("assets/fonts/Roboto-Regular.ttf", 16));
		fonts_.emplace_back(std::make_shared<Aegis::Font>("assets/fonts/WorkSans-Regular.ttf", 16));

		auto vec4 = sizeof(Aegis::Vec4);
		auto glm4 = sizeof(glm::vec4);

	}

	void OnUpdate() override
	{
		
		x_pos_ += x_vel_;
	}
	void OnEvent(Aegis::Event& event)
	{
		auto key_event = dynamic_cast<Aegis::KeyEvent*>(&event);
		if (key_event) {
			if (key_event->key_ == AE_KEY_A) {
				Aegis::Application::SetVsync(true);
			}
			else if (key_event->key_ == AE_KEY_S) {
				Aegis::Application::SetVsync(false);
			}
			else if (key_event->key_ == AE_KEY_F) {
				Aegis::Renderer2D::SetDefaultFont(fonts_[0]);
			}
			else if (key_event->key_ == AE_KEY_G) {
				Aegis::Renderer2D::SetDefaultFont(fonts_[1]);
			}
			else if (key_event->key_ == AE_KEY_LEFT) {
				x_vel_ = accel_;
				auto pos = Aegis::Application::GetMousePos();
				std::cout << pos.x << pos.y << "\n";
			}
			else if (key_event->key_ == AE_KEY_RIGHT) {
				x_vel_ = -accel_;
			}
		}

	}

	void OnRender(float delta_time) override
	{
		Aegis::RendererClear();

		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				Aegis::DrawQuad({ x * 26.0f, y * 26.0f }, { 25.0f, 25.0f }, { 0.3f, 0.6f, 0.9f, 1.0f });
				Aegis::DrawQuad({ x * 2.0f, y * 2.0f }, { 1.0f, 1.0f }, smiley_);
			}
		}
		Aegis::DrawText("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", { 240, 240 }, { 1.0f, 0.0f, 1.0f, 1.0f });
		Aegis::DrawText("FPS: " + std::to_string(Aegis::Application::GetFrameTime()), { 0.0f,0.0f }, { 1.0, 1.0, 1.0, 1.0f });


		Aegis::DrawQuad({ x_pos_ + (x_vel_ * delta_time), 200.0f }, { 100.0f, 100.0f }, smiley_);
		Aegis::DrawQuad({ 400.0f, 200.0f }, { 100.0f, 100.0f }, container_);
	}
	std::unique_ptr<Aegis::Texture> smiley_;
	std::unique_ptr<Aegis::Texture> container_;
	std::vector<std::shared_ptr<Aegis::Font>> fonts_;

	int x_vel_ = 0;
	int accel_ = 2;
	int x_pos_ = 0;
};

int main()
{
	Aegis::Application app(1280, 720);
	app.PushLayer(new Sandbox());
	app.Run();
}