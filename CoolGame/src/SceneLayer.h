#pragma once

#include <Murky.h>

#include "cube_object.h"

#define DIALOG_LAMBDA [this](const std::string& file)

class SceneLayer : public Murky::Layer
{
public:
	virtual ~SceneLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;

	inline const Murky::GuiImage* GetGuiImage() const { return m_image; }

	inline DialogLambda GetVertLambda() 
	{ 
		return DIALOG_LAMBDA{SetVertShader(file); };
	}
	inline DialogLambda GetFragLambda()
	{
		return DIALOG_LAMBDA{SetFragShader(file); };
	}
	inline DialogLambda GetModelLambda()
	{
		return DIALOG_LAMBDA{SetModel(file); };
	}

	inline void SetModelLitPtr(const bool*  isLitPtr) { m_isModelLit_ptr = isLitPtr; }
	inline void SetLightDirPtr(const float* lightPtr) { m_lightDir_ptr = lightPtr; }
	inline void SetCamSpeedPtr(const float* speedPtr) { m_camSpeed_ptr = speedPtr; }
	inline void SetCamera(const std::shared_ptr<Murky::Camera>& cam) { m_camera = cam; }
	inline void SetFrameBuffer(int width, int height) 
		{ m_frameBuffer = Murky::FrameBuffer(width, height); }

private:
	void SetVertShader(const std::string& file);
	void SetFragShader(const std::string& file);
	void SetModel(const std::string& file);


	Murky::GuiPanel m_panel;
	Murky::GuiImage* m_image = nullptr;

	CubeObject m_model;
	Murky::Material m_material;
	Murky::Light m_light;
	Murky::Shader* m_shader = nullptr;

	Murky::FrameBuffer m_frameBuffer;
	std::weak_ptr<Murky::Camera> m_camera;
	const bool* m_isModelLit_ptr = nullptr;
	const float* m_lightDir_ptr = nullptr;
	const float* m_camSpeed_ptr = nullptr;
	std::string m_vertShaderPath, m_fragShaderPath;

};