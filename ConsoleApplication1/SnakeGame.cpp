#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include "Snake.h"
#include "Menu.h"
#include "Game.h"
#include "Grid.h"

class Game
{
	private:
		int gameState = 0;
		std::vector<Snake> snake;
		std::vector<sf::CircleShape> food;

	public:
		Game::Game()
			: mWindow(sf::VideoMode(640, 480), "My Test Game")
			, menu(mWindow.getSize().x, mWindow.getSize().y)
			, grid()
		{
			Snake player1(1);
			snake.push_back(player1);
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

		void Game::start()
		{
			gameState = 1;
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
					stop();
					menu.Open(0);
					return;
				}
				if (menu.getSelectedItemIndex() < 0)
				{
					start();
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
				int multiple = 20;
				
				std::random_device rd;
				std::mt19937 eng(rd());
				std::uniform_int_distribution<> r(20, 200);

				int rX = r(eng);
				int rZ = r(eng);

				rX = rX + multiple - 1 - (rX - 1) % multiple;
				rZ = rZ + multiple - 1 - (rZ - 1) % multiple;

				sf::CircleShape foodPiece;
				foodPiece.setRadius(10.f);
				foodPiece.setPosition(rX, rZ);
				foodPiece.setFillColor(sf::Color::Green);
				food.push_back(foodPiece);
			}

		}

		void Game::render()
		{
			mWindow.clear();
			
			if (gameState == 1)
			{
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
			}
			else if (gameState == 0)
			{
				std::cout << "drawing menu" << std::endl;
				menu.Draw(mWindow);
			}
			mWindow.display();
		}

	private:
		sf::RenderWindow mWindow;
		Menu menu;
		Grid grid;

		void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
		{
			for (int i = 0; i < snake.size(); i++)
			{
				snake[i].updateMovement(key, isPressed);
			}
		}
};

int main()
{
	Game game;
	game.run();

	return 0;
}