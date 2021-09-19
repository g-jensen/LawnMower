#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MapUnit.h"
#include <iostream>

class MapRenderer
{
public:
	void render(const std::vector<std::vector<MapUnit>> &map) const;
};

