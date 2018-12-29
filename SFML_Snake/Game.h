#pragma once

#include "Window.h"

class Game final
{
public:
	Game(std::string windowTitle, sf::Vector2u windowSize);
	~Game();

	void handleEvents();
	void update();
	void render();
	bool isActive() const;

	template<typename GameObject>
	void subscribe(GameObject* slot)
	{
		m_updateSignal.connect(boost::bind(&GameObject::update, slot, _1));
		m_window->subscribe(slot);
	}

private:
	sf::Clock m_clock;
	sf::Int32 m_elapsedTime;
	std::unique_ptr<Window> m_window;
	boost::signals2::signal<void(sf::Time)> m_updateSignal;
};