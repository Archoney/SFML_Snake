#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace SnakeGame
{
	static const unsigned s_frameTime{ 200 };
	static const unsigned s_gridSize{ 10 };
	static const unsigned s_texSize{ 32 };
	static const unsigned s_infoHeight{ 64 };
	static const unsigned s_snakeStartSize{ (s_gridSize / 2) - 1 };
	static const sf::Vector2u s_resolution{ 
		s_gridSize * s_texSize, 
		s_gridSize * s_texSize + s_infoHeight };

	enum class BoardObject
	{
		Empty,
		Border,
		SnakeHead,
		SnakeBody,
		SnakeDead,
		Apple
	};

	using LogicBoard = std::array<std::array<BoardObject, s_gridSize>, s_gridSize>;
	using GfxBoard = std::array<std::array<sf::Sprite, s_gridSize>, s_gridSize>;
}