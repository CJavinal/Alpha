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
		explicit			World(sf::RenderWindow& window);
		void				update(sf::Time dt);
		void				draw();
		CommandQueue&		getCommandQueue();
	private:
		void				loadTextures();
		void				buildScene();
		void				adaptPlayerVelocity();
		void				adaptPlayerPosition();
	private:
		enum Layer {
			Background,
			Air,
			LayerCount
		};
	private:
		
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;
		Aircraft*							mPlayerAircraft;
};

#endif // World_HPP_INCLUDED
