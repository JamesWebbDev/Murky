#include <Murky.h>

class CoolGame : public Murky::Application
{
public:
	CoolGame()
	{

	}
	~CoolGame()
	{

	}
};

Murky::Application* Murky::CreateApplication()
{
	return new CoolGame();
}