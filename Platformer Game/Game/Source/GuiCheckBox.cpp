#include "GuiCheckBox.h"
#include "App.h"
#include "Input.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
    this->checked = false;
    this->id = id;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                checked = !checked;
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }
    return false;
}

bool GuiCheckBox::DrawDebug()
{
    switch (state)
    {
    case GuiControlState::NORMAL:
    {
        if (app->render->guiDebug)
        {
            if (checked)
            {
                app->render->DrawRectangle(bounds, 0, 255, 0, 255);
            }
            else
            {
                app->render->DrawRectangle(bounds, 0, 255, 0, 150);
            }
        }
        break;
    }

    case GuiControlState::FOCUSED:
    {
        if (app->render->guiDebug)
        {
            if (checked)
            {
                app->render->DrawRectangle(bounds, 255, 255, 0, 255);
            }
            else
            {
                app->render->DrawRectangle(bounds, 250, 250, 210, 255);
            }
        }
        break;
    }

    case GuiControlState::PRESSED:
    {
        if (app->render->guiDebug)
        {
            if (checked)
            {
                app->render->DrawRectangle(bounds, 255, 0, 0, 255);
            }
            else
            {
                app->render->DrawRectangle(bounds, 255, 0, 0, 150);
            }
        }
        break;
    }
    default:
        break;
    }
    return false;
}

bool GuiCheckBox::DrawTexture()
{
    switch (state)
    {
    case GuiControlState::NORMAL:
    {
        if (checked)
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[0]);
        }
        else
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[1]);
        }
        break;
    }
    case GuiControlState::FOCUSED:
    {
        if (checked)
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[2]);
        }
        else
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[3]);
        }
        break;
    }
    case GuiControlState::PRESSED:
    {
        if (checked)
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[4]);
        }
        else
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[5]);
        }
        break;
    }
    }
    return true;
}
