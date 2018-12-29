#pragma once

#include "SnakeLogic.h"
#include "SnakeGfx.h"

namespace SnakeGame
{
	class Snake
	{
	public:
		void handleEvent(sf::Event event);
		void update(sf::Time deltaTime);
		void render(DrawFunc draw);

	private:
		Logic m_logic;
		Gfx m_gfx;
	};
}