#ifndef GUI_ELEMENTS_H
#define GUI_ELEMENTS_H

#include "../core/core.h"
#include <imgui.h>
#include "imfilebrowser.h"

typedef MURKY_API std::function<void(const std::string&)> DialogLambda;

namespace Murky
{
	class MURKY_API GuiElement
	{
	public:
		virtual void Bind() = 0;
	};

	class MURKY_API GuiText : public GuiElement
	{
	public:
		GuiText(const char* text)    { m_text = text; }
		virtual void Bind() override { ImGui::Text(m_text); }
	private:
		const char* m_text;
	};

	class MURKY_API GuiCheckbox : public GuiElement
	{
	public:
		GuiCheckbox(const char* label, bool* valPtr)
		{
			m_label = label;
			m_val_ptr = valPtr;
		}
		virtual void Bind() override
		{
			ImGui::Checkbox(m_label, m_val_ptr);
		}
	private:
		const char* m_label;
		bool* m_val_ptr;
	};

	class MURKY_API GuiSliderFloat : public GuiElement
	{
	public:
		GuiSliderFloat(const char* desc, float* sliderRef, float min, float max) 
		{ 
			m_desc = desc;
			m_val_ptr = sliderRef;
			m_min = min;
			m_max = max;
		}
		virtual void Bind() override 
		{ 
			ImGui::SliderFloat(m_desc, m_val_ptr, m_min, m_max);
		}
	private:
		const char* m_desc;
		float* m_val_ptr;
		float m_min, m_max;
	};

	class MURKY_API GuiDragFloat3 : public GuiElement
	{
	public:
		GuiDragFloat3(
			const char* label, 
			float* val_ptr, 
			float speed = 1.0f, 
			float min = 0.0f, 
			float max = 1.0f, 
			const char* format = "%.3f",
			ImGuiSliderFlags flags = 0)
		{
			m_label = label; m_val_ptr = val_ptr; m_speed = speed; 
			m_min = min; m_max = max; m_format = format; m_flags = flags;
		}
		virtual void Bind() override
		{
			ImGui::DragFloat3(m_label, m_val_ptr, m_speed, m_min, m_max, m_format, m_flags);
		}
	private:
		const char* m_label;
		float* m_val_ptr;
		float m_speed, m_min, m_max;
		const char* m_format;
		ImGuiSliderFlags m_flags;
	};

	class MURKY_API GuiImage : public GuiElement
	{
	public:
		GuiImage(unsigned long texId = 0, ImVec2 size = { 100, 100 })
		{
			m_texId = texId;
			m_size = size;
		}

		virtual void Bind() override
		{
			ImGui::Image(
				reinterpret_cast<void*>(m_texId), 
				m_size, 
				ImVec2{0,1}, 
				ImVec2{1,0});
		}

		void SetTexId(unsigned long texId) { m_texId = texId; }
		void SetTexSize(ImVec2 size) { m_size = size; }

	private:
		unsigned long m_texId;
		ImVec2 m_size;
	};

	class MURKY_API GuiButton : public GuiElement
	{
	public:
		GuiButton(const char* name)
		{
			m_name = name;
		}

		virtual void Bind() override
		{
			if (ImGui::Button(m_name))
			{
				// If clicked
				m_callback();
			}
		}

		void SetCallback(const std::function<void()>& callback)
		{
			m_callback = callback;
		}
	private:
		const char* m_name;
		std::function<void()> m_callback;
	};

	class MURKY_API GuiFileDialog : public GuiElement
	{
	public:
		GuiFileDialog
		(
			const char* title, 
			const std::vector<std::string>& filters,
			const std::function<void(const std::string&)>& callback
		)
		{
			m_current_file = "< ... >";
			m_file_dialog.SetTitle(title);
			m_file_dialog.SetTypeFilters(filters); // E.g. { ".gltf" }
			if (callback != NULL)
				SetCallback(callback);
		}

		virtual void Bind() override
		{
			m_file_dialog.Display();
			if (m_file_dialog.HasSelected())
			{
				auto file_path = m_file_dialog.GetSelected().string();
				m_current_file = file_path.substr(file_path.find_last_of("/\\") + 1);

				if (m_callback != NULL)
					m_callback(file_path);
				else
					m_callback_default();

				m_file_dialog.ClearSelected();
			}
		}

		void Open()
		{
			m_file_dialog.Open();
		}

		std::function<void()> OpenLambda()
		{
			return [this]() { Open(); };
		}

		void SetCallback(const std::function<void(const std::string&)>& callback)
		{
			m_callback = callback;
		}

	private:

		const char* m_title;

		ImGui::FileBrowser m_file_dialog;

		std::function<void(const std::string&)> m_callback;
		const std::function<void()> m_callback_default = 
			[this](){ MK_ENG_WARN("Callback is not set on {0} File Dialog!", m_title); };
		std::string m_current_file;


	};


}


#endif