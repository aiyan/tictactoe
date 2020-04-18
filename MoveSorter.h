#ifndef MOVESORTER_H
#define MOVESORTER_H

#include "Position.h"

class MoveSorter {
public:
  MoveSorter() : size(0) {};

  void clear() {
    size = 0;
  }

  void add(Position::position_t move, int score) {
    int i = size++;
    for (; i && entries[i - 1].score > score; --i) {
      entries[i] = entries[i - 1];
    }
    entries[i].move = move;
    entries[i].score = score;
  }

  Position::position_t pop() {
    if (size) {
      return entries[--size].move;
    } else {
      return 0;
    }
  }

private:
  struct {
    Position::position_t move;
    int score;
  } entries[9];

  int size;
};

#endif //MOVESORTER_H
