
#include "Game.h"
#include <iostream>
#include <cmath>
#include "Block.h"
#include "Vector2.h"

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  //init ball movement
  ballDirection.x = 1;
  ballDirection.y = -1;
  ballDirection.normalise();

  //init ball
  ball.initialiseSprite(ball_texture, "Data/Images/ballGrey.png");
  ball.getSprite()->setScale(0.5, 0.5);
  ball.getSprite()->setPosition(window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2, paddle.getSprite()->getPosition().y - ball.getSprite()->getGlobalBounds().height - 20);

//init blocks as grid
for (int i = 0; i < rows; i++)
{
  for (int j = 0; j < columns; j++)
  {
    if (!block[i][j].initialiseSprite(block_texture, "Data/Images/element_yellow_rectangle.png"))
    {
      std::cout << "blocks didnt load";
    }
    block[i][j].getSprite()->setPosition(block[i][j].getSprite()->getGlobalBounds().width * (i - 0.09), block[i][j].getSprite()->getGlobalBounds().height * j);
  }
}

  //init paddle
  paddle.initialiseSprite(paddle_texture, "Data/Images/paddleRed.png");
  paddle.getSprite()->setScale(1.5, 0.5);
  paddle.getSprite()->setPosition(window.getSize().x / 2 - paddle.getSprite()->getGlobalBounds().width / 2, 980);

  //init texts
  menu_text.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  menu_text.getText()->setString("BREAKOUT:");
  menu_text.getText()->setCharacterSize(100);
  menu_text.getText()->setFillColor(sf::Color(225, 225, 255, 255));
  menu_text.getText()->setPosition(window.getSize().x / 2 - menu_text.getText()->getGlobalBounds().width / 2, window.getSize().y / 2 - menu_text.getText()->getGlobalBounds().height / 0.25);

  play_option.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  play_option.getText()->setString("Play");
  play_option.getText()->setFont(font);
  play_option.getText()->setCharacterSize(75);
  play_option.getText()->setFillColor(sf::Color(128,128,128, 150));
  play_option.getText()->setPosition(window.getSize().x / 2 - play_option.getText()->getGlobalBounds().width * 0.47, window.getSize().y / 2 - play_option.getText()->getGlobalBounds().height / 0.8);

  play_again.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  play_again.getText()->setString("Play");
  play_again.getText()->setFont(font);
  play_again.getText()->setCharacterSize(75);
  play_again.getText()->setFillColor(sf::Color(128,128,128, 150));
  play_again.getText()->setPosition(window.getSize().x / 2 - play_again.getText()->getGlobalBounds().width * 0.47, window.getSize().y / 2 - play_again.getText()->getGlobalBounds().height / 0.8);

  quit_option.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  quit_option.getText()->setString("Quit");
  quit_option.getText()->setFont(font);
  quit_option.getText()->setCharacterSize(75);
  quit_option.getText()->setFillColor(sf::Color(128,128,128, 150));
  quit_option.getText()->setPosition(window.getSize().x / 2 - quit_option.getText()->getGlobalBounds().width * 0.47, window.getSize().y / 1 - quit_option.getText()->getGlobalBounds().height / 0.2);

  lives_text.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  lives_text.getText()->setString("LIVES:");
  lives_text.getText()->setFont(font);
  lives_text.getText()->setCharacterSize(50);
  lives_text.getText()->setFillColor(sf::Color(255,255,255, 255));
  lives_text.getText()->setPosition(820 , 1020);

  game_over_text.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  game_over_text.getText()->setString("GAME OVER!");
  game_over_text.getText()->setFont(font);
  game_over_text.getText()->setCharacterSize(100);
  game_over_text.getText()->setFillColor(sf::Color(255,0,0, 255));
  game_over_text.getText()->setPosition(window.getSize().x / 2 - game_over_text.getText()->getGlobalBounds().width / 2, window.getSize().y / 2 - game_over_text.getText()->getGlobalBounds().height / 0.25);

  game_win_text.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  game_win_text.getText()->setString("YOU WIN!");
  game_win_text.getText()->setFont(font);
  game_win_text.getText()->setCharacterSize(100);
  game_win_text.getText()->setFillColor(sf::Color(0,255,0, 255));
  game_win_text.getText()->setPosition(window.getSize().x / 2 - game_over_text.getText()->getGlobalBounds().width / 2, window.getSize().y / 2 - game_over_text.getText()->getGlobalBounds().height / 0.25);


  //init lives
  lives.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  lives.getText()->setString(std::to_string(numlives));
  lives.getText()->setFont(font);
  lives.getText()->setCharacterSize(60);
  lives.getText()->setFillColor(sf::Color(255,255,255, 255));
  lives.getText()->setPosition(980, window.getSize().y - (lives.getText()->getGlobalBounds().height * 1.5));

  //init score
  score.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  score.getText()->setString("Your score: " + std::to_string(Score));
  score.getText()->setFont(font);
  score.getText()->setCharacterSize(60);
  score.getText()->setFillColor(sf::Color(255,255,255, 255));
  score.getText()->setPosition(75, window.getSize().y - (score.getText()->getGlobalBounds().height * 1.5));

  final_score.initialiseText(font, "Data/Fonts/open-sans/OpenSans-Semibold.ttf");
  final_score.getText()->setString("Your score: " + std::to_string(fScore));
  final_score.getText()->setFont(font);
  final_score.getText()->setCharacterSize(60);
  final_score.getText()->setFillColor(sf::Color(255,255,255, 255));
  final_score.getText()->setPosition(75, ((window.getSize().y / 2) +50));

  return true;
}

void Game::update(float dt)
{
  if (game_state == 1)
  {
    ball.getSprite()->move(ballDirection.x * ballSpeed * dt, ballDirection.y * ballSpeed * dt);

    // paddle movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      paddle.getSprite()->move(5.0f, 0 * paddleSpeed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      paddle.getSprite()->move(-5.0f, 0 * paddleSpeed * dt);
    }

    if (paddle.getSprite()->getPosition().x < 0)
    {
      paddle.getSprite()->setPosition(0, 980);
    }
    if (paddle.getSprite()->getPosition().x + paddle.getSprite()->getGlobalBounds().width > window.getSize().x)
    {
      paddle.getSprite()->setPosition(window.getSize().x - paddle.getSprite()->getGlobalBounds().width, 980);
    }

    // hitting bottom
    if (ball.getSprite()->getPosition().y > (window.getSize().y - ball.getSprite()->getGlobalBounds().height))
    {
      numlives--;
      ballSpeed = ballSpeed;
      paddle.getSprite()->setPosition(window.getSize().x / 2 - paddle.getSprite()->getGlobalBounds().width / 2, 980);
      ball.getSprite()->setPosition(window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2, paddle.getSprite()->getPosition().y - ball.getSprite()->getGlobalBounds().height - 20);
      lives.getText()->setString(std::to_string(numlives));
    }

    // hitting right wall
    if (ball.getSprite()->getPosition().x + ball.getSprite()->getGlobalBounds().width > window.getSize().x)
    {
      ballDirection.x = -ballDirection.x;
    }

    // hitting left wall
    if (ball.getSprite()->getPosition().x <= 0.0f)
    {
      ballDirection.x = -ballDirection.x;
    }

    // hitting top
    if (ball.getSprite()->getPosition().y < 0)
    {
      ballDirection.y = -ballDirection.y;
    }

    if (ball.getSprite()->getGlobalBounds().intersects(paddle.getSprite()->getGlobalBounds()))
    {
      sf::FloatRect overlap;
      ball.getSprite()->getGlobalBounds().intersects(
        paddle.getSprite()->getGlobalBounds(), overlap);

      if (overlap.width < overlap.height)
      {
      ballDirection.y = -ballDirection.y;
      }
    }

    //bouncing off sides of paddle
    if ((ball.getSprite()->getPosition().y + ball.getSprite()->getGlobalBounds().height > paddle.getSprite()->getPosition().y) &&
        (ball.getSprite()->getPosition().x + ball.getSprite()->getGlobalBounds().width > paddle.getSprite()->getPosition().x) &&
        (ball.getSprite()->getPosition().x < paddle.getSprite()->getPosition().x + paddle.getSprite()->getGlobalBounds().width))
    {
      ballDirection.y = -ballDirection.y;
    }

    //hitting blocks
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++)
      {
        if (block[i][j].is_visible && ball.getSprite()->getGlobalBounds().intersects(block[i][j].getSprite()->getGlobalBounds()))
        {
          sf::FloatRect overlap;
          ball.getSprite()->getGlobalBounds().intersects(block[i][j].getSprite()->getGlobalBounds(), overlap);

          if (overlap.width < overlap.height)
          {
            // Horizontal collision
            ballDirection.x = -ballDirection.x;
          }
          else
          {
            // Vertical collision
            ballDirection.y = -ballDirection.y;
          }
          block[i][j].is_visible = false;
          Score += 5;
          fScore += 5;
          ballSpeed += 5;
          score.getText()->setString("Your score: " + std::to_string(Score));
        }
      }
    }
  }
  if (numlives <= 0)
  {
      game_state = 2;
  }

  if (Score >= 1530)
  {
      game_state = 2;
  }

  //reset everything
  if (game_state == 2)
  {
      reset();
  }
}


void Game::reset()
{
  final_score.getText()->setString("Your score: " + std::to_string(fScore));
  score.getText()->setString("Your score: " + std::to_string(Score));
  lives.getText()->setString(std::to_string(numlives));
  numlives = 5;
  Score = 0;
  ballSpeed = 400;
  paddle.getSprite()->setPosition(window.getSize().x / 2 - paddle.getSprite()->getGlobalBounds().width / 2, 980);
  ball.getSprite()->setPosition(window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2, paddle.getSprite()->getPosition().y - ball.getSprite()->getGlobalBounds().height - 20);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < columns; ++j)
    {
      block[i][j].is_visible = true;
    }
  }
}


void Game::render()
{
  if (game_state == 0)
  //render menu
  {
    window.draw(*menu_text.getText());
    window.draw(*play_option.getText());
    window.draw(*quit_option.getText());
  }

  if (game_state == 1)
    //render main game
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++)
      {
        if (block[i][j].is_visible)
        {
          window.draw(*block[i][j].getSprite());
        }
      }
    }
    window.draw(*ball.getSprite());
    window.draw(*paddle.getSprite());
    window.draw(*lives.getText());
    window.draw(*score.getText());
    //window.draw(*score_text.getText());
    window.draw(*lives_text.getText());
  }

  if
    (game_state == 2)
  //render end game screen
  {
    window.draw(*final_score.getText());
    window.draw(*play_again.getText());
    window.draw(*quit_option.getText());

    if (Score >= 1530)
    {
      window.draw(*game_win_text.getText());
    }
    else
    {
      window.draw(*game_over_text.getText());
    }
    if (numlives = 0)
    {
      window.draw(*game_over_text.getText());
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
  {
    play_selected = !play_selected;
    if (play_selected)
    {
      play_option.getText()->setFillColor(sf::Color(255,255,255, 255));
      quit_option.getText()->setFillColor(sf::Color(128,128,128, 100));
    }

    else
    {
      quit_option.getText()->setFillColor(sf::Color(255,255,255, 255));
      play_option.getText()->setFillColor(sf::Color(128,128,128, 100));
    }

    playagain_selected = !playagain_selected;
    if (playagain_selected)
    {
      play_again.getText()->setFillColor(sf::Color(255,255,255, 255));
      quit_option.getText()->setFillColor(sf::Color(128,128,128, 100));
    }
    else
    {
      quit_option.getText()->setFillColor(sf::Color(255,255,255, 255));
      play_again.getText()->setFillColor(sf::Color(128,128,128, 100));
    }


  }

  if (event.key.code == sf::Keyboard::Escape)
  {
    game_state = 0;
  }

  else if (event.key.code == sf::Keyboard::Enter)
  {
    reset();
    fScore = 0;
    numlives = 5;
    if (play_selected || playagain_selected)
    {
      game_state = 1;
    }
    else
    {
      window.close();
    }
  }
}

