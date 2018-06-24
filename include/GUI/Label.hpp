#pragma once
#ifndef GUI_Label_HPP_INCLUDED
#define GUI_Label_HPP_INCLUDED
#include <GUI/Component.hpp>
#include <ResourceHolder.hpp>

#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI {
	class Label : public Component {
		public:
			typedef std::shared_ptr<Label> Ptr;


		public:
									Label(const std::string& text,
											const FontHolder& fonts);
			virtual bool			isSelectable() const;
			void					setText(const std::string& text);

			virtual void			handleEvent(const sf::Event& event);

		private:
			void					draw(sf::RenderTarget& target, 
											 sf::RenderStates states) const;

		private:
			sf::Text				mText;
	};
};


#endif // GUI_Label_HPP_INCLUDED
