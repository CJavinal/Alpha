#pragma once
#ifndef ResourceIdentifiers_HPP_INCLUDED
#define ResourceIdentifiers_HPP_INCLUDED

// Forward declaration of SFML classes
namespace sf {
	class Texture;
	class Font;
}

namespace Textures {
	enum ID {
		Eagle,
		Raptor,
		Avenger,
		Bullet,
		Missile,
		Desert,
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
	};
}

namespace Fonts {
	enum ID {
		Main,
	};
}

// Forward declartion and a few type definitions
template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif // ResourceIdentifiers_HPP_INCLUDED
