
#include "CoolWindow.h"

// ---------- ENTRY POINT ----------
#include <Murky/core/entry_point.h>
// ---------------------------------


class CoolGame : public Murky::Application
{
public:
	CoolGame()
	{
		m_CoolWindow = std::make_unique<CoolWindow>();

		if (m_CoolWindow->Init(1280, 720, "Cool App") == false)
		{
			MK_ERROR("Failed to create new Cool Window!");
		}
	}
	virtual ~CoolGame() override
	{
		
	}

	virtual void Run() override
	{
		while (!m_CoolWindow->ShouldWindowClose())
		{
			m_CoolWindow->Tick();
			m_CoolWindow->Render();
			m_CoolWindow->PollInputs();
		}


	}

	std::unique_ptr<CoolWindow> m_CoolWindow;
};

// Defined and executed by entry_point.h
Murky::Application* Murky::CreateApplication()
{
	return new CoolGame();
}