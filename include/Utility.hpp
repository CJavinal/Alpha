#pragma once
#ifndef Utility_HPP_INCLUDED
#define Utility_HPP_INCLUDED
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
namespace sf {
	class Sprite;
	class Text;
}

std::string toString(sf::Keyboard::Key key); 

void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);

float			toDegree(float radian);
float			toRadian(float degree);

float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

#endif // Utility_HPP_INCLUDED
