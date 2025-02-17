//
// Created by micro on 12/02/2024.
//

#ifndef BREAKOUTSFML_BLOCK_H
#define BREAKOUTSFML_BLOCK_H
#include <SFML/Graphics.hpp>


class Block
{



 public:
  Block();
  enum Colour {Red, Blue, Green};
  sf::Sprite sprite;


  void addTexture(sf::Texture& texture, Colour col);


 private:
  Colour colour;


};

#endif // BREAKOUTSFML_BLOCK_H
