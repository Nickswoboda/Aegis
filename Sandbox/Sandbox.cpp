#include "../src/Aegis.h"

class Sandbox : public Aegis::Layer
{
public:
	void OnUpdate() override
	{
		auto smiley = std::make_unique<Aegis::Texture>("assets/textures/smiley.png");
		auto container = std::make_unique<Aegis::Texture>("assets/textures/container.jpg");
		Aegis::Renderer2D::Clear();
		Aegis::Renderer2D::DrawQuad({ 100, 200 }, { 200, 200 }, { 1.0, 0.0, 0.0, 1.0 });
		Aegis::Renderer2D::DrawText("The Quick Brown $ | Dog Jumped Over The Lazy Fox", { 20, 0 }, { 0.0, 0.0, 0.0, 1.0 });
		Aegis::Renderer2D::DrawQuad({ 0, 50 }, { 100, 100 }, container);
	}
};

int main()
{
	Aegis::Application app(640, 480);
	app.PushLayer(new Sandbox());
	app.Run();
}