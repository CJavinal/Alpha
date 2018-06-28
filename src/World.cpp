#include "World.hpp"
#include "SpriteNode.hpp"

#include <cstddef>
#include <cmath>

#include <algorithm>
#include <memory>

World::World(sf::RenderWindow& window, FontHolder& fonts)
	: mWindow(window)
	  , mWorldView(window.getDefaultView())
	  , mTextures()
	  , mFonts(fonts)
	  , mSceneGraph()
	  , mSceneLayers()
	  , mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	  , mSpawnPosition(mWorldView.getSize().x / 2.f,
						mWorldBounds.height - mWorldView.getSize().y / 2.f)
	  , mScrollSpeed(-50.f)
	  , mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the fontsview
	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures() {
	mTextures.load(Textures::Eagle,	"Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor,"Media/Textures/Raptor.png");
	mTextures.load(Textures::Avenger, "Media/Textures/Avenger.png");
	mTextures.load(Textures::Desert,"Media/Textures/Desert.png");

	mTextures.load(Textures::Bullet, "Media/Textures/Bullet.png");
	mTextures.load(Textures::Missile, "Media/Textures/Missile.png");

	mTextures.load(Textures::HealthRefill, "Media/Textures/HealthRefill.png");
	mTextures.load(Textures::MissileRefill, "Media/Textures/MissileRefill.png");
	mTextures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
	mTextures.load(Textures::FireRate, "Media/Textures/FireRate.png");	
}

void World::buildScene() {
	// Initialize the different layers
	for(std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);
	// Setting the background
	std::unique_ptr<SpriteNode> backgroundSprite(
			new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
	
	// Setting the playes Aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures,
				mFonts));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mSceneLayers[Air]->attachChild(std::move(leader));
	
	// Add enemy aircrafts
	addEnemies();
}

void World::addEnemies() {
	// Add enemies to the spawn point container
	addEnemy(Aircraft::Raptor,    0.f,  500.f);
	addEnemy(Aircraft::Raptor,    0.f, 1000.f);
	addEnemy(Aircraft::Raptor, +100.f, 1100.f);
	addEnemy(Aircraft::Raptor, -100.f, 1100.f);
	addEnemy(Aircraft::Avenger, -70.f, 1400.f);
	addEnemy(Aircraft::Avenger, -70.f, 1600.f);
	addEnemy(Aircraft::Avenger,  70.f, 1400.f);
	addEnemy(Aircraft::Avenger,  70.f, 1600.f);
	
	// Sort all enemies according to their y value, such that lower enemies are
	// checked first for spawning
	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), 
			[](SpawnPoint lhs, SpawnPoint rhs) {
				return lhs.y < rhs.y;
			});
}

void World::addEnemy(Aircraft::Type type, float relX, float relY) {
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

void World::adaptPlayerPosition() {
	// Keep player's position inside the screen bounds, at least borderDistance
	// units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
			mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity() {
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity to have always the same velocity
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}

void World::draw() {
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
	// Scroll the world, reset player velocity.
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adap velocity(scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

	// Remove all destroyed entities, create new ones
	spawnEnemies();

	// Regular update step, adapt position(correct if outside view)
	mSceneGraph.update(dt,mCommandQueue);
	adaptPlayerPosition();
	
}

CommandQueue& World::getCommandQueue() {
	return mCommandQueue;
}

void World::spawnEnemies() {
	while(!mEnemySpawnPoints.empty()
			&& mEnemySpawnPoints.back().y > getBattlefieldBounds().top) {
		SpawnPoint spawn = mEnemySpawnPoints.back();
		
		std::unique_ptr<Aircraft> enemy(
				new Aircraft(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);

		mSceneLayers[Air]->attachChild(std::move(enemy));
		
		mEnemySpawnPoints.pop_back();
	}
}

sf::FloatRect World::getViewBounds() const {
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
			mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const {
	// Return view bounds = same area at top, where enemies spawn
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}
