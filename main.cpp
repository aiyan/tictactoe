#include <iostream>
#include <chrono>
#include "Position.h"
#include "Agent.h"

int main(int argc, char **argv) {
  Position P;
  P.display();

  Agent A;

  int score;
  int trials = 200;

  auto start_time = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < trials; ++i) {
    score = A.evaluate(P);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

  std::cout << "Score: " << score << " Nodes visited: " << A.num_visited() / trials
            << " Time: " << duration.count() / trials << " ms" << std::endl;

  return 0;
}
