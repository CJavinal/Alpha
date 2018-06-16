#pragma once
#ifndef Entity_HPP_INCLUDED
#define Entity_HPP_INCLUDED
#include "SceneNode.hpp"
#include <SFML/System/Vector2.hpp>



class Entity: public SceneNode {
	public:
		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		void			accelerate(sf::Vector2f velocity);
		void			accelerate(float vx, float vy);
		sf::Vector2f	getVelocity() const;
	private:
		virtual void	updateCurrent(sf::Time dt);
	private:
		sf::Vector2f	mVelocity;
};

#endif // Entity_HPP_INCLUDED
