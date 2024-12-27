#include <My_lib/Game.hpp>
#include <SFML/Window/Event.hpp>



Game::Game()
	: mWindow(sf::VideoMode(800, 800), "ChessAPP", sf::Style::Close), mWorld(mWindow){}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	//mWorld.World_processEvent();
	while (mWindow.isOpen())
	{
		mWorld.World_processEvents();
	}
	
}

