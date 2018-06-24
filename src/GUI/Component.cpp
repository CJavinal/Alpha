#include <GUI/Component.hpp>

namespace GUI {
	Component::Component() : mIsSelected(false)
			, mIsActive(false) {
	}

	Component::~Component(){ }

	bool Component::isSelected() const { return mIsSelected; }

	void Component::select() { if(isSelectable()) mIsSelected = true; }

	void Component::deselect() { mIsSelected = false; }

	bool Component::isActive() const { return mIsActive; }

	void Component::deactivate() { mIsActive = false; }

	void Component::activate() { mIsActive = true; }

}
