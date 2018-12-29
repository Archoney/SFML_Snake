#pragma once

// SFML
#include <SFML\Graphics.hpp>

// Boost
#include <boost\signals2.hpp>

// STD
#include <algorithm>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include <random>
#include <set>
#include <string>
#include <sstream>

// Type alliases
using DrawFunc = std::function<void(const sf::Drawable&)>;