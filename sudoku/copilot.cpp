#include <bits/stdc++.h>
using namespace std;

// Sudoku solver (9x9) using backtracking + bitmask constraints + MRV heuristic
// - Board represented as a 9x9 int array (0 = empty)
// - rowMask[r], colMask[c], boxMask[b] hold used digits as bits (1<<d) for d in [1..9]
// - Choose next empty cell with Minimum Remaining Values (fewest candidates)

static const int N = 9;

int boxIndex(int r, int c) {
  return (r / 3) * 3 + (c / 3);
}

void printBoard(const array<array<int, N>, N>& board) {
  for (int r = 0; r < N; ++r) {
    if (r % 3 == 0 && r != 0) cout << "------+-------+------\n";
    for (int c = 0; c < N; ++c) {
      if (c % 3 == 0 && c != 0) cout << "| ";
      cout << board[r][c] << (c == N-1 ? '\n' : ' ');
    }
  }
}

// Convert bitmask of candidates to vector of ints (digits)
vector<int> bitsToDigits(int mask) {
  vector<int> digits;
  for (int d = 1; d <= 9; ++d) {
    if (mask & (1 << d)) digits.push_back(d);
  }
  return digits;
}

bool solveSudoku(array<array<int, N>, N>& board) {
  // masks: bit i (1<<d) means digit d is already used
  array<int, N> rowMask{}, colMask{}, boxMask{};
  // initialize masks
  for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c) {
      int val = board[r][c];
      if (val != 0) {
        int bit = 1 << val;
        rowMask[r] |= bit;
        colMask[c] |= bit;
        boxMask[boxIndex(r,c)] |= bit;
      }
    }

  // list of empty positions
  vector<pair<int,int>> empties;
  empties.reserve(81);
  for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c) if (board[r][c] == 0) empties.emplace_back(r,c);

  // recursive lambda for backtracking
  function<bool()> backtrack = [&]() -> bool {
    if (empties.empty()) return true; // solved

    // MRV: choose empty cell with fewest candidates
    int bestIdx = -1;
    int bestCount = 10; // more than max
    int bestMask = 0;
    for (int i = 0; i < (int)empties.size(); ++i) {
      auto [r, c] = empties[i];
      int used = rowMask[r] | colMask[c] | boxMask[boxIndex(r,c)];
      int candidatesMask = 0;
      for (int d = 1; d <= 9; ++d) if (!(used & (1 << d))) candidatesMask |= (1 << d);
      int cnt = __builtin_popcount((unsigned)candidatesMask);
      if (cnt == 0) return false; // dead end
      if (cnt < bestCount) {
        bestCount = cnt;
        bestIdx = i;
        bestMask = candidatesMask;
        if (cnt == 1) break; // optimal
      }
    }

    // pick the cell
    auto [r, c] = empties[bestIdx];
    // move chosen cell to the end and pop back to avoid erasing middle element repeatedly
    swap(empties[bestIdx], empties.back());
    empties.pop_back();

    // try candidates
    for (int d = 1; d <= 9; ++d) {
      if (!(bestMask & (1 << d))) continue;
      int bit = 1 << d;
      // place
      board[r][c] = d;
      rowMask[r] |= bit;
      colMask[c] |= bit;
      boxMask[boxIndex(r,c)] |= bit;

      if (backtrack()) return true;

      // undo
      board[r][c] = 0;
      rowMask[r] &= ~bit;
      colMask[c] &= ~bit;
      boxMask[boxIndex(r,c)] &= ~bit;
    }

    // restore empties state
    empties.push_back({r,c});
    swap(empties[bestIdx], empties.back());
    return false;
  };

  return backtrack();
}

int main() {
  // Example puzzle (0 = empty). You can replace this with any 9x9 puzzle.
  array<array<int, N>, N> board = {{
      {{5,3,0,0,7,0,0,0,0}},
      {{6,0,0,1,9,5,0,0,0}},
      {{0,9,8,0,0,0,0,6,0}},
      {{8,0,0,0,6,0,0,0,3}},
      {{4,0,0,8,0,3,0,0,1}},
      {{7,0,0,0,2,0,0,0,6}},
      {{0,6,0,0,0,0,2,8,0}},
      {{0,0,0,4,1,9,0,0,5}},
      {{0,0,0,0,8,0,0,7,9}}
  }};

  cout << "Input:\n";
  printBoard(board);

  const auto ok = solveSudoku(board);
  if (ok) {
    cout << "\nSolved:\n";
    printBoard(board);
  } else {
    cout << "No solution found.\n";
  }

  return 0;
}
