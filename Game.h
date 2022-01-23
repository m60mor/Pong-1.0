#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
	sf::RenderWindow* window;
	sf::RectangleShape map;
	sf::RectangleShape player;
	sf::RectangleShape ai;
	sf::RectangleShape ball;

	sf::RectangleShape menu;
	sf::RectangleShape button1;
	sf::RectangleShape button2;
	sf::RectangleShape button3;
	sf::RectangleShape buttons[3] = { button1, button2, button3 };

	sf::Font font;
	sf::Text score;
	sf::Text button1text;
	sf::Text button2text;
	sf::Text button3text;
	sf::Text buttonsText[3] = { button1text, button2text, button3text };

	sf::SoundBuffer wallBuffer;
	sf::Sound wallSound;
	sf::SoundBuffer paddleBuffer;
	sf::Sound paddleSound;

	bool mainMenu = 1;
	bool stopMenu = 1;
	bool stop = 1;
	bool diffSelection = 0;
	int temp = 0;
	int prevKey = sf::Keyboard::Escape;

	float ballMoveX = -3.f + (rand() % 2) * 6.f;
	float ballMoveY = (rand()%2 * 2) - 1.f;
	float ballSpeedChangeX = 0.3f;
	float ballSpeedChangeY = 0.f;
	float ballSpeedChangeY_ai = 0.f;

	bool playerMoved = 0;
	bool aiMoved = 0;

	void initWindow();
	void initMenu();
	void initMap();
	void initPlayerAndAi();
	void initBall();

	void initSound();

	void initFont();
	void initText();

	void playerMove();
	void player2Move();
	void aiMove();
	void ballMove();
	void ballScore();
	
	void pauseMenu();
	void modeSelect();
	void diffSelect();
	void roundOver();
	void gameReset();

public:
	Game();
	~Game();

	bool modeSelection = 0;
	int playerPoints = 0;
	int aiPoints = 0;
	int diff = 0;
	int gameMode = 0;

	bool getIsOpen();

	void updating();
	void rendering();
};

