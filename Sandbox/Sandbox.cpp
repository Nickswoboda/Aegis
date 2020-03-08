#include "../src/Aegis.h"

#include <deque>
#include <iostream>

class Sandbox : public Aegis::Layer
{
public:
	Sandbox()
	{
		smiley_ = std::make_unique<Aegis::Texture>("assets/textures/smiley.png");
		container_ = std::make_unique<Aegis::Texture>("assets/textures/container.jpg");
	}
	void OnUpdate() override
	{
		static std::deque<double> fps (20, 60.0);
		fps.push_back(Aegis::Application::GetFrameTime());
		fps.pop_front();

		double total_time = 0;
		for (const auto time : fps) {
			total_time += time;
		}

		double average_frame_time = total_time / fps.size();
		
		Aegis::Renderer2D::Clear();
		
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				Aegis::Renderer2D::DrawQuad({ x * 26, y*26 }, { 25, 25 }, { 0.3f, 0.6f, 0.9f, 1.0f });
				Aegis::Renderer2D::DrawQuad({ x*2, y*2 }, { 1, 1 }, smiley_);
			}
		}
		Aegis::Renderer2D::DrawText("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", { 240, 240 }, { 1.0f, 0.0f, 1.0f, 1.0f });
		Aegis::Renderer2D::DrawText("FPS: " + std::to_string(average_frame_time), { 0,0 }, { 1.0, 1.0, 1.0, 1.0f });

		Aegis::Renderer2D::DrawQuad({ 0, 200 }, { 100, 100 }, smiley_);
		Aegis::Renderer2D::DrawQuad({ 400, 200 }, { 100, 100 }, container_);

	}
	void OnEvent(Aegis::Event& event)
	{
		auto key_event = dynamic_cast<Aegis::KeyEvent*>(&event);
		if (key_event) {
			if (key_event->key_ == GLFW_KEY_A) {
				Aegis::Application::SetVsync(true);
			}
			else if (key_event->key_ == GLFW_KEY_S) {
				Aegis::Application::SetVsync(false);
			}
		}

	}

	std::unique_ptr<Aegis::Texture> smiley_;
	std::unique_ptr<Aegis::Texture> container_;

};

int main()
{
	Aegis::Application app(640, 480);
	app.PushLayer(new Sandbox());
	app.Run();
}