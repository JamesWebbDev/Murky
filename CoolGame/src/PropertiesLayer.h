#pragma once

#include <Murky.h>

class PropertiesLayer : public Murky::Layer
{
public:
	virtual ~PropertiesLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;

	void SetModelListener(DialogLambda listener);
	inline void SetCamera(const std::shared_ptr<Murky::Camera>& cam) { m_camera_ptr = cam; }

	inline const bool*  GetLitModelValue() const { return &m_litModel; }
	inline const float* GetLightDirValue()   const { return m_lightDirVal; }
	inline const float* GetCamSpeedValue()   const { return &m_cameraSpeed; }
	inline const Murky::GuiFileDialog* GetModelDialog() const { return m_modelDialog; }

private:

	Murky::GuiFileDialog* m_modelDialog;

	Murky::GuiPanel m_panel;
	bool  m_litModel = false;
	float m_lightDirVal[3] = { -0.2f, -1.0f, -0.3f };
	float m_cameraSpeed = 10.0f;

	std::weak_ptr<Murky::Camera> m_camera_ptr;
};