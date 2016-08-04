#include <SFML/Graphics.hpp>
#include "Game.h"

Game game;

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "My Test Game")
	, menu(mWindow.getSize().x, mWindow.getSize().y)
	, grid(mWindow.getSize().y)
{

	if (!font.loadFromFile("Font/arial.ttf"))
	{

	}
	/*
	sf::CircleShape s1;0
	s1.setRadius(10.f);
	s1.setPosition(80.f, 100.f);
	s1.setFillColor(sf::Color::Cyan);
	sf::CircleShape s2;
	s2.setRadius(10.f);
	s2.setPosition(60.f, 100.f);
	s2.setFillColor(sf::Color::Cyan);
	sf::CircleShape s3;
	s3.setRadius(10.f);
	s3.setPosition(40.f, 100.f);
	s3.setFillColor(sf::Color::Cyan);

	//Test data for snake
	snake.push_back(mPlayer);
	snake.push_back(s1);
	snake.push_back(s2);
	snake.push_back(s3);
	*/
}
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
			
	while (mWindow.isOpen())
	{
				
		//Only continue with gamelogic if the gamestate is running (1)
		proccessEvents();
		if (gameState == 1)
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				proccessEvents();
				update(timePerFrame);
			}
		}
		render();
	}
}

bool Game::isRunning()
{
	return gameState == 1;
}

void Game::start(bool reset)
{
	gameState = 1;

	for (int i = 1; i < playerCount+1; i++)
	{
		Snake s(i);
		snake.push_back(s);
	}

	//Reset scores etc
	if (reset)
	{
				
	}
}

void Game::stop()
{
	gameState = 0;
}

void Game::proccessEvents()
{
	//Check all other events
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			if (isRunning())
			{
				stop();
				menu.Open(0);
			}
			else
			{
				start(false);
				menu.Close();
			}

			return;
		}
		if (menu.getSelectedItemIndex() < 0)
		{
			start(true);
		}
		if (gameState == 1)
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			}
		}
		if (gameState == 0 && menu.isOpen())
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				menu.handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				menu.handleInput(event.key.code, false);
				break;
			}
		}
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	for (int i = 0; i < snake.size();i++)
	{
		snake[i].update(deltaTime);
	}
	if (food.size() < 1)
	{
		generateFood();

	}
	if (snake.size() > 0 && snake[0].getBody()[0].getPosition() != lastPos)
	{
		//Food collision check
		for (int i = 0; i < food.size(); i++)
		{
			for (int s = 0; s < snake.size(); s++)
			{
				if (grid.getTileAt(snake[s].getBody()[0].getPosition()) == grid.getTileAt(food[i].getPosition()))
				{
					snake[s].handleCollision(food[i], true);
					//food.erase(food.begin() + i);
				}
			}
			//snake.erase(snake.begin() + s);
		}
		/*
		//Check for body collision
		for (int i = 0; i < snake.size(); i++)
		{
			for (int s = 0; s < snake.size(); s++)
			{
				for (int b = 0; b < snake[s].getBody().size();b++)
				{
					if (snake[i].getBody()[0].getPosition() == snake[s].getBody()[b].getPosition())
					{
						snake.erase(snake.begin() + i);
					}
				}
			}
		}
		*/
		lastPos = snake[0].getBody()[0].getPosition();
	}
}

void Game::render()
{
	mWindow.clear();
			
	if (gameState == 1)
	{
		grid.draw(mWindow);
		//Loop over all snakes
		for (int i = 0; i < snake.size(); i++)
		{
			//For each snake loop over the body and draw them to screen
			for (int part = 0; part < snake[i].getBody().size(); part++)
			{
				mWindow.draw(snake[i].getBody()[part]);
			}
		}
		//Draw the food on screen
		for (int i = 0; i < food.size(); i++)
		{
			mWindow.draw(food[i]);
		}

		sf::Text text;
		std::string str = "Scores";
			
		text.setFont(font);
		text.setCharacterSize(12);
		for (int i = 0; i < snake.size(); i++)
		{
			str += "\nPlayer " + std::to_string(snake[i].getNumber()) +  " - " + std::to_string(snake[i].getScore());
		}

		text.setString(str);
		mWindow.draw(text);
	}
	else if (gameState == 0)
	{
		menu.Draw(mWindow);
	}
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	for (int i = 0; i < snake.size(); i++)
	{
		snake[i].updateMovement(key, isPressed);
	}
}

void Game::generateFood()
{
	if (food.size() < 1)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> rWidth(0.f, mWindow.getSize().x);
		std::uniform_int_distribution<> rHeight(0.f, mWindow.getSize().y);

		int rX = rWidth(eng);
		int rZ = rHeight(eng);

		sf::Vector2f tile = grid.getTileAt(sf::Vector2f(rX, rZ));

		sf::CircleShape foodPiece;
		foodPiece.setRadius(10.f);
		foodPiece.setPosition(tile.x, tile.y);
		foodPiece.setFillColor(sf::Color::Green);
		food.push_back(foodPiece);
	}
}

void Game::setPlayers(int players)
{
	playerCount = players;
}

int main()
{
	Game game;
	game.run();

	return 0;
}