#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(uint32 id, SDL_Rect bounds, const char* text);
    virtual ~GuiSlider();

    bool Update(Input* input, float dt);
    bool Draw(Render* render);
    bool DrawDebug(Render* render);

    SDL_Rect slider;
    int value;

    int minValue = 0;
    int maxValue = 100;

private:

    // GuiSlider specific properties
    // Maybe some animation properties for state change?

};

#endif // __GUISLIDER_H__
#pragma once
