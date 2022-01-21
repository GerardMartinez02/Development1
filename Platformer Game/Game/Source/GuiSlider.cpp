#include "GuiSlider.h"
#include "App.h"
#include "GuiManager.h"
#include "Audio.h"
#include "Window.h"
#include "Render.h"
#include "Input.h"
#include "SceneIntro.h"


GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* texture) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = texture;
    slider.x = bounds.x;
    slider.y = bounds.y;
    slider.w = 20;
    slider.h = bounds.h;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(Input* input, float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        input->GetMousePosition(mouseX, mouseY);

        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
                int posX;
                int posY;
                input->GetMousePosition(posX, posY);
                slider.x = posX;
            }

            if (slider.x < bounds.x)
            {
                slider.x = bounds.x;
            }

            if (slider.x + slider.w >= bounds.x + bounds.w)
            {
                slider.x = bounds.x + bounds.w - slider.w;
            }

            float percent = (100.0f / bounds.w) * (slider.x - bounds.x);
            percent = percent / 100.0f;
            value = maxValue * percent;

            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }
    return false;
}

bool GuiSlider::DrawDebug(Render* render)
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED:
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle(bounds, 0, 255, 0, 100);
        }
        break;
    case GuiControlState::NORMAL:
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle(bounds, 255, 255, 0, 100);
        }
        break;
    case GuiControlState::FOCUSED:
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle(bounds, 0, 255, 255, 100);
        }
        break;
    case GuiControlState::PRESSED:
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle(bounds, 0, 255, 0, 100);
        }
        break;
    default:
        break;
    }
    return false;
}

bool GuiSlider::Draw(Render* render)
{
    switch (state)
    {
    case GuiControlState::NORMAL:
    {
        render->DrawTexture(this->texture, this->slider.x, this->slider.y, &this->anim.frames[0], 0.0f);
        break;
    }
    case GuiControlState::FOCUSED:
    {
        render->DrawTexture(this->texture, this->slider.x, this->slider.y, &this->anim.frames[1], 0.0f);
        break;
    }
    case GuiControlState::PRESSED:
    {
        render->DrawTexture(this->texture, this->slider.x, this->slider.y, &this->anim.frames[2], 0.0f);
        break;
    }
    default:
        break;
    }
    return false;
}
