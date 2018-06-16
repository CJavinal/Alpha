#ifndef Command_HPP_INCLUDED
#define Command_HPP_INCLUDED
#include "Category.hpp"
#include "SceneNode.hpp"
#include <functional>

#include <SFML/System/Time.hpp>


struct Command {
	Command();
	std::function<void(SceneNode&, sf::Time)>		action;
	unsigned int									category;
};

template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
	return [=] (SceneNode& node, sf::Time dt) {
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}


#endif // Command_HPP_INCLUDED
