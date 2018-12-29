#include "stdafx.h"
#include "Snake.h"

#include "SnakeDefines.h"

namespace SnakeGame
{
	void Snake::handleEvent(sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up: 
				m_logic.requestDirectionChange(Logic::Direction::Up); 
				break;
			case sf::Keyboard::Down: 
				m_logic.requestDirectionChange(Logic::Direction::Down); 
				break;
			case sf::Keyboard::Left: 
				m_logic.requestDirectionChange(Logic::Direction::Left); 
				break;
			case sf::Keyboard::Right: 
				m_logic.requestDirectionChange(Logic::Direction::Right); 
				break;
			case sf::Keyboard::Space:
				m_logic.start();
				break;
			default: 
				break;
			}
		}
	}

	void Snake::update(sf::Time deltaTime)
	{
		m_elapsedTime += deltaTime;
		if (m_elapsedTime.asMilliseconds() > s_frameTime)
		{
			m_logic.update();
			m_gfx.update(m_logic.getBoard());

			m_elapsedTime -= sf::milliseconds(s_frameTime);
		}
	}

	void Snake::render(DrawFunc draw)
	{
		m_gfx.render(draw);
	}
}
