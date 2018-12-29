#include "stdafx.h"
#include "SnakeLogic.h"

namespace SnakeGame
{
	Logic::Logic()
	{
		reset();
	}

	void Logic::start()
	{
		if (m_isGameOver)
		{
			reset();
		}
		
		m_directions.push_back(Direction::Up);
	}

	void Logic::reset()
	{
		m_directions.clear();
		m_score = 0;
		m_isGameOver = false;

		for (unsigned column{}; column < s_gridSize; ++column)
		{
			for (unsigned row{}; row < s_gridSize; ++row)
			{
				const bool isOnBorder = column == 0 || row == 0
					|| column == s_gridSize - 1 || row == s_gridSize - 1;
				m_board[column][row] = isOnBorder ?
					BoardObject::Border : BoardObject::Empty;
			}
		}

		m_snake.clear();
		const auto& snakeHeadCoord = sf::Vector2u{ s_gridSize / 2, s_gridSize / 2 };
		for (unsigned index = 0; index < s_snakeStartSize; ++index)
		{
			m_snake.emplace_back(sf::Vector2u{ snakeHeadCoord.x, snakeHeadCoord.y + index });
		}

		setSnakeOnBoard();
		spawnApple();
	}

	void Logic::setSnakeOnBoard()
	{
		for (const auto& snakeSegment : m_snake)
		{
			m_board[snakeSegment.x][snakeSegment.y] = BoardObject::SnakeBody;
		}

		const auto snakeHead = m_snake.front();
		m_board[snakeHead.x][snakeHead.y] = m_isGameOver ?
			BoardObject::SnakeDead : BoardObject::SnakeHead;
	}

	void Logic::spawnApple()
	{
		std::vector<sf::Vector2u> validCoords;
		for (unsigned column{}; column < s_gridSize; ++column)
		{
			for (unsigned row{}; row < s_gridSize; ++row)
			{
				if (m_board[column][row] == BoardObject::Empty)
				{
					validCoords.push_back(sf::Vector2u{ column, row });
				}
			}
		}

		if (validCoords.empty())
		{
			m_isGameOver = true;
		}
		else if (validCoords.size() == 1)
		{
			const auto& coord = validCoords.front();
			m_board[coord.x][coord.y] = BoardObject::Apple;
		}
		else
		{
			std::mt19937 randomEngine(m_randomSeedClock.getElapsedTime().asMilliseconds());
			std::uniform_int_distribution<size_t> uniformDistribution(0, validCoords.size() - 1);
			const size_t randomIndex = uniformDistribution(randomEngine);

			const auto& coord = validCoords[randomIndex];
			m_board[coord.x][coord.y] = BoardObject::Apple;
		}
	}

	void Logic::update()
	{
		if (!m_isGameOver && !m_directions.empty())
		{
			if (m_directions.size() > 1)
			{
				m_directions.pop_front();
			}

			move();
			setSnakeOnBoard();
		}
	}

	void Logic::move()
	{
		auto target = m_snake.front();
		switch (m_directions.front())
		{
		case Direction::Up:		target -= sf::Vector2u{ 0, 1 }; break;
		case Direction::Down:	target += sf::Vector2u{ 0, 1 }; break;
		case Direction::Left:	target -= sf::Vector2u{ 1, 0 }; break;
		case Direction::Right:	target += sf::Vector2u{ 1, 0 }; break;
		default: break;
		}

		m_snake.emplace_front(target);
		if (m_board[target.x][target.y] != BoardObject::Apple)
		{
			const auto& tail = m_snake.back();
			m_board[tail.x][tail.y] = BoardObject::Empty;
			m_snake.pop_back();
		}
		else
		{
			spawnApple();
			++m_score;
		}

		if (m_board[target.x][target.y] == BoardObject::Border
			|| m_board[target.x][target.y] == BoardObject::SnakeBody)
		{
			m_isGameOver = true;
		}
	}

	void Logic::requestDirectionChange(Direction direction)
	{
		if (!m_directions.empty() && m_directions.size() <= 3
			&& isValidDirectionChange(m_directions.back(), direction))
		{
			m_directions.push_back(direction);
		}
	}

	bool Logic::isValidDirectionChange(Direction source, Direction target) const
	{
		if (source == target)
		{
			return false;
		}

		switch (target)
		{
		case Direction::Up:		return source != Direction::Down;
		case Direction::Down:	return source != Direction::Up;
		case Direction::Left:	return source != Direction::Right;
		case Direction::Right:	return source != Direction::Left;
		default: return false;
		}
	}

	const LogicBoard& Logic::getBoard() const
	{
		return m_board;
	}

	unsigned Logic::getScore() const
	{
		return m_score;
	}

	bool Logic::isGameOver() const
	{
		return m_isGameOver;
	}
}
