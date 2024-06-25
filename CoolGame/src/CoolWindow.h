#pragma once

#include <Murky.h>

class CoolWindow : public::Murky::Window
{
public:
	
	virtual void OnInit() override;
	virtual void Tick() override;
	virtual void Render() override;
	virtual void PollInputs() override;
	virtual void OnDestroy() override;

	void SetMouseMode(bool isMouseLocked) const noexcept;
	
	void PollExit();

	std::function<void(const std::string&)> SetModelAsFunction();
	void SetModel(const std::string& file);

	void SetShader(const std::string& file);

	virtual void OnEvent(Murky::Event& e) override;

	
	bool OnMouseMoved(Murky::MouseMovedEvent& e);
	bool OnMouseScrolled(Murky::MouseScrolledEvent& e);
	bool OnKeyPressed(Murky::KeyPressedEvent& e);
	bool OnWindowResize(Murky::WindowResizeEvent& e);

	void FlipFlopCamFreeze(Murky::KeyPressedEvent& e);
	void CloseWindow(Murky::KeyPressedEvent& e);
private:

	Murky::LayerStack m_layerStack;

	std::shared_ptr<Murky::FlyingCamera> m_camera;
	Murky::InputKey m_input_freeze;
	Murky::InputKey m_input_exit;

	double m_deltaTime = 0.0, m_lastFrame = 0.0;
};