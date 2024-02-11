#include "mkpch.h"

#include "gui_panels.h"

namespace Murky
{
	GuiPanel::GuiPanel(const char* name)
	{
		m_name = name;
	}
	GuiPanel::~GuiPanel()
	{
		for (size_t i = 0; i < m_elements.size(); i++)
		{
			delete(m_elements[i]);
			m_elements[i] = nullptr;
		}
		for (size_t i = 0; i < m_elements_post_end.size(); i++)
		{
			delete(m_elements_post_end[i]);
			m_elements_post_end[i] = nullptr;
		}
	}
	void GuiPanel::GeneratePanel()
	{
		if (!m_hasBegun)
			ImGui::Begin(m_name);

		for (size_t i = 0; i < m_elements.size(); i++)
		{
			m_elements[i]->Bind();
		}
		m_hasBegun = false;
		ImGui::End();
		for (size_t i = 0; i < m_elements_post_end.size(); i++)
		{
			m_elements_post_end[i]->Bind();
		}
	}
	GuiText* GuiPanel::AddText(const char* text)
	{
		m_elements.emplace_back(new GuiText(text));
		return (GuiText*)m_elements.back();
	}
	GuiCheckbox* GuiPanel::AddCheckbox(const char* label, bool* boolPtr)
	{
		m_elements.emplace_back(new GuiCheckbox(label, boolPtr));
		return (GuiCheckbox*)m_elements.back();
	}
	GuiSliderFloat* GuiPanel::AddSliderFloat(const char* desc, float* sliderRef, float min, float max)
	{
		m_elements.emplace_back(new GuiSliderFloat(desc, sliderRef, min, max));
		return (GuiSliderFloat*)m_elements.back();
	}

	GuiDragFloat3* GuiPanel::AddDragFloat3(const char* label, float* val_ptr, float speed, float min, float max, const char* format, ImGuiSliderFlags flags)
	{
		m_elements.emplace_back(new GuiDragFloat3(label, val_ptr, speed, min, max, format, flags));
		return (GuiDragFloat3*)m_elements.back();
	}

	GuiImage* GuiPanel::AddImage(unsigned long texId, ImVec2 size)
	{
		m_elements.emplace_back(new GuiImage(texId, size));
		return (GuiImage*)m_elements.back();
	}

	GuiButton* GuiPanel::AddButton(const char* text)
	{
		m_elements.emplace_back(new GuiButton(text));
		return (GuiButton*)m_elements.back();
	}

	GuiFileDialog* GuiPanel::AddFileDialog
	(
		const char* title, 
		const std::vector<std::string>& filters, 
		const std::function<void(const std::string&)>& callback)
	{
		m_elements_post_end.emplace_back(new GuiFileDialog(title, filters, callback));
		return (GuiFileDialog*)m_elements_post_end.back();
	}

	GuiViewport::GuiViewport(const char* name)
	{
		m_name = name;
	}
	GuiViewport::~GuiViewport()
	{

	}
	void GuiViewport::Begin(void) { ImGui::Begin(m_name); }
	void GuiViewport::End(void) { ImGui::End(); }
	void GuiViewport::RenderImageViewport(ImVec2 viewportSize, const unsigned long &texId)
	{
		ImGui::Image(
			reinterpret_cast<void*>(texId), 
			ImVec2{ viewportSize.x, viewportSize.y }, 
			ImVec2{ 0, 1 }, 
			ImVec2{ 1, 0 });
	}
}