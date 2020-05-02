#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include "Agent.h"
#include "Position.h"
#include "PerfectAgent.h"

class Benchmark {
public:
  /**
   * Benchmarks the speed of an agent by running many trials.
   *
   * @param A The agent to test.
   * @param trials The number of trials to run.
   */
  static const void benchmark(Agent *A, unsigned int trials) {
    // Use an empty board for testing.
    Position P;

    std::chrono::microseconds total_time{0};

    for (int i = 0; i < trials; ++i) {
      // Record the start time.
      auto start_time = std::chrono::high_resolution_clock::now();

      // Evaluate the empty position.
      A->play(P);

      // Record the stop time and calculate the elapsed time.
      auto end_time = std::chrono::high_resolution_clock::now();
      total_time += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

      // Reset the transposition table.
      A->reset();
    }

    std::cout << "Average time: " << total_time.count() / trials << " microseconds" << std::endl;
  }

  /**
   * Matches two agents against each other.
   *
   * @param A1 The agent to play first.
   * @param A2 The agent to play second.
   */
  static const void match(Agent *A1, Agent *A2) {
    Agent *agents[2]{A1, A2};
    Position P;
    P.display();
    std::cout << std::endl;

    int curr_player = 0;
    int winner = 0;

    // Record the start time.
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 9; ++i) {
      Position::position_t move = agents[curr_player]->play(P);
      P.play(move);

      P.display();
      std::cout << std::endl;

      if (P.opp_winning()) {
        winner = curr_player + 1;
        break;
      }
      if (P.full()) {
        break;
      }

      // Switch to the next player.
      curr_player = (curr_player + 1) % 2;
    }

    // Record the stop time and calculate the elapsed time.
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Winner: P" << winner << std::endl;
    std::cout << "Time: " << duration.count() << " us" << std::endl;
  }
};

#endif //BENCHMARK_H
