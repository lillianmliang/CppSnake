#include "game.h"
#include <iostream>
#include "SDL.h"
#include "food.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      random_food(0, static_cast<int>(FoodType::Filling)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood(bool random) {
  int x, y, foodType;
  bool occupied;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    foodType = random? random_food(engine) : FoodType::Normal;
    occupied = false;
    // Check that the location is not occupied before placing food.
    if (snake.SnakeCell(x, y)) occupied = true;  // snake is already in this location
    else {
      for (auto f : food) {
        if (x == f.x && y == f.y) occupied = true; // food is already in this location
      }
    }
    if (occupied) continue; // if occupied, try again
    else 
    {
      food.emplace_back(static_cast<FoodType> (foodType), x, y);
      if (static_cast<FoodType> (foodType) == FoodType::Poison) continue;
      else break;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  // Check if there's food over here
  for (auto it = food.begin(); it !=food.end(); it++)  {
    auto f = *it;
    if (f.x == new_x && f.y == new_y) {
      if (f._type == FoodType::Poison) {
        snake.alive = false;
        break;
      }
      else {
        score+=f._points;
        // Grow snake and increase speed.
        snake.GrowBody();
        if (snake.speed+f._speedDiff>0) snake.speed += f._speedDiff;
        std::cout<<"speed "<<snake.speed<<std::endl;
        
        // pop eaten food
        std::cout<<"food.size before pop back: "<<food.size()<<std::endl;
        food.pop_back();
        std::cout<<"food.size after pop back: "<<food.size()<<std::endl;
        
        // place new food
        std::cout<<"food.size before place food: "<<food.size()<<std::endl;
        PlaceFood(true);
        std::cout<<"food.size after place food: "<<food.size()<<std::endl;
        std::cout<<"Food placed"<<std::endl;
        // remove element from food vector and exit loop
        //std::cout<<"food.size before erase: "<<food.size()<<std::endl;
        //food.erase(it);
        //std::cout<<"food.size after erase: "<<food.size()<<std::endl;
        break;
      }
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }