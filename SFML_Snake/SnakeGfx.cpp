#include "stdafx.h"
#include "SnakeGfx.h"

#include "SnakeLogic.h"

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
		{
			m_tex[index].loadFromFile(texPaths[index]);
		}

		assert(std::all_of(begin(m_tex), end(m_tex), 
			[](const sf::Texture& tex) 
			{return tex.getSize() == sf::Vector2u(s_texSize, s_texSize); }));

		for (unsigned column{}; column < s_gridSize; ++column)
		{
			for (unsigned row{}; row < s_gridSize; ++row)
			{
				m_board[column][row].setPosition(
					sf::Vector2f{ static_cast<float>(column * s_texSize),
								 static_cast<float>(row * s_texSize) });
			}
		}

		m_font.loadFromFile("res\\ferrum.otf");
		const auto textOffset{ 8.0f };
		const auto textHeight = 24u;
		const auto& textPosition = sf::Vector2f{ textOffset, static_cast<float>(
				s_gridSize * s_texSize) + textOffset };

		m_infoLine1 = sf::Text("", m_font, textHeight);
		m_infoLine1.setPosition(textPosition);
		m_infoLine1.setFillColor(sf::Color::White);

		m_infoLine2 = sf::Text("SPACE TO START, ARROWS TO MOVE", m_font, textHeight);
		m_infoLine2.setPosition(
			textPosition + sf::Vector2f{0.0f, static_cast<float>(textHeight)});
		m_infoLine2.setFillColor(sf::Color::White);
	}

	void Gfx::update(const Logic& logic)
	{
		const auto& logicBoard = logic.getBoard();
		for (unsigned column{}; column < s_gridSize; ++column)
		{
			for (unsigned row{}; row < s_gridSize; ++row)
			{
				m_board[column][row].setTexture(
					m_tex[static_cast<int>(logicBoard[column][row])]);
			}
		}

		std::ostringstream text;
		text << "SCORE: " << logic.getScore();
		if (logic.isGameOver())
		{
			text << " GAME OVER!";
		}
		m_infoLine1.setString(text.str());
	}

	void Gfx::render(DrawFunc draw)
	{
		for (unsigned column{}; column < s_gridSize; ++column)
		{
			for (unsigned row{}; row < s_gridSize; ++row)
			{
				draw(m_board[column][row]);
			}
		}

		draw(m_infoLine1);
		draw(m_infoLine2);
	}
}
