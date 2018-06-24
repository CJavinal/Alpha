#pragma once
#ifndef SettingsState_HPP_INCLUDED
#define SettingsState_HPP_INCLUDED
#include <State.hpp>
#include <GUI/Button.hpp>
#include <GUI/Container.hpp>
#include <GUI/Label.hpp>
#include <Player.hpp>

#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class SettingsState : public State {
	public:
							SettingsState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

	private:
		void				updateLabels();
		void				addButtonLabel(Player::Action, float y,
								const std::string& text, Context context);
	
	private:
		sf::Sprite											mBackgroundSprite;
		GUI::Container										mGUIContainer;
		std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount>	mBindingLabels;
		

};

#endif // SettingsState_HPP_INCLUDED
