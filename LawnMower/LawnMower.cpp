#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "MapUnit.h"
#include "MapRenderer.h"

int main() {
	std::vector<std::vector<MapUnit>> map;
	std::ifstream file("map.txt");
	std::string output;
	int i = 0;
	if (file.is_open()) {
		while (getline(file, output))
		{
			std::cout << output << std::endl;
			std::vector<MapUnit> row;
			for (int k = 0; k < output.size(); k++) {
				row.push_back(MapUnit(sf::Vector2i(k,i),(MapUnitState)stoi(std::string(1, output[k]))));
			}
			i++;
			map.push_back(row);
		}
	}

	MapRenderer renderer;
	renderer.render(map);

}