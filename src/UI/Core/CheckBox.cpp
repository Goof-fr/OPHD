// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/**
 * ===========================================================
 * = NOTES ABOUT DECISIONS MADE
 * ===========================================================
 * = You'll note that I opted to define get/set type functions
 * = within the source file of the CheckBox class definition
 * = instead of in the header file -- this is an attempt to
 * = separate implementation details from interface details. I
 * = know, there are perhaps better ways to do this (pImpl
 * = for instance), but this makes it a bit simpler and makes
 * = the class header file a quicker read.
 * ===========================================================
 */

#include "CheckBox.h"

#include"../../Constants.h"
#include "../../FontManager.h"

#include "NAS2D/Utility.h"
#include "NAS2D/Renderer/Renderer.h"
#include "NAS2D/MathUtils.h"

#include <algorithm>


using namespace NAS2D;

static Font* CBOX_FONT = nullptr;

/**
 * C'tor
 */
CheckBox::CheckBox() : mSkin("ui/skin/checkbox.png")
{
	CBOX_FONT = Utility<FontManager>::get().font(constants::FONT_PRIMARY, constants::FONT_PRIMARY_NORMAL);
	Utility<EventHandler>::get().mouseButtonDown().connect(this, &CheckBox::onMouseDown);
}


/**
 * D'tor
 */
CheckBox::~CheckBox()
{
	Utility<EventHandler>::get().mouseButtonDown().disconnect(this, &CheckBox::onMouseDown);
}


/**
 * Sets checked state.
 * 
 * \note	Setting check state with this method will not fire
 *			a clicked event.
 */
void CheckBox::checked(bool toggle)
{
	mChecked = toggle;
}


/**
 * 
 */
bool CheckBox::checked() const
{
	return mChecked;
}


/**
 * 
 */
CheckBox::ClickCallback& CheckBox::click()
{
	return mCallback;
}


/**
 * 
 */
void CheckBox::onMouseDown(EventHandler::MouseButton button, int x, int y)
{
	if (!enabled() || !visible() || !hasFocus()) { return; }
	
	if (button == EventHandler::MouseButton::BUTTON_LEFT && isPointInRect(x, y,
        static_cast<int>(rect().x()),
        static_cast<int>(rect().y()),
        static_cast<int>(rect().width()),
        static_cast<int>(rect().height())))
	{
		mChecked = !mChecked;
		mCallback();
	}
}


/**
 * 
 */
void CheckBox::onTextChanged()
{
	width(16.0f + CBOX_FONT->width(text()));
}


/**
 * Enforces minimum and maximum sizes.
 */
void CheckBox::onSizeChanged()
{
	mRect.height(std::clamp(height(), 13.0f, 13.0f));
	if (width() < 13.0f) { mRect.width(13.0f); }
}


/**
 * 
 */
void CheckBox::update()
{
	Renderer& r = Utility<Renderer>::get();

	r.drawSubImage(mSkin, positionX(), positionY(), mChecked ? 13.0f : 0.0f, 0.0f, 13.0f, 13.0f);
	r.drawText(*CBOX_FONT, text(), positionX() + 20.0f, positionY(), 255, 255, 255);
}
