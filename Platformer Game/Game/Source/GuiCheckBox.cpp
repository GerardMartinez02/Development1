#include "GuiCheckbox.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	
	canClick = true;
	drawBasic = false;

}

GuiCheckBox::~GuiCheckBox()
{

}

bool GuiCheckBox::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3_D: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x && mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y && mouseY < bounds.y + bounds.h))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				state = GuiControlState::PRESSED;
				//cout << "Pressed " << endl;
				NotifyObserver();
			}
			else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::SELECTED;
				//cout << "Selected " << endl;
				//NotifyObserver();
			}
			else
			{
				state = GuiControlState::NORMAL;
			}
		}

	}

	return false;
}

bool GuiCheckBox::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
	} break;

	case GuiControlState::NORMAL:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);

	} break;
	case GuiControlState::FOCUSED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
	} break;
	case GuiControlState::PRESSED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
	} break;

	/******/

	case GuiControlState::SELECTED:render->DrawTexture(texture, bounds.x, bounds.y, NULL);
		break;

	default:
		break;
	}

	return false;
}
