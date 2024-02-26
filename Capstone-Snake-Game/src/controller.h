#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  void HandleInput2(bool &running, Snake &snake, std::vector<SDL_Point> food) const;//snake2 //food_v2
//   void HandleInput2(bool &running, Snake &snake, SDL_Point food) const;//snake2 //food_v2

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif