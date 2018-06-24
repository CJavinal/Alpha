#pragma once
#ifndef MenuState_HPP_INCLUDED
#define MenuState_HPP_INCLUDED
#include <State.hpp>
#include <GUI/Container.hpp>

#include <cstddef>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);
	
	private:
		sf::Sprite				mBackgroundSprite;
		GUI::Container			mGUIContainer;
};

#endif // MenuState_HPP_INCLUDED
