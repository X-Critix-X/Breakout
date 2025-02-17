//
// Created by micro on 09/02/2024.
//
#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>


bool Block::isVisible() const
{
  return is_visible;
}

void Block::setIsVisible(bool isVisible)
{
  is_visible = isVisible;
}



