#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <fstream>

int main() {
  std::cout << "How many obstacles do you want to have in this game?(from 1 to 5)" << "\n";
  int obstacle = 1;
  std::cin >> obstacle;
  if(obstacle < 0) {
    obstacle = 0;
  }
  else if(obstacle > 5) {
    obstacle = 5;
  }
  else{
  }
  std::cout << "There are " << obstacle << " obstacles" << "\n";
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  std::fstream inputFile("../src/score.txt", std::ios::in | std::ios::out);
  if (!inputFile.is_open()) {
      std::cerr << "Can not open file." << std::endl;
      return 1;
  }
  // Đọc dữ liệu từ tệp
  std::string line;
  std::getline(inputFile, line);
  int result = std::stoi(line);
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, obstacle);
  game.SetMaxScore(result);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  if(game.GetScore() > game.GetMaxScore())
  {
    // Đưa con trỏ tệp về đầu để ghi dữ liệu
    inputFile.clear(); // Xóa trạng thái lỗi nếu có
    inputFile.seekp(0, std::ios::beg);
//     std::cout << "before: " << game.GetScore() << "\n";
    std::string maxScore = std::to_string(game.GetScore());
    inputFile << maxScore << std::endl;
//     std::cout << "maxScore: " << maxScore << "\n";
  }
  inputFile.close();
  return 0;
}