#include "Game.h"

Game::Game()
{	
	this->initWindow();
	this->initMap();
	
	this->initPlayerAndAi();
	this->initBall();

	this->initFont();
	this->initText();
	this->initMenu();
	this->initSound();
}

Game::~Game()
{
	window->close();
}

void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 500), "Pong", sf::Style::Default);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);

}

void Game::initMap()
{
	map.setSize(sf::Vector2f(760.f, 460.f));
	map.setPosition(sf::Vector2f(20.f, 20.f));
	map.setFillColor(sf::Color::Black);
	map.setOutlineThickness(10.f);
	map.setOutlineColor(sf::Color::White);
}

void Game::initPlayerAndAi()
{
	player.setSize(sf::Vector2f(15.f, 80.f));
	player.setPosition(sf::Vector2f(40.f, 210.f));
	player.setFillColor(sf::Color::White);

	ai.setSize(sf::Vector2f(15.f, 80.f));
	ai.setPosition(sf::Vector2f(745.f, 210.f));
	ai.setFillColor(sf::Color::White);
}

void Game::initBall()
{
	ball.setSize(sf::Vector2f(10.f, 10.f));
	ball.setPosition(sf::Vector2f(400.f, 250.f));
	ball.setFillColor(sf::Color::White);
}

void Game::initSound()
{
	if (!wallBuffer.loadFromFile("Sounds/WallSound.wav"))
	{
		std::cout << "Error" << std::endl;
	}
	wallSound.setBuffer(wallBuffer);
	if (!paddleBuffer.loadFromFile("Sounds/PaddleSound.wav"))
	{
		std::cout << "Error" << std::endl;
	}
	paddleSound.setBuffer(paddleBuffer);
}

void Game::initFont()
{
	if (!font.loadFromFile("Fonts/pixelmix.ttf"))
	{
		std::cout << "Error";
	}
}

void Game::initText()
{
	score.setFont(font);
	score.setCharacterSize(25);
	score.setFillColor(sf::Color::White);
	score.setString(std::to_string(playerPoints) + " : " + std::to_string(aiPoints));
	score.setPosition(sf::Vector2f((map.getGlobalBounds().width + 20)/ 2 - score.getGlobalBounds().width / 2, 22.f));

	for (int i = 0; i < 3; i++)
	{
		buttonsText[i].setFont(font);
		buttonsText[i].setCharacterSize(20);
		buttonsText[i].setFillColor(sf::Color(255, 255, 255, 200));
	}
}

void Game::initMenu()
{
	menu.setOutlineThickness(2.f);
	menu.setSize(sf::Vector2f(250.f, 150.f));
	menu.setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() + 2 * menu.getOutlineThickness() - menu.getGlobalBounds().width) / 2, (map.getGlobalBounds().height - menu.getGlobalBounds().height + 20) / 2));
	menu.setFillColor(sf::Color(0, 0, 0, 0));
	menu.setOutlineColor(sf::Color::White);

	buttonsText[0].setString("New Game");
	buttonsText[1].setString("Quit");

	for (int i = 0; i < 3; i++)
	{
		buttons[i].setSize(sf::Vector2f(200.f, 40.f));
		buttons[i].setFillColor(sf::Color(0, 0, 0, 255));
		buttons[i].setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() - buttons[i].getGlobalBounds().width) / 2, menu.getGlobalBounds().top + (menu.getGlobalBounds().height + menu.getOutlineThickness() * 2 - 2 * 60 + 19) / 2 + i * 60));
		buttonsText[i].setPosition(sf::Vector2f((int)(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonsText[i].getGlobalBounds().width) / 2), (int)(buttons[i].getGlobalBounds().top + buttons[i].getGlobalBounds().height/2 - buttonsText[i].getGlobalBounds().height/2 - 3)));
	}
	buttons[0].setFillColor(sf::Color(20, 20, 20, 255));
}

void Game::pauseMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (prevKey != sf::Keyboard::Escape && mainMenu != 1)
		{
			modeSelection = 0;
			diffSelection = 0;
			temp = 0;
			buttons[0].setFillColor(sf::Color(20, 20, 20, 255));
			buttons[1].setFillColor(sf::Color(0, 0, 0, 255));
			buttonsText[0].setString("New Game");
			buttonsText[1].setString("Quit");

			menu.setSize(sf::Vector2f(250.f, 150.f));
			menu.setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() + 2 * menu.getOutlineThickness() - menu.getGlobalBounds().width) / 2, (map.getGlobalBounds().height - menu.getGlobalBounds().height + 20) / 2));

			for (int i = 0; i < 2; i++)
			{
				buttons[i].setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() - buttons[i].getGlobalBounds().width) / 2, menu.getGlobalBounds().top + (menu.getGlobalBounds().height + menu.getOutlineThickness() * 2 - 2 * 60 + 19) / 2 + i * 60));
				buttonsText[i].setPosition(sf::Vector2f((int)(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonsText[i].getGlobalBounds().width) / 2), (int)(buttons[i].getGlobalBounds().top + buttons[i].getGlobalBounds().height / 2 - buttonsText[i].getGlobalBounds().height / 2 - 3)));
			}

			if (stop == 0)
			{
				stopMenu = 1;
				stop = 1;
			}
			else
			{
				stopMenu = 0;
				stop = 0;
			}
		}
		prevKey = sf::Keyboard::Escape;
	}
	else
	{
		prevKey = 0;
	}
}

void Game::modeSelect()
{
	menu.setSize(sf::Vector2f(250.f, 150.f));
	menu.setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() + 2 * menu.getOutlineThickness() - menu.getGlobalBounds().width) / 2, (map.getGlobalBounds().height - menu.getGlobalBounds().height + 20) / 2));

	buttonsText[0].setString("1 Player");
	buttonsText[1].setString("2 Players");

	for (int i = 0; i < 2; i++)
	{
		buttons[i].setFillColor(sf::Color(0, 0, 0, 255));
		buttons[i].setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() - buttons[i].getGlobalBounds().width) / 2, menu.getGlobalBounds().top + (menu.getGlobalBounds().height + menu.getOutlineThickness() * 2 - 2 * 60 + 19) / 2 + i * 60));
		buttonsText[i].setPosition(sf::Vector2f((int)(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonsText[i].getGlobalBounds().width) / 2), (int)(buttons[i].getGlobalBounds().top + buttons[i].getGlobalBounds().height / 2 - buttonsText[i].getGlobalBounds().height / 2 - 3)));
	}
	buttons[0].setFillColor(sf::Color(20, 20, 20, 255));
}

void Game::diffSelect()
{
	menu.setSize(sf::Vector2f(250.f, 225.f));
	menu.setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() + 2 * menu.getOutlineThickness() - menu.getGlobalBounds().width) / 2, (map.getGlobalBounds().height - menu.getGlobalBounds().height + 20) / 2));

	buttonsText[0].setString("Easy");
	buttonsText[1].setString("Medium");
	buttonsText[2].setString("Hard");

	for (int i = 0; i < 3; i++)
	{
		buttons[i].setFillColor(sf::Color(0, 0, 0, 255));
		buttons[i].setPosition(sf::Vector2f((map.getGlobalBounds().width + 2 * map.getOutlineThickness() - buttons[i].getGlobalBounds().width) / 2, menu.getGlobalBounds().top + (menu.getGlobalBounds().height + menu.getOutlineThickness() * 2 - 3 * 60 + 19) / 2 + i * 60));
		buttonsText[i].setPosition(sf::Vector2f((int)(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonsText[i].getGlobalBounds().width) / 2), (int)(buttons[i].getGlobalBounds().top + buttons[i].getGlobalBounds().height / 2 - buttonsText[i].getGlobalBounds().height / 2 - 3)));
	}
	buttons[0].setFillColor(sf::Color(20, 20, 20, 255));
}

void Game::playerMove()
{
	//Klawiatura
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		player.move(0.f, -5.f);
		playerMoved = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		player.move(0.f, 5.f);
		playerMoved = 1;
	}
	
	//Kolizja z œcianami
	if (player.getPosition().y <= 22)
	{
		player.setPosition(sf::Vector2f(40.f, 23.f));
	}
	else if (player.getPosition().y + 80 >= 478)
	{
		player.setPosition(sf::Vector2f(40.f, 397.f));
	}
}

void Game::player2Move()
{
	//Klawiatura
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		ai.move(0.f, -5.f);
		aiMoved = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		ai.move(0.f, 5.f);
		aiMoved = 1;
	}

	//Kolizja z œcianami
	if (ai.getPosition().y <= 22)
	{
		ai.setPosition(sf::Vector2f(745.f, 23.f));
	}
	else if (ai.getPosition().y + 80 >= 478)
	{
		ai.setPosition(sf::Vector2f(745.f, 397.f));
	}
}

void Game::aiMove()
{
	//Œledzenie pi³ki
	float aiBallTracking = ball.getPosition().y + 5 - ai.getPosition().y - 40 + 0.01;
	//std::cout << abs(aiBallTracking) << " " << (20 + 800 / ball.getGlobalBounds().left + 5) + 3 * (diff + 1) << std::endl;
	if (abs(aiBallTracking) >= (20 + 800 / ball.getGlobalBounds().left + 5) + 3 * (diff + 1))
	{
		//std::cout << (1 + diff) << " " << (diff + 3.f) * aiBallTracking / abs(aiBallTracking) << std::endl;
		ai.move(0.f, (diff + 3.f) * aiBallTracking / abs(aiBallTracking));
	}
	else
	{
		//std::cout << (1 + diff) << " " << (((float)diff / 4) + 0.5f) * aiBallTracking / abs(aiBallTracking) << std::endl;
		ai.move(0.f, (((float)diff / 4) + 0.5f) * aiBallTracking / abs(aiBallTracking));
	}
	aiMoved = 1;
	
	//Kolizja ze œcianami
	if (ai.getPosition().y <= 22)
	{
		ai.setPosition(sf::Vector2f(745.f, 23.f));
	}
	else if (ai.getPosition().y + 80 >= 478)
	{
		ai.setPosition(sf::Vector2f(745.f, 397.f));
	}
}

void Game::ballMove()
{
	if (abs(ballMoveX) >= 8)
	{
		ballSpeedChangeX = 0;
	}
	
	//kolizja z œcianami
	if (ball.getPosition().y <= 20)
	{
		ball.setPosition(sf::Vector2f(ball.getPosition().x, 21));
		ballMoveY = -ballMoveY;
		wallSound.play();
	}
	else if (ball.getPosition().y + 10 >= 480)
	{
		ball.setPosition(sf::Vector2f(ball.getPosition().x, 469));
		ballMoveY = -ballMoveY;
		wallSound.play();
	}

	//std::cout << "abs: " << abs(ball.getPosition().y - player.getPosition().y - 80) << " " << abs(ball.getPosition().y - ai.getPosition().y - 80) << std::endl;
	//Kolizja z graczem
	if (player.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		//std::cout << "player: " << player.getPosition().x + 15 - ball.getPosition().x << " 2: " << ball.getPosition().y << " " << player.getPosition().y << " : " << abs(ball.getPosition().y - player.getPosition().y - 80) << std::endl;
		if (ball.getPosition().y + 10 <= player.getPosition().y + 15 && player.getPosition().x + 15 - ball.getPosition().x > abs(ball.getPosition().y - player.getPosition().y))
		{
			//std::cout << "left" << std::endl;
			ballMoveY = ballMoveY * 2;
			if (ballMoveY >= 0)
			{
				ballMoveY = -ballMoveY;
			}
			ball.move(sf::Vector2f(0.f, playerMoved * -10.f));
		}
		else if (ball.getPosition().y >= player.getPosition().y + 65 && player.getPosition().x + 15 - ball.getPosition().x > abs(ball.getPosition().y - player.getPosition().y - 80))
		{
			//std::cout << "right" << std::endl;
			ballMoveY = ballMoveY * 2;
			if (ballMoveY <= 0)
			{
				ballMoveY = -ballMoveY;
			}
			ball.move(sf::Vector2f(0.f, playerMoved * 10.f));
		}
		else
		{
			//std::cout << "else" << std::endl;
			ball.setPosition(sf::Vector2f(player.getPosition().x + 16, ball.getPosition().y));
			ballMoveX = -ballMoveX + ballSpeedChangeX;
			ballMoveY += (ball.getPosition().y + 5 - (player.getPosition().y + 40)) / 40;
		}
		paddleSound.play();
	}

	//Kolizja z ai / 2 graczem
	else if (ai.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		//std::cout << "ai: " << ball.getPosition().x + 10 - ai.getPosition().x << " 2: " << ball.getPosition().y << " " << ai.getPosition().y << " : " << abs(ball.getPosition().y - ai.getPosition().y - 80) << std::endl;
		if (ball.getPosition().y + 10 <= ai.getPosition().y + 15 && ball.getPosition().x + 10 - ai.getPosition().x > abs(ball.getPosition().y - ai.getPosition().y))
		{
			//std::cout << "left ai" << std::endl;
			ballMoveY = ballMoveY * 2;
			if (ballMoveY >= 0)
			{
				ballMoveY = -ballMoveY;
			}
			ball.move(sf::Vector2f(0.f, aiMoved * -10.f));
		}
		else if (ball.getPosition().y >= ai.getPosition().y + 65 && ball.getPosition().x + 10 - ai.getPosition().x > abs(ball.getPosition().y - ai.getPosition().y - 80))
		{
			//std::cout << "rigt ai" << std::endl;
			ballMoveY = ballMoveY * 2;
			if (ballMoveY <= 0)
			{
				ballMoveY = -ballMoveY;
			}
			ball.move(sf::Vector2f(0.f, aiMoved * 10.f));
		}
		else
		{
			//std::cout << "else ai" << std::endl;
			ball.setPosition(sf::Vector2f(ai.getPosition().x - 16, ball.getPosition().y));
			ballMoveX = -ballMoveX - ballSpeedChangeX;
			ballMoveY += (ball.getPosition().y + 5 - (ai.getPosition().y + 40)) / 40;
		}
		paddleSound.play();
	}
	playerMoved = 0;
	aiMoved = 0;
	ball.move(sf::Vector2f(ballMoveX, ballMoveY));
}

void Game::ballScore()
{
	if (ball.getPosition().x <= 20)
	{
		aiPoints++;
		roundOver();
	}
	else if (ball.getPosition().x >= 770)
	{
		playerPoints++;
		roundOver();
	}
}

void Game::updating()
{
	sf::Event ev;
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
			case sf::Event::Closed():
				window->close();
			break;

			case sf::Event::KeyPressed:
				if (stop == 1)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						if (buttons[0].getFillColor() == sf::Color(20, 20, 20, 255))
						{
							if (modeSelection == 1)
							{
								gameMode = 0;
								modeSelection = 0;
								diffSelection = 1;
								diffSelect();
							}
							else if (diffSelection == 1)
							{
								mainMenu = 0;
								diff = 0;
								diffSelection = 0;
								stop = 0;
							}
							else
							{
								gameReset();
							}
						}
						else if (buttons[1].getFillColor() == sf::Color(20, 20, 20, 255))
						{
							if (modeSelection == 1)
							{
								mainMenu = 0;
								gameMode = 1;
								modeSelection = 0;
								stop = 0;
							}
							else if (diffSelection == 1)
							{
								mainMenu = 0;
								diff = 1;
								diffSelection = 0;
								stop = 0;
							}
							else
							{
								window->close();
							}
						}
						else if (buttons[2].getFillColor() == sf::Color(20, 20, 20, 255))
						{
							mainMenu = 0;
							diff = 2;
							diffSelection = 0;
							stop = 0;
						}
					}

					int key = 0;
					int help = 1;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						key = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						key = -1;
						help = 0;
					}

					buttons[temp].setFillColor(sf::Color(0, 0, 0, 255));
					if (temp == help * (key + diffSelection))
					{
						temp = abs((help - 1)) * (temp + 1 + diffSelection);
						buttons[temp].setFillColor(sf::Color(20, 20, 20, 255));
					}
					else
					{
						temp = temp + key;
						buttons[temp].setFillColor(sf::Color(20, 20, 20, 255));
					}
				}
			break;

			default:
			break;
		}
	}

	pauseMenu();

	if (stop == 0)
	{
		ballMove();
		playerMove();
		if (gameMode == 1)
		{
			player2Move();
		}
		else
		{
			aiMove();
		}
		ballScore();
	}
}

void Game::rendering()
{
	window->clear();

	window->draw(map);
	window->draw(player);
	window->draw(ai);
	window->draw(ball);
	window->draw(score);

	if (stop == 1)
	{
		window->draw(menu);
		for (int i = 0; i < 2 + diffSelection; i++)
		{
			window->draw(buttons[i]);
			window->draw(buttonsText[i]);
		}
	}

	window->display();
}

bool Game::getIsOpen()
{
	return window->isOpen();
}

void Game::roundOver()
{
	ballMoveX = -3.f + (rand() % 2) * 6.f;
	ballMoveY = (rand() % 2 * 2) - 1.f;
	ballSpeedChangeX = 0.3f;
	ballSpeedChangeY = 0.f;
	ballSpeedChangeY_ai = 0.f;

	initText();
	initPlayerAndAi();
	initBall();
}

void Game::gameReset()
{
	playerPoints = 0;
	aiPoints = 0;
	modeSelection = 1;
	stop = 1;
	stopMenu = 0;
	gameMode = 0;

	ballMoveX = -3.f + (rand() % 2) * 6.f;
	ballMoveY = (rand() % 2 * 2) - 1.f;
	ballSpeedChangeX = 0.3f;
	ballSpeedChangeY = 0.f;
	ballSpeedChangeY_ai = 0.f;

	initText();
	initPlayerAndAi();
	initBall();
	modeSelect();
}