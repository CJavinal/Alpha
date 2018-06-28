#include <Aircraft.hpp>
#include <DataTables.hpp>
#include <ResourceIdentifiers.hpp>
#include <Utility.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

Textures::ID toTextureID(Aircraft::Type type) {
	switch(type) {
		case Aircraft::Eagle:
			return Textures::Eagle;
		case Aircraft::Raptor:
			return Textures::Raptor;
		case Aircraft::Avenger:
			return Textures::Avenger;
		default:
			return Textures::Avenger;
	}
}

namespace {
	const std::vector<AircraftData> Table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, 
		const FontHolder& fonts) : 
	Entity(Table[type].hitpoints)
	,	mType(type)
	,	mSprite(textures.get(toTextureID(type)))
	,	mTravelledDistance(0.f)
	,	mDirectionIndex(0)
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
	
	
	//update enemy movement pattern, apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	// Update Texts
	updateTexts();
}

void Aircraft::updateMovementPattern(sf::Time dt) {
	const std::vector<Direction>& directions = Table[mType].directions;
	if(!directions.empty()) {
		float distanceToTravel = directions[mDirectionIndex].distance;
		if (mTravelledDistance > distanceToTravel) {
			mDirectionIndex = (mDirectionIndex + 1) % directions.size();
			mTravelledDistance = 0.f;
		}
		float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);
		setVelocity(vx, vy);
		mTravelledDistance += getMaxSpeed() * dt.asSeconds();

	}
}

float Aircraft::getMaxSpeed() const {
	return Table[mType].speed;
}

unsigned Aircraft::getCategory() const {
	switch(mType) {
		case Eagle:
			return Category::PlayerAircraft;
		default:
			return Category::EnemyAircraft;
	}
}

void Aircraft::updateTexts() {
	mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());
}
