#ifndef MY_LIB_GAME_HPP 
#define MY_LIB_GAME_HPP

#include <SFML/Graphics.hpp>
#include <My_lib/World.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Game : private sf::NonCopyable
{
public:
	Game();
	void run();

private:;
	static const sf::Time	TimePerFrame;
	sf::RenderWindow mWindow;
	World mWorld;
	//sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;
};

#endif