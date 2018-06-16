#ifndef SceneNode_HPP_INCLUDED
#define SceneNode_HPP_INCLUDED
#include "Category.hpp"
#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

struct Command;

class SceneNode :	public sf::Transformable, public sf::Drawable,
					private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
	public:
							SceneNode();

		void				attachChild(Ptr child);
		Ptr					detachChild(const SceneNode& node);

		void				update(sf::Time dt);

		sf::Transform		getWorldTransform() const;
		sf::Vector2f		getWorldPosition() const;

		virtual unsigned	getCategory() const;
		void				onCommand(const Command& command, sf::Time dt);
	private:
		virtual void		updateCurrent(sf::Time dt);
		void				updateChildren(sf::Time dt);
		virtual void		draw(sf::RenderTarget& target,
										sf::RenderStates states) const;
		virtual void		drawCurrent(sf::RenderTarget& target,
										sf::RenderStates states) const;
		void				drawChildren(sf::RenderTarget& target,
										sf::RenderStates states) const;
	private:
		std::vector<Ptr>	mChildren;
		SceneNode*			mParent;
};


#endif // SceneNode_HPP_INCLUDED
