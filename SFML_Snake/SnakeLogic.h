#pragma once

#include "SnakeDefines.h"

namespace SnakeGame
{
	class Logic
	{
	public:
		Logic();

		void start();
		void reset();
		void update();

		enum class Direction{Up, Down, Left, Right};
		void requestDirectionChange(Direction direction);

		const LogicBoard& getBoard() const;
		unsigned getScore() const;
		bool isGameOver() const;

	private:
		LogicBoard m_board;
		unsigned m_score{};
		bool m_isGameOver{};
		
		std::list<sf::Vector2u> m_snake;
		std::list<Direction> m_directions{};
		sf::Clock m_randomSeedClock;

		void setSnakeOnBoard();
		void move();
		bool isValidDirectionChange(Direction source, Direction target) const;
		void spawnApple();
	};
}