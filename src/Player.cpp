#include "Aircraft.hpp"
#include "Player.hpp"
#include "SceneNode.hpp"

#include <cassert>
#include <functional>
#include <iostream>


struct AircraftMover {
	AircraftMover(float vx, float vy)
		: velocity(vx, vy) 
	{
	}

	void operator() (Aircraft& aircraft, sf::Time dt) const {
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player() {
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for(auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}
void Player::handleRealtimeInput(CommandQueue& commands) {
	// Traversed all assigned keys and check if they are pressed
	for(auto pair : mKeyBinding) {
		if (sf::Keyboard::isKeyPressed(pair.first)
				&& isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
	// Remove all keys that alread map to action
	for(auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();) {
		if(itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}
	// Insert new binding 
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
	for(auto pair : mKeyBinding) {
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions() {
	const float playerSpeed = 200.f;
	
	mActionBinding[MoveLeft].action		= derivedAction<Aircraft>(
			AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action	= derivedAction<Aircraft>(
			AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action		= derivedAction<Aircraft>(
			AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action		= derivedAction<Aircraft>(
			AircraftMover(0.f, +playerSpeed));
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	if(event.type == sf::Event::KeyPressed) {
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

bool Player::isRealtimeAction(Action action) {
	switch(action) {
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;
		default:
			return false;
	}
}
