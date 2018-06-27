#include <Aircraft.hpp>
#include <DataTables.hpp>
#include <ResourceIdentifiers.hpp>
#include <Utility.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(Aircraft::Type type) {
	switch(type) {
		case Aircraft::Eagle:
			return Textures::Eagle;
		case Aircraft::Raptor:
			return Textures::Raptor;
		case Aircraft::Avenger:
			return Textures::Avenger;
		default:
			return Textures::Eagle;
	}
}

namespace {
	const std::vector<AircraftData> Table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, 
		const FontHolder& fonts) : 
	Entity(10)
	,	mType(type)
	,	mSprite(textures.get(toTextureID(type)))
{
	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));
	centerOrigin(mSprite);
}


void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) 
		const {
	target.draw(mSprite, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands) {
	mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());
	Entity::updateCurrent(dt, commands);
}

unsigned Aircraft::getCategory() const {
	switch(mType) {
		case Eagle:
			return Category::PlayerAircraft;
		default:
			return Category::EnemyAircraft;
	}
}
