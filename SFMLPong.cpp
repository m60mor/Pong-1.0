#include <iostream>

#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main()
{
	Game game;
	//Petla gry
	while (game.getIsOpen())
	{
		game.updating();

		game.rendering();
	}
}

