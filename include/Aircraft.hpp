#pragma once
#ifndef Aircraft_HPP_INCLUDED
#define Aircraft_HPP_INCLUDED
#include <Entity.hpp>
#include <ResourceHolder.hpp>
#include <TextNode.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Aircraft : public Entity {
	public:
		enum Type {
			Eagle,
			Raptor,
			Avenger,
			TypeCount
		};
	public:
							Aircraft(Type type, const TextureHolder& textures,
									const FontHolder& fonts);
							
		virtual void		drawCurrent(sf::RenderTarget& target,
										sf::RenderStates states) const;
		virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
		void				updateMovementPattern(sf::Time dt);
		virtual unsigned	getCategory() const;

	private:
		float				getMaxSpeed() const;
		void				updateTexts();

	
	private:
		Type				mType;
		sf::Sprite			mSprite;
		TextNode*			mHealthDisplay;

		float				mTravelledDistance;
		unsigned			mDirectionIndex;
};

#endif // Aircraft_HPP_INCLUDED
