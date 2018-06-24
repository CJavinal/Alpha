#ifndef Player_HPP_INCLUDED
#define Player_HPP_INCLUDED
#include "CommandQueue.hpp"

#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>


class Player {
	public:
							Player();
	public:
		enum Action {
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			ActionCount
		};

		void				assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key	getAssignedKey(Action action) const;

		void				handleEvent(const sf::Event& event,
										CommandQueue& commands);
		void				handleRealtimeInput(CommandQueue& commands);
	private:
		void				initializeActions();
		static bool			isRealtimeAction(Action action);

	private:
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
};

#endif // Player_HPP_INCLUDED
