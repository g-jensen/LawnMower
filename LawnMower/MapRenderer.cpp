#include "MapRenderer.h"

void MapRenderer::render(const std::vector<std::vector<MapUnit>>&map) const
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Lawn Mower");

    sf::Vector2i previousMousePosition = sf::Vector2i(window.getView().getCenter().x, window.getView().getCenter().y);

    window.setFramerateLimit(60);

	while (window.isOpen()) {
        window.setFramerateLimit(15);
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
                window.setView(sf::View(visibleArea));
            }

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.mouseWheelScroll.delta <= -1) {
                sf::View view = window.getView();
                view.zoom(1.1);
                window.setView(view);
            }
            if (event.mouseWheelScroll.delta >= 1) {
                sf::View view = window.getView();
                view.zoom(0.9);
                window.setView(view);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::View view = window.getView();
            view.move(0,-50);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::View view = window.getView();
            view.move(0, 50);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sf::View view = window.getView();
            view.move(-50, 0);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sf::View view = window.getView();
            view.move(50, 0);
            window.setView(view);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < map.size(); i++) {
            for (int k = 0; k < map[i].size(); k++) {
                MapUnit unit = map[i][k];
                sf::RectangleShape rec;
                int size = 40;
                rec.setPosition(unit.position.x* size, unit.position.y* size);
                rec.setSize(sf::Vector2f(size, size));
                if (unit.state == MapUnitState::BORDER) {
                    rec.setFillColor(sf::Color::Red);
                }
                else if (unit.state == MapUnitState::LONG_GRASS) {
                    rec.setFillColor(sf::Color::Green);
                }
                window.draw(rec);
            }
        }


        // end the current frame
        window.display();
	}

}
