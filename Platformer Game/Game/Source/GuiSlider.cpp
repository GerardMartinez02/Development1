#include "GuiSlider.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "sceneIntro.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect sliderBounds, SDL_Texture* texture, SDL_Texture* sliderTexture) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->limitBounds = sliderBounds;
	this->texture = texture;
	this->textureForSlider = sliderTexture;
	//canClick = true;
	drawBasic = false;
}

GuiSlider::~GuiSlider()
{

}

bool GuiSlider::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		if (canClick == true)
		{
			int mouseX, mouseY;
			app->input->GetMousePosition(mouseX, mouseY);


			if ((mouseX > bounds.x && mouseX < (bounds.x + bounds.w)) &&
				(mouseY > bounds.y && mouseY < bounds.y + bounds.h))
			{
				state = GuiControlState::FOCUSED;
				//extraBounds.x = mouseX;
				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				{
					state = GuiControlState::PRESSED;
					limitBounds.x = limitBounds.x;
					//cout << "Pressed " << endl;
					//NotifyObserver();
				}
				else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::SELECTED;
					//cout << "Selected " << endl;
					limitBounds.x = mouseX;
					NotifyObserver();
				}
				else
				{
					state = GuiControlState::NORMAL;
					NotifyObserver();
				}
			}
		}
	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture(textureForSlider, limitBounds.x, limitBounds.y, NULL);
	} break;

	case GuiControlState::NORMAL:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture(textureForSlider, limitBounds.x, limitBounds.y, NULL);
	} break;

	//L14: TODO 4: Draw the button according the GuiControl State
	case GuiControlState::FOCUSED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture(textureForSlider, limitBounds.x, limitBounds.y, NULL);
	} break;
	case GuiControlState::PRESSED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture(textureForSlider, limitBounds.x, limitBounds.y, NULL);
	} break;

	/******/

	case GuiControlState::SELECTED:
	{
		render->DrawTexture(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture(textureForSlider, limitBounds.x, limitBounds.y, NULL);
	}break;
	default:
		break;
	}

	return false;
}