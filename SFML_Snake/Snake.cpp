#include "stdafx.h"
#include "Snake.h"

namespace SnakeGame
{
	void Snake::handleEvent(sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up: m_logic.requestDirectionChange(Logic::Direction::Up); break;
			case sf::Keyboard::Down: m_logic.requestDirectionChange(Logic::Direction::Down); break;
			case sf::Keyboard::Left: m_logic.requestDirectionChange(Logic::Direction::Left); break;
			case sf::Keyboard::Right: m_logic.requestDirectionChange(Logic::Direction::Right); break;
			default: break;
			}
		}
	}

	void Snake::update(sf::Time deltaTime)
	{
		if (m_logic.isGameOver())
		{
			sf::sleep(sf::milliseconds(2000));
			m_logic.reset();
		}

		m_logic.update();
		m_gfx.update(m_logic.getBoard());
	}

	void Snake::render(DrawFunc draw)
	{
		m_gfx.render(draw);
	}
}
