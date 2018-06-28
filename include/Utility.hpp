#pragma once
#ifndef Utility_HPP_INCLUDED
#define Utility_HPP_INCLUDED
#include <string>
#include <SFML/Window/Keyboard.hpp>
namespace sf {
	class Sprite;
	class Text;
}

std::string toString(sf::Keyboard::Key key); 

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float toDegree(float radian);
float toRadian(float degree);

#endif // Utility_HPP_INCLUDED
