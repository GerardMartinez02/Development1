#include "GuiButton.h"
#include "Input.h"
#include "App.h"
#include "Render.h"
GuiButton::GuiButton(uint32 id, SDL_Rect bounds, SDL_Texture* text) : GuiControl(GuiControlType::BUTTON, id)
{
    this->id = id;
    this->bounds = bounds;
    this->texture = text;
}

GuiButton::~GuiButton()
{
}

bool GuiButton::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            if (state == GuiControlState::NORMAL)
            {
                //app->audio->PlayFx(MouseOver){
            }
            if (state != GuiControlState::PRESSED)
            {
                state = GuiControlState::FOCUSED;
            }
            else
            {
                //app->audio->PlayFx(Pressed)
            }

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiButton::Draw(Render* render)
{
    switch (state)
    {
    case GuiControlState::DISABLED:
        break;
    case GuiControlState::NORMAL:
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle(bounds, 0, 255, 0, 100);
        }
        break;
    case GuiControlState::FOCUSED:
        // app->render->DrawTexture(texture, bounds.x, bounds.y, &SDL_Rect({ 0,0,9,7 }));
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle(bounds, 255, 255, 0, 100);
        }
        break;
    case GuiControlState::PRESSED:
        // app->render->DrawTexture(texture, bounds.x, bounds.y, &SDL_Rect({ 9,0,9,7 }));
        break;
    case GuiControlState::SELECTED:
        app->render->DrawTexture(texture, bounds.x, bounds.y, &SDL_Rect({ 9,0,9,7 }));
        break;
    default:
        break;
    }

    return true;
}
