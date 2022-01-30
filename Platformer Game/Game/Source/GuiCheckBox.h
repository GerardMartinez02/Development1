#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

    GuiCheckBox(uint32 id, SDL_Rect bounds);
    virtual ~GuiCheckBox();

    bool Update(float dt);
    bool Draw(Render* render);

    int mouseX, mouseY;
    unsigned int click;

    bool canClick = true;
    bool drawBasic = false;

private:

    bool checked;
};

#endif __GUICHECKBOX_H__
#pragma once
