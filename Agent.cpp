#include "Agent.h"
#include "MoveSorter.h"

/**
   * Evaluates the score of a position.
   * Scores are relative to the player whose turn is next.
   *
   * @param position The position of the board.
   * @return a score where positive is win, zero is draw, and negative is loss.
   */
int Agent::evaluate(Position &position) {
  return negamax(position, -Position::MAX_SCORE, Position::MAX_SCORE);
}

int Agent::negamax(Position &P, int alpha, int beta) {
  ++nodes_visited;

  if (P.winning()) {
    return P.score();
  }
  if (P.opp_winning()) {
    return -P.score();
  }
  if (P.full()) {
    return 0;
  }

  Position::position_t possible_moves = P.possible_moves();

  MoveSorter move_sorter;
  for (int i = 0; i < 9; ++i) {
    int cell_num = move_order[i];
    if (Position::position_t move = possible_moves & Position::cell_mask(cell_num)) {
      move_sorter.add(move, 0); // TODO: Calculate score.
    }
  }

  int best_score = -Position::MAX_SCORE;

  while (const Position::position_t move = move_sorter.pop()) {
    P.play(move);
    int score = -negamax(P, -beta, -alpha);
    P.undo(move);
    if (score > best_score) {
      best_score = score;
    }
    if (best_score > alpha) {
      alpha = best_score;
    }
    if (alpha >= beta) {
      break;
    }
  }

  return best_score;
}
