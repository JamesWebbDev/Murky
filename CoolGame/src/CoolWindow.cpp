#include "CoolWindow.h"

#include "cube_object.h"
#include "PropertiesLayer.h"
#include "SceneLayer.h"

bool isCamFrozen = false;

std::string vertShaderPath, fragShaderPath;
Murky::Light dirLightConfig;
Murky::Shader cubeShader, floorShader;
Murky::Material cubeMat, floorMat;
Murky::FrameBuffer frameBuffer;
CubeObject cubeObj, floorObj;


Murky::GuiPanel guiPanel;
Murky::GuiViewport guiModelViewport;
float sliderVal = 0.1f;

float lightDirVal[] = { -0.4f, -1.0f, -0.7f };

Murky::Texture2D* debugTexture;

PropertiesLayer* properties;


void CoolWindow::OnInit()
{
	using namespace Murky;
	// Move over prior code
	m_input_freeze = InputKey(*m_wnd, GLFW_KEY_F);
	m_input_exit = InputKey(*m_wnd, GLFW_KEY_ESCAPE);


	m_camera = std::make_unique<FlyingCamera>();
	//m_camera->register_window_callbacks(m_wnd);
	//m_camera->register_input_callbacks(m_wnd);
	m_camera->SetNearFar(0.3f, 1000.f);
	m_camera->SetAspectRatio((float)GetWidth() / (float)GetHeight());
	m_camera->Position = glm::vec3(0.0f, 3.0f, 15.0f);
	
	Murky::MurkyGui::InitGui(m_wnd);

	auto tempScenePtr = (SceneLayer*)m_layerStack.PushLayer((Layer*)new SceneLayer);
	auto tempPropertiesPtr = (PropertiesLayer*)m_layerStack.PushOverlay((Layer*)new PropertiesLayer);
	
	tempPropertiesPtr->OnAttach();
	tempScenePtr->OnAttach();

	tempPropertiesPtr->SetModelListener(tempScenePtr->GetModelLambda());
	tempPropertiesPtr->SetCamera(m_camera);

	tempScenePtr->SetModelLitPtr(tempPropertiesPtr->GetLitModelValue());
	tempScenePtr->SetLightDirPtr(tempPropertiesPtr->GetLightDirValue());
	tempScenePtr->SetCamera(m_camera);
	tempScenePtr->SetFrameBuffer(GetWidth(), GetHeight());
}

void CoolWindow::Tick()
{
	double currentFrame = GetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}


void CoolWindow::Render()
{
	// Pre render OpenGL

	glm::vec3 dir = m_camera->Forward;

	Murky::MurkyGL::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Murky::MurkyGL::ClearBuffers_COLOR_DEPTH();
	Murky::MurkyGL::Enable(GL_DEPTH_TEST);

	// Pre render Imgui
	Murky::MurkyGui::PreRender();
	
	// Draw OpenGL objects
	for (auto layer : m_layerStack)
	{
		layer->OnUpdate();
	}

	// Post render GUI
	Murky::MurkyGui::PostRender();

	// Post render OpenGL
	swapBuffers();
}

void CoolWindow::PollInputs()
{
	
	pollWindowEvents();
	//PollFreeze(isCamFrozen);
	//PollExit();
	m_camera->poll_move_inputs(m_wnd, m_deltaTime);
}

void CoolWindow::OnDestroy()
{
	Murky::MurkyGui::Shutdown();
}

void CoolWindow::OnEvent(Murky::Event& e) 
{
	MK_TRACE("Overriden!");
	Murky::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Murky::WindowCloseEvent>(BIND_EVENT_FN(Murky::Window::OnWindowClose));
	//MK_TRACE("evebt {0}", e.ToString());
	dispatcher.Dispatch<Murky::MouseMovedEvent>(BIND_EVENT_FN(CoolWindow::OnMouseMoved));

	dispatcher.Dispatch<Murky::MouseScrolledEvent>(BIND_EVENT_FN(CoolWindow::OnMouseScrolled));
	
	dispatcher.Dispatch<Murky::KeyPressedEvent>(BIND_EVENT_FN(CoolWindow::OnKeyPressed));

	dispatcher.Dispatch<Murky::WindowResizeEvent>(BIND_EVENT_FN(CoolWindow::OnWindowResize));
}

bool CoolWindow::OnMouseMoved(Murky::MouseMovedEvent& e)
{
	m_camera->RotateCamera(e);
	return true;
}

bool CoolWindow::OnMouseScrolled(Murky::MouseScrolledEvent& e)
{
	m_camera->ZoomCamera(e);
	return true;
}

bool CoolWindow::OnKeyPressed(Murky::KeyPressedEvent& e)
{
	FlipFlopCamFreeze(e);
	CloseWindow(e);
	//m_camera->MoveCamera(e, m_deltaTime);

	return true;
}

bool CoolWindow::OnWindowResize(Murky::WindowResizeEvent& e)
{
	m_camera->SetViewportSize(e.GetWidth(), e.GetHeight());
	return true;
}


void CoolWindow::SetMouseMode(bool isMouseLocked) const noexcept
{
	GLuint cursorState = isMouseLocked ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
	setCursorMode(cursorState);
}

void CoolWindow::FlipFlopCamFreeze(Murky::KeyPressedEvent& e)
{
	if (e.GetKeyCode() != GLFW_KEY_F)
	{
		return;
	}

	isCamFrozen = !isCamFrozen;
	SetMouseMode(isCamFrozen);

	if (m_camera != NULL)
	{
		m_camera->set_is_frozen(m_wnd, isCamFrozen);
	}
}

void CoolWindow::CloseWindow(Murky::KeyPressedEvent& e)
{
	if (e.GetKeyCode() != GLFW_KEY_ESCAPE)
	{
		return;
	}

	setShouldWindowClose(true);
}

void CoolWindow::PollExit()
{
	m_input_exit.PollKeyInput();

	if (m_input_exit.GetKeyPressed())
		setShouldWindowClose(true);
}

std::function<void(const std::string&)> CoolWindow::SetModelAsFunction()
{
	MK_TRACE("Before Return SetModelAsFunction");
	return [this](const std::string& file) { SetModel(file); };
}

void CoolWindow::SetModel(const std::string& file)
{
	//MK_INFO("Setting Model at {0}!", file.c_str());
	Murky::Model modelCube = Murky::Model(file.c_str());//("my_models/a_cube/a_cube.gltf");
	
	cubeMat.colour = glm::vec3(0.7f, 0.8f, 0.7f);
	floorMat.colour = glm::vec3(1.0f, 1.0f, 1.0f);

	modelCube.SetMaterial(cubeMat, true);

	//Model modelFloor = Model("models/sword/scene.gltf");
	//modelFloor.SetMaterial(floorMat, true);

	cubeObj = CubeObject();
	cubeObj.CubeModel = modelCube;
	cubeObj.CubeTransform.Position.x -= 3.0f;
}

void CoolWindow::SetShader(const std::string& filePath)
{
	cubeShader = Murky::Shader("#version 460 core", "#version 460 core");

	cubeShader.add_preprocessor_frag("#define NR_DIR_LIGHTS " + std::to_string(1));
	//floorShader.add_preprocessor_frag("#define NR_DIR_LIGHTS " + std::to_string(1));

	cubeShader.set_matching_shader_files(filePath);

	cubeShader.use();

	for (short i = 0; i < 1; i++)
	{
		dirLightConfig.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

		cubeShader.add_light_directional(dirLightConfig, i);
		//objShader.setVec3("dirLights[0].colour", dirLightConfig.colour);
	}


}