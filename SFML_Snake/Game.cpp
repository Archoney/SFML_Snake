#include "stdafx.h"
#include "Game.h"

#include "SnakeDefines.h"

Game::Game(std::string windowTitle, sf::Vector2u windowSize) : m_window{ std::make_unique<Window>(windowTitle, windowSize) }
{
}

Game::~Game()
{
	m_updateSignal.disconnect_all_slots();
}

void Game::handleEvents()
{
	m_window->handleEvents();
}

void Game::update()
{
	m_elapsedTime = m_clock.getElapsedTime().asMilliseconds();
	if (m_elapsedTime > SnakeGame::s_frameTime)
	{
		m_updateSignal(sf::Time());
		m_elapsedTime -= SnakeGame::s_frameTime;
		render();
		m_clock.restart();
	}
}

void Game::render()
{
	m_window->render();
}

bool Game::isActive() const
{
	return m_window->isActive();
}
