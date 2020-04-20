#ifndef TRANSPOSITIONTABLE_H
#define TRANSPOSITIONTABLE_H

#include <cstring>

template<class key_t, class value_t, class depth_t>
class TranspositionTable {
public:
  TranspositionTable() {
    table = new Entry[size];
    clear();
  }

  ~TranspositionTable() {
    delete[] table;
  }

  /**
   * Retrieves an entry from the transposition table.
   *
   * @param key The unique key of the position.
   * @return a pair where the first and second values are the position value and the position depth, respectively.
   * Zeros are returned if the entry was not found.
   */
  std::pair<key_t, depth_t> get(key_t key) const {
    Entry entry = table[compute_index(key)];

    // Check if the entry's key matches.
    // It may not match if the entry does not exist or it was overwrote.
    if (entry.key != key) {
      return std::make_pair(0, 0);
    }
    return std::make_pair(entry.value, entry.depth);
  }

  /**
   * Puts an entry into the transposition table.
   *
   * @param key The unique key of the board position.
   * @param value The value of the position.
   * @param depth The depth of the position.
   */
  void put(key_t key, value_t value, depth_t depth) {
    // Obtain the index of the key.
    size_t pos = compute_index(key);

    // Save the necessary data as a table entry.
    table[pos] = {
      key,
      value,
      depth,
    };
  }

  /**
   * Fills the transposition table with zeros.
   */
  void clear() {
    memset(table, 0, size * sizeof(Entry));
  }

private:
  static constexpr size_t size = 131072;

  struct Entry {
    key_t key;
    value_t value;
    depth_t depth;
  };

  Entry *table;

  size_t compute_index(key_t key) const {
    return key % size;
  }
};

#endif //TRANSPOSITIONTABLE_H
