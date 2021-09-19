#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "FileExplorer.h"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    int width = 100;
    int height = 100;
    int brushSize = 5;
    int size = 50;

    std::vector<std::vector<sf::RectangleShape>> map;

    for (int i = 0; i < height; i++) {
        std::vector<sf::RectangleShape> row;
        for (int k = 0; k < width; k++) {
            sf::RectangleShape rec;
            rec.setFillColor(sf::Color::Red);
            rec.setPosition(k*size,i*size);
            rec.setSize(sf::Vector2f(size,size));
            row.push_back(rec);
        }
        map.push_back(row);
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
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

            
            if (event.type == event.TextEntered) {
                std::cout << event.text.unicode << std::endl;
                if (event.text.unicode == 19) {
                    std::ofstream myfile;
                    myfile.open("map.txt");
                    for (int i = 0; i < map.size(); i++) {
                        for (int k = 0; k < map[i].size(); k++) {
                            if (map[i][k].getFillColor() == sf::Color::Green) {
                                myfile << "1";
                            }
                            else {
                                myfile << "0";
                            }
                        }
                        myfile << "\n";
                    }
                    myfile.close();
                }
                if (event.text.unicode >= 49 && event.text.unicode < 57) {
                    brushSize = (char)event.text.unicode - '0';
                }
                if ((char)event.text.unicode == 'f') {
                    map.clear();
                    std::ifstream file(FileExplorer::Open());
                    std::string output;
                    int i = 0;
                    if (file.is_open()) {
                        while (getline(file, output))
                        {
                            std::cout << output << std::endl;
                            std::vector<sf::RectangleShape> row;
                            for (int k = 0; k < output.size(); k++) {
                                sf::RectangleShape rec;
                                rec.setSize(sf::Vector2f(size, size));
                                rec.setPosition(k*size,i*size);
                                if (stoi(std::string(1, output[k])) == 0) {
                                    rec.setFillColor(sf::Color::Red);
                                }
                                else {
                                    rec.setFillColor(sf::Color::Green);
                                }
                                row.push_back(rec);
                            }
                            i++;
                            map.push_back(row);
                        }
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::View view = window.getView();
            view.move(0, -50);
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int i = 0; i < map.size(); i++) {
                for (int k = 0; k < map[i].size(); k++) {
                    if (map[i][k].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y)) {
                        for (int s = 0; s < brushSize; s++) {
                            for (int s2 = 0; s2 < brushSize; s2++) {
                                if (i + s <= map.size() - 1 && k + s2 <= map[i].size() - 1) {
                                    map[i + s][k + s2].setFillColor(sf::Color::Green);

                                }
                            }
                        }
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            for (int i = 0; i < map.size(); i++) {
                for (int k = 0; k < map[i].size(); k++) {
                    if (map[i][k].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y)) {
                        for (int s = 0; s < brushSize; s++) {
                            for (int s2 = 0; s2 < brushSize; s2++) {
                                map[i + s][k + s2].setFillColor(sf::Color::Red);
                            }
                        }
                    }
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < map.size(); i++) {
            for (int k = 0; k < map[i].size(); k++) {
                window.draw(map[i][k]);
            }
        }

        // end the current frame
        window.display();
    }

    
    

    return 0;
}