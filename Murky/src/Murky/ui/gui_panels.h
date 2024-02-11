#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include "../core/core.h"

#include "gui_elements.h"

namespace Murky
{
	class MURKY_API GuiPanel
	{
	public:

		GuiPanel() {}
		GuiPanel(const char* name);
		~GuiPanel();

		inline void PreBegin() { m_hasBegun = true; ImGui::Begin(m_name); }
		void GeneratePanel();
		GuiText* AddText(const char* text);
		GuiCheckbox* AddCheckbox(const char* label, bool* boolPtr);
		GuiSliderFloat* AddSliderFloat(const char* desc, float* sliderRef, float min, float max);
		GuiDragFloat3* AddDragFloat3(const char* label, float* val_ptr, float speed, float min, float max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
		GuiImage* AddImage(unsigned long texId = 0, ImVec2 size = {100,100});
		GuiButton* AddButton(const char* text);
		GuiFileDialog* AddFileDialog
		(
			const char* title,
			const std::vector<std::string>& filters, 
			const std::function<void(const std::string&)>& callback = NULL
		);

		std::vector<GuiElement*> m_elements;
		std::vector<GuiElement*> m_elements_post_end;

	private:
		const char* m_name = "";
		bool m_hasBegun = false;
	};

	class MURKY_API GuiViewport
	{
	public:

		GuiViewport() {}
		GuiViewport(const char* name);
		~GuiViewport();

		void Begin(void);
		void End(void);
		void RenderImageViewport(ImVec2 viewportSize, const unsigned long& texId = 0);

	private:
		unsigned long m_texId = 0;
		const char* m_name = "";
	};

}

#endif