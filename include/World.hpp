#pragma once
#ifndef World_HPP_INCLUDED
#define World_HPP_INCLUDED
#include "Aircraft.hpp"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"

#include <array>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class World : private sf::NonCopyable {
	public:
		explicit			World(sf::RenderWindow& window, FontHolder& fonts);
		void				update(sf::Time dt);
		void				draw();
		CommandQueue&		getCommandQueue();
	private:
		void				loadTextures();
		void				adaptPlayerVelocity();
		void				adaptPlayerPosition();

		void				buildScene();
		void				addEnemies();
		void				addEnemy(Aircraft::Type type, float relX, float relY);

		void				spawnEnemies();
		sf::FloatRect		getViewBounds() const;
		sf::FloatRect		getBattlefieldBounds() const;
	private:
		enum Layer {
			Background,
			Air,
			LayerCount
		};
		struct SpawnPoint {
			SpawnPoint(Aircraft::Type type, float x, float y) 
				: type(type), x(x), y(y) { }
			Aircraft::Type	type;
			float			x;
			float			y;
		};
	private:
		
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		FontHolder&							mFonts;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;
		Aircraft*							mPlayerAircraft;

		std::vector<SpawnPoint>				mEnemySpawnPoints;
};

#endif // World_HPP_INCLUDED
