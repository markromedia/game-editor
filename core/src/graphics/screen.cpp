//
//  screen.cpp
//  Flight
//
//  Created by Mark Udit on 9/9/14.
//
//

#include "screen.h"

Screen* Screen::_instance = NULL;

void Screen::Init(int width, int height)
{
    Screen::_instance = new Screen();
    Screen::_instance->width = width;
    Screen::_instance->height = height;
}

float Screen::Width()
{
    return Screen::_instance->width;
}

float Screen::Height()
{
    return Screen::_instance->height;
}