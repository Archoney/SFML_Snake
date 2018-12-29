#pragma once

#include "SnakeDefines.h"

namespace SnakeGame
{
	class Gfx
	{
	public:
		Gfx();

		void update(const LogicBoard& logicBoard);
		void render(DrawFunc draw);

	private:
		std::vector<sf::Texture> m_tex;
		GfxBoard m_board;
	};
}