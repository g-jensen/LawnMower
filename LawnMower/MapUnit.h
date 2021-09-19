#pragma once

#include <SFML/System/Vector2.hpp>

enum class MapUnitState {
	BORDER,
	LONG_GRASS,
	CUT_GRASS
};

class MapUnit
{
public:
	sf::Vector2i position;
	MapUnitState state;
	MapUnit(sf::Vector2i position, MapUnitState state);
};

