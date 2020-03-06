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
		static std::deque<double> fps (10, 60.0);
		fps.push_back(Aegis::Application::GetFrameTime());
		fps.pop_front();

		double total_time = 0;
		for (const auto time : fps) {
			total_time += time;
		}

		int average_fps = 1000 / (total_time / fps.size());
		
		Aegis::Renderer2D::Clear();
	

		glm::vec4 red = {1.0, 0.0, 0.0, 1.0};
		glm::vec4 yellow = {1.0, 1.0, 0.0, 1.0};
		for (int y = 0; y < 10; ++y) {
			if (y % 2 == 0) {
				Aegis::Renderer2D::DrawQuad({ 100.0f, y * 100.0f }, { 100.0f, 100.0f }, red);
			}
			else{
				Aegis::Renderer2D::DrawQuad({ 100.0f, y * 100.0f }, { 100.0f, 100.0f }, smiley_);
			}
		}
		
		
		//Aegis::Renderer2D::DrawText("FPS: " + std::to_string(average_fps), { 0,0 }, { 1.0, 1.0, 1.0, 1.0f });
		//Aegis::Renderer2D::DrawText("The Quick Brown", { 20, 0 }, { 1.0, 0.0, 0.0, 1.0 });
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