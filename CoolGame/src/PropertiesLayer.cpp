#include "PropertiesLayer.h"

PropertiesLayer::~PropertiesLayer()
{
}

void PropertiesLayer::OnAttach()
{
	m_panel = Murky::GuiPanel("Properties Panel");
	m_panel.AddText("MURKY RENDERER TOOL");
	m_panel.AddText("Tap the 'F' key the toggle the mouse cursor.");

	Murky::GuiButton* modelButton = m_panel.AddButton("Open Model");
	m_modelDialog = m_panel.AddFileDialog
	(
		"Open Model",
		{ ".gltf" }
	);
	modelButton->SetCallback(m_modelDialog->OpenLambda());

	m_panel.AddCheckbox("Should the next model be lit?", &m_litModel);
	m_panel.AddDragFloat3("Light Direction", m_lightDirVal, 0.002f, -1.0f, 1.0f);
	m_panel.AddSliderFloat("Camera Speed", &m_cameraSpeed, 1.0f, 100.0f);
}

void PropertiesLayer::OnDetach()
{
}

void PropertiesLayer::OnUpdate()
{
	m_panel.GeneratePanel();
	Murky::FlyingCamera* baseCamera = (Murky::FlyingCamera*)(m_camera_ptr.lock().get());
	baseCamera->set_speed(m_cameraSpeed);
}

void PropertiesLayer::SetModelListener(DialogLambda listener)
{
	m_modelDialog->SetCallback(listener);
}
