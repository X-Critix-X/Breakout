
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H
#endif // BREAKOUT_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include <iostream>


class GameObject
{
 public:


  GameObject();
  ~GameObject();


bool initialiseSprite(sf::Texture &texture, std::string  filename);
sf::Sprite* getSprite();

bool initialiseText(sf::Font &font, std::string  filename);
sf::Text* getText();

bool is_visible;

bool isEmpty;


    private:
  sf::Sprite* sprite = nullptr;
  sf::Text* Text = nullptr;



};