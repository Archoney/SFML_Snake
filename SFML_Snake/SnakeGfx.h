#pragma once

#include "SnakeDefines.h"

namespace SnakeGame
{
	class Logic;

	class Gfx
	{
	public:
		Gfx();

		void update(const Logic& logic);
		void render(DrawFunc draw);

	private:
		std::vector<sf::Texture> m_tex;
		GfxBoard m_board;

		sf::Font m_font;
		sf::Text m_infoLine1;
		sf::Text m_infoLine2;
	};
}