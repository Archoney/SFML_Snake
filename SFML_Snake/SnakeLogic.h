#pragma once

#include "SnakeDefines.h"

namespace SnakeGame
{
	class Logic
	{
	public:
		Logic();

		void reset();
		void update();

		enum class Direction{Up, Down, Left, Right};
		void requestDirectionChange(Direction direction);

		const LogicBoard& getBoard() const;
		bool isGameOver() const;

	private:
		LogicBoard m_board;
		std::list<sf::Vector2u> m_snake;
		std::list<Direction> m_directions{};
		bool m_isGameOver{};
		sf::Clock m_randomSeedClock;

		void setSnakeOnBoard();
		void move();
		bool isValidDirectionChange(Direction source, Direction target) const;
		void spawnApple();
	};
}