#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect sliderBounds, SDL_Texture* texture, SDL_Texture* sliderTexture);
    virtual ~GuiSlider();

    bool Update(float dt);
    bool Draw(Render* render);
    
    SDL_Rect slider;
    int value;

    int minValue = 0;
    int maxValue = 100;

    int mouseX, mouseY;
    unsigned int click;

    bool canClick = true;
    bool drawBasic = false;
private:

    // GuiSlider specific properties
    // Maybe some animation properties for state change?

};

#endif // __GUISLIDER_H__
#pragma once
