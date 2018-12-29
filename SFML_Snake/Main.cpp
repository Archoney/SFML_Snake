#include "stdafx.h"
#include "Game.h"
#include "Snake.h"
#include "SnakeDefines.h"

int main(int argc, char** argv[])
{
	auto game = std::make_unique<Game>("Snake!", SnakeGame::s_resolution);
	auto snake = std::make_unique<SnakeGame::Snake>();
	game->subscribe(snake.get());
	
	while (game->isActive())
	{
		game->handleEvents();
		game->update();
	}

	return 0;
}