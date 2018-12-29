#include "stdafx.h"
#include "SnakeGfx.h"

namespace SnakeGame
{
	Gfx::Gfx()
	{
		std::vector<std::string> texPaths{
			"res\\empty.png",
			"res\\border.png",
			"res\\snakeHead.png",
			"res\\snakeBody.png",
			"res\\snakeDead.png",
			"res\\apple.png"
		};

		m_tex.resize(texPaths.size());
		for (unsigned index{}; index < m_tex.size(); ++index)
			m_tex[index].loadFromFile(texPaths[index]);

		assert(std::all_of(begin(m_tex), end(m_tex), 
			[](const sf::Texture& tex) 
			{return tex.getSize() == sf::Vector2u(s_texSize, s_texSize); }));

		for (unsigned column{}; column < s_gridSize; ++column)
			for (unsigned row{}; row < s_gridSize; ++row)
				m_board[column][row].setPosition(
					sf::Vector2f{static_cast<float>(column * s_texSize),
								 static_cast<float>(row * s_texSize)});
	}

	void Gfx::update(const LogicBoard & logicBoard)
	{
		for (unsigned column{}; column < s_gridSize; ++column)
			for (unsigned row{}; row < s_gridSize; ++row)
				m_board[column][row].setTexture(m_tex[static_cast<int>(logicBoard[column][row])]);
	}

	void Gfx::render(DrawFunc draw)
	{
		for (unsigned column{}; column < s_gridSize; ++column)
			for (unsigned row{}; row < s_gridSize; ++row)
				draw(m_board[column][row]);
	}
}
