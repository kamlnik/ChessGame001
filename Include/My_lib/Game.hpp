/*********************************************************************
 * @file  Game.cpp
 *
 * @brief Contains a start Game.
 *********************************************************************/
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
	/**
	* @brief Game Initialize.
	*/
	Game();
	/**
	* @brief Func that run Game.
	*/
	void run();

private:
	/**
	* @brief Render Window.
	*/
	sf::RenderWindow mWindow;
	/**
	* @brief World element.
	*/
	World mWorld;

};

#endif