
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include "GameObject.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include "Block.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void reset();
  bool collisionCheck(sf::Sprite* sprite1, sf::Sprite* sprite2);


 private:
  sf::RenderWindow& window;
  GameObject ball;
  sf::Texture ball_texture;
  GameObject paddle;
  sf::Texture paddle_texture;



  GameObject block [17][18];
  int rows = 17;
  int columns = 18;
  sf::Texture block_texture;



  sf::Font font;


  GameObject menu_text;

  //vector
  Vector2 ballDirection;


  bool play_selected = false;
  bool playagain_selected = false;
  GameObject play_option;
  GameObject play_again;
  GameObject quit_option;
  //GameObject score_text;
  GameObject final_score;
  GameObject your_score;
  GameObject lives_text;
  GameObject game_over_text;
  GameObject game_win_text;
  int game_state = 0;
  /*
   * 0 = menu
   * 1 = playing
   * 2 = game over
   */
  sf::Font font1;
  GameObject lives;
  int numlives = 5;
  GameObject score;
  int Score = 0;
  int fScore = 0;

  float paddleSpeed = 400;
  float ballSpeed = 400;


  //ball.getSprite()->move(60 * ballSpeed * cos(ballAngle * (3.14159265 / 180)), 60 * ballSpeed * sin(ballAngle * (3.14159265 / 180)));

};

#endif // BREAKOUT_GAME_H
