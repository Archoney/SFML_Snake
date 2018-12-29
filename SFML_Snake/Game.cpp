#include "stdafx.h"
#include "Game.h"

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
	m_updateSignal(m_clock.restart());
}

void Game::render()
{
	m_window->render();
}

bool Game::isActive() const
{
	return m_window->isActive();
}
