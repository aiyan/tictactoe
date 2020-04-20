#include "PerfectAgent.h"

Position::position_t PerfectAgent::play(Position &P) {
  const Position::position_t possible_moves = P.possible_moves();

  Position::position_t best_move;

  /**
   * It is important to keep track of alpha (our lowest guaranteed score at the current position).
   * We pass alpha to the negamax function so it can prune branches faster, resulting in
   * a significantly faster search time. The reduction is often 50%!
   */
  int alpha = -Position::MAX_SCORE;

  for (int cell_num : move_order) {
    Position::position_t move = possible_moves & Position::cell_mask(cell_num);
    if (!move) continue;

    P.play(move);

    int score = -negamax(P, -Position::MAX_SCORE, -alpha);

    P.undo(move);

    if (score > alpha) {
      alpha = score;
      best_move = move;
    }
  }

  return best_move;
}

int PerfectAgent::evaluate(Position &P) {
  return negamax(P, -Position::MAX_SCORE, Position::MAX_SCORE);
}

int PerfectAgent::negamax(Position &P, int alpha, int beta) {
  ++nodes_visited;

  // Try to retrieve the entry from the transposition table.
  std::pair<uint8_t, uint8_t> retrieved = transTable.get(P.key());

  // Use the entry only if it exists and its depth is at least the current depth.
  // The depth check is important to determine whether the entry is from the current search.
  if (retrieved.first && retrieved.second >= P.num_moves()) {
    // Derive the actual score from the normalized score.
    int actual_value = retrieved.first + Position::MIN_SCORE - 1;
    beta = std::min(beta, actual_value);
    if (alpha >= beta) {
      return actual_value;
    }
  }

  /**
   * Check for game end conditions.
   */
  if (P.winning()) {
    return P.score();
  }
  if (P.opp_winning()) {
    return -P.score();
  }
  if (P.full()) {
    return 0;
  }

  const Position::position_t possible_moves = P.possible_moves();

  for (int cell_num : move_order) {
    Position::position_t move = possible_moves & Position::cell_mask(cell_num);
    if (!move) continue;

    P.play(move);

    int value = -negamax(P, -beta, -alpha);

    P.undo(move);

    alpha = std::max(alpha, value);

    if (alpha >= beta) {
      break;
    }
  }

  transTable.put(P.key(), alpha - Position::MIN_SCORE + 1, P.num_moves());

  return alpha;
}
