#include "stdafx.h"
#include "Window.h"

Window::Window(const std::string& title, const sf::Vector2u size) : m_title{ title }, m_size{ size } 
{
	m_window.create({m_size.x, m_size.y}, m_title);
}

Window::~Window()
{
	m_window.close();
	m_eventSignal.disconnect_all_slots();
	m_renderSignal.disconnect_all_slots();
}

void Window::handleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		handleEvent(event);
		m_eventSignal(event);
	}
}

void Window::render()
{
	m_window.clear();
	m_renderSignal([this](const sf::Drawable& drawable) {m_window.draw(drawable); });
	m_window.display();
}

bool Window::isActive() const
{
	return m_isActive;
}

const sf::Vector2u & Window::size() const
{
	return m_size;
}

void Window::handleEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:	m_isActive = false; break;
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::F5: toggleFullScreen(); break;
		}
		break;
	default: break;
	}
}

void Window::toggleFullScreen()
{
	m_isFullScreen = !m_isFullScreen;
	const auto& style = m_isFullScreen ? ::sf::Style::Fullscreen : sf::Style::Default;
	m_window.create({ m_size.x, m_size.y }, m_title, style);
}