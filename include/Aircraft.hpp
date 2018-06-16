#ifndef Aircraft_HPP_INCLUDED
#define Aircraft_HPP_INCLUDED
#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/Sprite.hpp>


class Aircraft : public Entity {
	public:
		enum Type {
			Eagle,
			Raptor,
		};
	public:
							Aircraft(Type type, const TextureHolder& textures);
		virtual unsigned	getCategory() const;
	private:
		void				drawCurrent(sf::RenderTarget& target,
										sf::RenderStates states) const;
	
	private:
		Type				mType;
		sf::Sprite			mSprite;
};

#endif // Aircraft_HPP_INCLUDED
