#pragma once
#ifndef GUI_Container_HPP_INCLUDED
#define GUI_Container_HPP_INCLUDED
#include <GUI/Component.hpp>

#include <vector>

namespace GUI {
	class Container : public Component {
		public:
			typedef std::shared_ptr<Container> Ptr;
		public:
									Container();

			void					pack(Component::Ptr component);

			virtual bool			isSelectable() const;
			virtual void			handleEvent(const sf::Event& event);
		
		private:
			virtual void			draw(sf::RenderTarget& target,
											sf::RenderStates states) const;

			void					select(std::size_t index);
			void					selectNext();
			void					selectPrevious();
			bool					hasSelection() const;

		private:
			std::vector<Component::Ptr>		mChildren;
			int								mSelectedChild;
	};
}


#endif	// GUI_Container_HPP_INCLUDED 
