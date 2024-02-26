#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include <random>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

//snake2
// void Controller::HandleInput2(bool &running, Snake &snake, SDL_Point food) const {
void Controller::HandleInput2(bool &running, Snake &snake, std::vector<SDL_Point> food) const {//food_v2 
//     // Khởi tạo một đối tượng random_engine
//     std::random_device rd;
//     std::mt19937 mt(rd());

//     // Tạo một phạm vi từ 1 đến 8
//     std::uniform_int_distribution<int> dist(1, 4);

//     // Lấy một số ngẫu nhiên từ phạm vi đã định
//     int randomNumber = dist(mt);
  if(static_cast<int>(snake.head_x) < food[0].x)//food_v2 
  {
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);    
  } else if(static_cast<int>(snake.head_x) > food[0].x)//food_v2 
  {
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);     
  }
  else
  {
  	if(static_cast<int>(snake.head_y) <= food[0].y)//food_v2 
  	{
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);   
  	} else {
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);   
  	}    
  }
//       switch (randomNumber) {
//         case 1:
//           ChangeDirection(snake, Snake::Direction::kUp,
//                           Snake::Direction::kDown);
//           break;

//         case 2:
//           ChangeDirection(snake, Snake::Direction::kDown,
//                           Snake::Direction::kUp);
//           break;

//         case 3:
//           ChangeDirection(snake, Snake::Direction::kLeft,
//                           Snake::Direction::kRight);
//           break;

//         case 4:
//           ChangeDirection(snake, Snake::Direction::kRight,
//                           Snake::Direction::kLeft);
//           break;
//       }
}
//snake2