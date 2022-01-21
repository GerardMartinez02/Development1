#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

    GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text);
    virtual ~GuiCheckBox();

    bool Update(float dt);
    bool DrawDebug();
    bool DrawTexture();

private:

    bool checked;
};

#endif __GUICHECKBOX_H__
#pragma once
