#pragma once
#ifndef SpriteNode_HPP_INCLUDED
#define SpriteNode_HPP_INCLUDED
#include "SceneNode.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteNode : public SceneNode {
	public:
		explicit		SpriteNode(const sf::Texture& texture);
						SpriteNode(const sf::Texture& texture,
									const sf::IntRect& rect);

	private:
		virtual void	drawCurrent(sf::RenderTarget& target,
									sf::RenderStates states) const;
	
	private:
		sf::Sprite		mSprite;
};


#endif // SpriteNode_HPP_INCLUDED
