#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <bitset>
#include "cstdint"

class Position {
public:
  using position_t = uint16_t;

  Position() : position(0), mask(0), total_moves(0) {};

  [[nodiscard]] bool winning() const {
    return check_winning(position);
  }

  [[nodiscard]] bool opp_winning() const {
    return check_winning(position ^ mask);
  }

  /**
   * The score is calculated as follows:
   * Let P = position.
   * Let S = score of position from my perspective.
   * Let n = number of turns until win.
   * Let m = player's perspective (either -1 or 1) relative to the position.
   *
   * S(P) = m * (9 - n + 2) / 2
   *
   * For example, if I won after 9 plies (9 half-turns), I would obtain a score of 1.
   * If the opponent won after 7 plies, I would obtain a score of -2.
   *
   * However, in the function below, m is assumed to be 1,
   * as the perspective will be determined by the agent.
   */
  [[nodiscard]] int score() const {
    return (11 - total_moves) / 2;
  }

  /**
   * Determines whether the board is full.
   * Note: the function's return value does not necessarily imply a draw.
   *
   * @return a boolean of whether the board is full.
   */
  [[nodiscard]] bool full() const {
    return total_moves == 9;
  }

  /**
   * Executes a move on the current position.
   *
   * @param move A bitmap where "on" bits denote cells to play in.
   */
  void play(position_t move) {
    // Switch to next player's board.
    position ^= mask;
    // Mark the played move in the mask.
    mask |= move;
    ++total_moves;
  };

  /**
   * Undoes a previously executed move.
   *
   * @param move A bitmap where "on" bits denote the cell(s) where the move was played.
   */
  void undo(position_t move) {
    mask ^= move;
    position ^= mask;
    --total_moves;
  }

  /**
   * Plays in a cell on the board.
   *
   * @param move The cell to play in, ranging from 0 through 8, inclusive.
   */
  void play_cell(int move) {
    play(UINT16_C(1) << (8 - move));
  };

  /**
   * Gets the unoccupied cells in the current position.
   *
   * @return a bitmap where "on" bits are free cells.
   */
  position_t possible_moves() const {
    return ~mask;
  };

  /**
   * Displays the current position in a pretty format.
   */
  void display() const {
    position_t x_position = (total_moves & 1) ? opponent_position() : position;
    position_t o_position = x_position ^mask;

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (first_cell_mask & x_position) {
          std::cout << "X ";
        } else if (first_cell_mask & o_position) {
          std::cout << "O ";
        } else {
          std::cout << ". ";
        }

        x_position <<= 1;
        o_position <<= 1;
      }
      std::cout << std::endl;
    }
  };

  /**
   * Creates a position bitmask where only the specified cell is turned on.
   *
   * @param cell The cell number from 0 to 8, inclusive.
   * @return a position bitmask.
   */
  static constexpr position_t cell_mask(int cell) {
    return UINT16_C(1) << (8 - cell);
  }

  // Since the minimum number of turns to win is 5, the maximum score is (9 - 5 + 2) / 2 = 3.
  // See the public function `score` for more details of how this is calculated.
  static constexpr int MAX_SCORE = 3;

private:
  position_t position;
  position_t mask;
  int total_moves;

  static constexpr position_t first_cell_mask = UINT16_C(1) << 8;
  static constexpr position_t winning_lines[8]{
    0b111000000,
    0b000111000,
    0b000000111,
    0b100100100,
    0b010010010,
    0b001001001,
    0b100010001,
    0b001010100
  };

  /**
   * Checks if the current position is in a won state.
   *
   * @return a boolean of whether the current positions is in a won state.
   */
  [[nodiscard]] bool check_winning(position_t pos) const {
    for (const position_t line : winning_lines) {
      if ((pos & line) == line) {
        return true;
      }
    }
    return false;
  };

  /**
   * Gets the position from the perspective of the opponent.
   *
   * @return the position where "on" bits signify cells where the opponent has played.
   */
  [[nodiscard]] position_t opponent_position() const {
    return position ^ mask;
  };
};

#endif //POSITION_H
