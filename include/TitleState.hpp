#ifndef TitleState_HPP_INCLUDED
#define TitleState_HPP_INCLUDED
#include "State.hpp"
#include "StateStack.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

class TitleState : public State {
	public:
							TitleState(StateStack& stack,
										Context context);
		
		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

	private:
		sf::Sprite			mBackgroundSprite;
		sf::Text			mText;

		bool				mShowText;
		sf::Time			mTextEffectTime;
};

#endif // TitleState_HPP_INCLUDED
