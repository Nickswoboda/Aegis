#include "../src/Aegis.h"

#include <deque>
#include <iostream>

#include <glm/glm.hpp>

class MenuScene : public Aegis::Scene
{
public:
	MenuScene()
		: camera_(0, 1280, 720, 0)
	{}
	void Update() override
	{

	}
	void Render(float delta_time) override
	{
		Aegis::Renderer2D::BeginScene(camera_.view_projection_matrix_);
		Aegis::RendererClear();
		Aegis::DrawQuad({ 400, 200 }, { 200, 200 }, { 1.0, 1.0, 1.0, 1.0f });
		Aegis::Renderer2D::EndScene();
	}

	void OnEvent(Aegis::Event& event) override
	{
		auto key_event = dynamic_cast<Aegis::KeyEvent*>(&event);
		if (key_event) {
			if (key_event->key_ == AE_KEY_ENTER  && key_event->action_ == AE_BUTTON_PRESS) {
				manager_->PopScene();
			}
		}
	}

	Aegis::Camera camera_;
};
class Sandbox : public Aegis::Scene
{
public:
	Sandbox()
		:camera_(0, 1280, 720, 0)
	{
		smiley_ = Aegis::TextureManager::Instance().Load("assets/textures/smiley.png");
		container_ = Aegis::TextureManager::Instance().Load("assets/textures/container.jpg");

		fonts_.emplace_back(std::make_shared<Aegis::Font>("assets/fonts/Roboto-Regular.ttf", 16));
		fonts_.emplace_back(std::make_shared<Aegis::Font>("assets/fonts/WorkSans-Regular.ttf", 16));

		sprite_ = new Aegis::Sprite(smiley_);
	}

	void Update() override
	{
		Aegis::Vec2 a(1, 0);
		Aegis::Vec2 b(0, 1);
		Aegis::Vec2 c(0, 1);

		bool same = b != b;
		bool diff = a != c;
		x_pos_ += x_vel_;
	}
	void OnEvent(Aegis::Event& event)
	{
		auto key_event = dynamic_cast<Aegis::KeyEvent*>(&event);
		if (key_event) {
			if (key_event->key_ == AE_KEY_A) {
				time_step_ *= 2.0f;
				Aegis::Application::SetTimeStep(time_step_);
			}
			else if (key_event->key_ == AE_KEY_S) {
				time_step_ /= 2.0f;
				Aegis::Application::SetTimeStep(time_step_);
			}
			else if (key_event->key_ == AE_KEY_F) {
				Aegis::Renderer2D::SetDefaultFont(fonts_[0]);
			}
			else if (key_event->key_ == AE_KEY_G) {
				Aegis::Renderer2D::SetDefaultFont(fonts_[1]);
			}
			static int x = 0;

			if (key_event->key_ == AE_KEY_LEFT) {
				--x_vel_;
				--x;
			}
			else if (key_event->key_ == AE_KEY_RIGHT) {
				++x;
				++x_vel_;
			}
			if (key_event->key_ == AE_KEY_ENTER && key_event->action_ == AE_BUTTON_PRESS) {
				manager_->ReplaceScene(std::unique_ptr<Aegis::Scene>(new MenuScene));
			}

			camera_.SetPosition({ x, 0, 0 });
		}

	}

	void Render(float delta_time) override
	{
		Aegis::Renderer2D::BeginScene(camera_.view_projection_matrix_);
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
		Aegis::Renderer2D::EndScene();
	}
	std::shared_ptr<Aegis::Texture> smiley_;
	std::shared_ptr<Aegis::Texture> container_;
	std::vector<std::shared_ptr<Aegis::Font>> fonts_;
	
	Aegis::Sprite* sprite_;
	Aegis::Camera camera_;
	int x_vel_ = 0;
	int accel_ = 2;
	int x_pos_ = 0;
	float time_step_ = 1.0 / 60.0f;
};

int main()
{

	Aegis::Vec2 a(2, 0);
	Aegis::Vec2 b(3, 2);
	Aegis::Vec2 c = a / b;
	Aegis::Vec2 d = a * b;
	
	Aegis::Vec2 e = (a * b).Normalized();
	b.Normalize();

	Aegis::Application app(1280, 720);
	app.PushScene(std::unique_ptr<Aegis::Scene>(new Sandbox));
	app.PushScene(std::unique_ptr<Aegis::Scene>(new MenuScene));
	app.Run();
}