#include "../src/Aegis.h"

#include <deque>
#include <iostream>

class Sandbox : public Aegis::Layer
{
public:
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
		
		//auto smiley = std::make_unique<Aegis::Texture>("assets/textures/smiley.png");
		//auto container = std::make_unique<Aegis::Texture>("assets/textures/container.jpg");

		for (int y = 0; y < 480; y+=25) {
			for (int x = 0; x < 640; x += 25)
				Aegis::Renderer2D::DrawQuad({ x, y }, { 20, 20 }, { 1.0, 0.0, 0.0, 1.0 });
		}

		Aegis::Renderer2D::EndBatch();
		Aegis::Renderer2D::DrawText("FPS: " + std::to_string(average_fps), { 0,0 }, { 1.0, 1.0, 1.0, 1.0f });
		//Aegis::Renderer2D::DrawText("The Quick Brown", { 20, 0 }, { 1.0, 0.0, 0.0, 1.0 });
		//Aegis::Renderer2D::DrawQuad({ 0, 50 }, { 100, 100 }, container);
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

};

int main()
{
	Aegis::Application app(640, 480);
	app.PushLayer(new Sandbox());
	app.Run();
}