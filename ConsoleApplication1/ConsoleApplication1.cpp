#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game
{
	private:
		int direction = 2;
		std::vector<sf::CircleShape> snake;
	public:
		Game::Game()
			: mWindow(sf::VideoMode(640, 480), "My Test Game")
			, mPlayer()
		{
			mPlayer.setRadius(10.f);
			mPlayer.setPosition(100.f, 100.f);
			mPlayer.setFillColor(sf::Color::Yellow);

			sf::CircleShape s1;
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
		}
		void Game::run()
		{
			sf::Clock clock;
			sf::Time timeSinceLastUpdate = sf::Time::Zero;
			const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
			while (mWindow.isOpen())
			{
				proccessEvents();
				timeSinceLastUpdate += clock.restart();
				while (timeSinceLastUpdate > timePerFrame)
				{
					timeSinceLastUpdate -= timePerFrame;
					proccessEvents();
					update(timePerFrame);
				}
				render();
			}
		}
	private:
		void proccessEvents()
		{
			sf::Event event;
			while (mWindow.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
						mWindow.close();
						break;
					case sf::Event::KeyPressed:
						handlePlayerInput(event.key.code, true);
						break;
					case sf::Event::KeyReleased:
						handlePlayerInput(event.key.code, false);
						break;
				}
			}
		}
		sf::Clock clock;
		void update(sf::Time deltaTime)
		{
			//Update the snakes body pathing every second
			if (clock.getElapsedTime().asSeconds() > 0.1f)
			{
				clock.restart();
				for (int i = snake.size()-1; i > 0; i--)
				{
					if(i != 0)
					{
						snake[i].setPosition(snake[i - 1].getPosition());
					}
				}
				sf::Vector2f snakePos = snake[0].getPosition();
				if (direction == 1)
				{
					snakePos.x -= 20.f;
				}
				else if (direction == 2)
				{ 
					snakePos.x += 20.f;
				}
				else if (direction == 3)
				{
					snakePos.y -= 20.f;
				}
				else if (direction == 4)
				{
					snakePos.y += 20.f;
				}
				snake[0].setPosition(snakePos);
			}
		}
		void render()
		{
			mWindow.clear();
			for (int i = 0; i < snake.size(); i++)
			{
				mWindow.draw(snake[i]);
			}
			mWindow.display();
		}
	private:
		void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
		{
			if (isPressed)
			{
				if (key == sf::Keyboard::D)
				{
					direction = 2;
				}
				else if (key == sf::Keyboard::A)
				{
					direction = 1;
				}
				else if (key == sf::Keyboard::W)
				{
					direction = 3;
				}
				else if (key == sf::Keyboard::S)
				{
					direction = 4;
				}
				else {
					return;
				}
			}
		}
	private:
		sf::RenderWindow mWindow;
		sf::CircleShape mPlayer;
};

int main()
{
	Game game;
	game.run();
}