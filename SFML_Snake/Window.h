#pragma once

class Window final
{
public:
	Window(const std::string& title, const sf::Vector2u size);
	~Window();

	void handleEvents();
	void render();

	bool isActive() const;
	const sf::Vector2u& size() const;

	template<typename GameObject>
	void subscribe(GameObject* slot)
	{
		m_eventSignal.connect(boost::bind(&GameObject::handleEvent, slot, _1));
		m_renderSignal.connect(boost::bind(&GameObject::render, slot, _1));
	}


private:
	void toggleFullScreen();
	void handleEvent(sf::Event event);

	sf::RenderWindow m_window;
	std::string m_title;
	sf::Vector2u m_size;
	bool m_isActive{ true };
	bool m_isFullScreen{ false };

	boost::signals2::signal<void(sf::Event)> m_eventSignal;
	boost::signals2::signal<void(DrawFunc)> m_renderSignal;
};
