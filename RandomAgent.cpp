#include <vector>
#include <random>
#include "RandomAgent.h"

/**
 * Selects a random move from a vector of possible moves.
 *
 * @tparam Iter The iterator of the vector.
 * @param start An iterator to the beginning of the vector.
 * @param end An iterator to the end of the vector.
 * @return An iterator advanced to the random element.
 */
template<typename Iter>
Iter RandomAgent::select_rand_move(Iter start, Iter end) {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
  std::advance(start, dis(gen));

  return start;
}

/**
 * Plays a random, legal move.
 *
 * @param P The position on which the agent should play.
 * @return A bitmap where a single "on" bit represents the desired move.
 */
Position::position_t RandomAgent::play(Position &P) {
  // Get a bitmap of all possible moves.
  const Position::position_t possible_moves = P.possible_moves();

  // Initialize a vector such that each element is one move.
  std::vector<Position::position_t> moves;

  for (int i = 0; i < 9; ++i) {
    // Mask the possible moves bitmap with a cell mask.
    Position::position_t move = possible_moves & P.cell_mask(i);
    // If there is a possible move in this cell, add it to the list of possible moves.
    if (move) moves.push_back(move);
  }

  // Select a random move.
  Position::position_t decision = *select_rand_move(moves.begin(), moves.end());

  return decision;
}
