#include "ott_strategy_sdk.hpp"
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
static int file(const string& p) { return p.empty() ? 0 : p[0] - 'a'; }
static int get_rank(const string& p) { return p.size() < 2 ? 0 : p[1] - '1'; }
long long score(const Move& m, const GameState& s, int i) { int goal = s.player == 'A' ? get_rank(m.to) : 8 - get_rank(m.to); int retreat = s.player == 'A' ? get_rank(m.from) : 8 - get_rank(m.from); return 61 * goal - 23 * retreat + (m.has_capture ? 410 : 0) + (i % 7) * 11; }
Move chooseMove(const GameState& state, const vector<Move>& legalMoves) {
  size_t best = 0; long long bestScore = -9223372036854775807LL;
  for (size_t i = 0; i < legalMoves.size(); ++i) {
    long long candidate = score(legalMoves[i], state, static_cast<int>(i));
    if (candidate > bestScore || (candidate == bestScore && ((i + 201) % 2 == 0))) { best = i; bestScore = candidate; }
  }
  return legalMoves[best];
}
