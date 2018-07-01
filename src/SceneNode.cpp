#include "SceneNode.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include <Utility.hpp>
#include <algorithm>
#include <cassert>


SceneNode::SceneNode(Category::Type category) :
	mChildren()
	,	mParent(nullptr)
	,	mDefaultCategory(category)
{
}

void SceneNode::attachChild(Ptr child) 
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) 
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
			[&](Ptr& p) -> bool { return p.get() == &node;});

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::removeWrecks() 
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(),
			std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	std::for_each(mChildren.begin(), mChildren.end(), 
			std::mem_fn(&SceneNode::removeWrecks));
}

sf::FloatRect SceneNode::getBoundingRect() const 
{
	return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const 
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool SceneNode::isDestroyed() const 
{
	// By default, scene node needn't be remove
	return false;
}



float distance(const SceneNode& lhs, const SceneNode& rhs) 
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}



void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	// apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const 
{
	// none for now
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states)
	const 
{
	for(const Ptr& child : mChildren)
		child->draw(target, states);
}


void SceneNode::update(sf::Time dt, CommandQueue& commands) 
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}
void SceneNode::updateCurrent(sf::Time, CommandQueue&) 
{
	// None for now
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands) 
{
	for(Ptr& child : mChildren) {
		child->update(dt,commands);
	}
}

sf::Transform SceneNode::getWorldTransform() const 
{
	sf::Transform transform = sf::Transform::Identity;
	for(const SceneNode* node = this;
			node != nullptr; node = node->mParent) {
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const 
{
	return getWorldTransform() * sf::Vector2f();
}

unsigned SceneNode::getCategory() const 
{
	return mDefaultCategory;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) 
{
	if(command.category & getCategory())
		command.action(*this, dt);

	for(Ptr& child : mChildren) 
		child->onCommand(command, dt);
}
