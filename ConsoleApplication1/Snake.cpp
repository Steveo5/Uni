#include "Snake.h"

#include <iostream>
#include <math.h>

Snake::Snake(int playerNo)
{
	sf::CircleShape mPlayer;
	mPlayer.setRadius(10.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Yellow);
	snake.push_back(mPlayer);
}

void Snake::update(sf::Time deltaTime)
{
	//Update the snake every 10th of a second
	if (clock.getElapsedTime().asSeconds() > 0.1f)
	{
		//Restart the clock
		clock.restart();

		//Update the snakes body segement locations
		for (int i = snake.size() - 1; i > 0; i--)
		{
					sf::Vector2f previousPos = snake[i - 1].getPosition();
					//yPos = yPos + 20 - 1 - (yPos - 1) % 20;

					snake[i].setPosition(previousPos);
	
		}
		//Get the snakes head location
		sf::Vector2f snakePos = snake[0].getPosition();

		//Find the snakes direction and keep the momentum going
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
		//Changing the snakes head location
		//snake[0].move(snakePos * deltaTime.asSeconds());
		//Check if the snake is colliding with itself
		for (int i = 0; i < snake.size(); i++)
		{
			sf::Vector2f pos = snake[i].getPosition();
			if (i > 0 && pos == snakePos)
			{
				
			}
			//Checking if the snake is out of bounds
			if (pos.x > 640.0f)
			{
				pos.x = 0.0f;
			}
			else if (pos.x < 0.0f)
			{
				pos.x = 640.0f;
			}
			else if (pos.y > 480.0f)
			{
				pos.y = 0.0f;
			}
			else if (pos.y < 0.0f)
			{
				pos.y = 480.0f;
			}

			if (pos != snake[i].getPosition())
			{
				snake[i].setPosition(pos);
			}
		}
		//Check if the snake is eating food
		/*
		for (int i = 0; i < food.size(); i++)
		{
			if (food[i].getPosition().x == snakePos.x && food[i].getPosition().y == snakePos.y)
			{
				food.erase(food.begin() + 0);

				sf::CircleShape part;
				part.setRadius(10.f);
				part.setPosition(-10000.f, -10000.f);
				part.setFillColor(sf::Color::Cyan);
				snake.push_back(part);
			}
		}
		*/
	}
}
void Snake::updateMovement(sf::Keyboard::Key key, bool isPressed)
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

//Get the body segments where index 0 is the snakes head
std::vector<sf::CircleShape> &Snake::getBody()
{
	return snake;
}

void Snake::handleCollision(sf::CircleShape obj, bool isFood)
{
	if (isFood)
	{
		sf::CircleShape segment;
		segment.setRadius(10.f);
		segment.setPosition(100000.f, 100000.f);
		segment.setFillColor(sf::Color::Cyan);
		snake.push_back(segment);
		score += 20;
	}
}

int Snake::getScore()
{
	return score;
}

void Snake::setScore(int newScore)
{
	score = newScore;
}