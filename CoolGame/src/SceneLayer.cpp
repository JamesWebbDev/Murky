#include "SceneLayer.h"

SceneLayer::~SceneLayer()
{
}

void SceneLayer::OnAttach()
{

	m_material.colour = glm::vec3(0.7f, 0.8f, 0.7f);
	m_panel = Murky::GuiPanel("Scene");
	m_image = m_panel.AddImage();
}

void SceneLayer::OnDetach()
{
}

void SceneLayer::OnUpdate()
{
	m_frameBuffer.Bind();

	std::shared_ptr<Murky::Camera> camRef = m_camera.lock();

	if (m_shader == nullptr || m_shader->ID == UINT_MAX)//(m_shader->ID == UINT_MAX)
	{
		MK_WARN("cubeShader is not set!!!");
	}
	else
	{
		if (m_model.CubeModel.IsFileSet() == false)
		{
			MK_WARN("cubeObj is not set!!!");
		}
		else
		{
			MK_TRACE("Rendering cubeObj!!!");
			m_shader->use();

			for (short i = 0; i < 1; i++)
			{
				if (m_light.direction.x != m_lightDir_ptr[0] ||
					m_light.direction.y != m_lightDir_ptr[1] ||
					m_light.direction.z != m_lightDir_ptr[2])
				{
					m_light.direction = glm::vec3(m_lightDir_ptr[0], m_lightDir_ptr[1], m_lightDir_ptr[2]);

					m_shader->add_light_directional(m_light, i);
				}
			}

			m_shader->Update(*camRef.get());

			m_model.Draw(*m_shader);
		}
	}

	m_frameBuffer.Unbind();

	// Capture panel's size by Pre-beginning
	m_panel.PreBegin(); 

	ImVec2 viewportPanelSize = Murky::MurkyGui::GetContentRegionAvail();

	camRef->SetAspectRatio(viewportPanelSize.x / viewportPanelSize.y);
	camRef->UpdateView();
	if (m_shader != nullptr)
		m_shader->Update(*camRef.get());

	
	GLuint textureID = m_frameBuffer.GetTextureID();

	m_image->SetTexId(textureID);
	m_image->SetTexSize(viewportPanelSize);
	
	m_panel.GeneratePanel();
}

void SceneLayer::SetVertShader(const std::string& file)
{
	m_vertShaderPath = file;
	if (m_fragShaderPath != "")
	{
		m_shader->set_shader_files_abs(m_vertShaderPath, m_fragShaderPath);
	}
}

void SceneLayer::SetFragShader(const std::string& file)
{
	m_fragShaderPath = file;
	if (m_vertShaderPath != "")
	{
		m_shader->set_shader_files_abs(m_vertShaderPath, m_fragShaderPath);
	}
}

void SceneLayer::SetModel(const std::string& file)
{
	Murky::Model modelCube = Murky::Model(file.c_str());
	modelCube.SetMaterial(m_material, true);

	if (m_shader != nullptr)
	{
		delete(m_shader);
		m_shader = nullptr;
	}

	m_shader = Murky::Shader::generate_suitable_shader(modelCube, *m_isModelLit_ptr);

	m_shader->use();

	m_light.direction = glm::vec3(1, 0, 0);

	m_shader->add_light_directional(m_light, 1);
	
	m_model = CubeObject();
	m_model.CubeModel = modelCube;
	m_model.CubeTransform.Position.x -= 3.0f;
}
