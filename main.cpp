#include <array>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>


/// @var Compile time number of queens
#ifndef NB_QUEENS
#define NB_QUEENS 8U
#endif

/// @namespace n-queens namespace
namespace n_queens {

/// @var Compile time size of the board based on number of queens. @see NB_QUEENS.
constexpr size_t DEFAULT_SIZE = NB_QUEENS;

/// @enum box representation
enum class box_t : bool {
  EMPTY = false, ///< @var empty box
  QUEEN = true, ///< @var queen placed on box
};

constexpr auto DEFAULT_WHITE_STR = "⬜";
constexpr auto DEFAULT_BLACK_STR = "⬛";
constexpr auto DEFAULT_QUEEN_STR = "👸";

/// @struct box string operator
struct box_stringifier_t final {

  std::string black_str{DEFAULT_BLACK_STR};
  std::string white_str{DEFAULT_WHITE_STR};
  std::string queen_str{DEFAULT_QUEEN_STR};

  box_stringifier_t() {
	char *env_str;
	env_str = getenv("N_QUEENS_BLACK");
	if (env_str!=nullptr) {
	  black_str = std::string{env_str};
	}
	env_str = getenv("N_QUEENS_WHITE");
	if (env_str!=nullptr) {
	  white_str = std::string{env_str};
	}
	env_str = getenv("N_QUEENS_QUEEN");
	if (env_str!=nullptr) {
	  queen_str = std::string{env_str};
	}
  }

  /// @fn call function
  /// @brief convert a box to its string representation
  /// @param box the box to convert to string
  /// @param line_index the line index of the box
  /// @param column_index the column index of the box
  /// @return the string representation
  const std::string &operator()(const box_t &box, int line_index, int column_index) const {
	switch (box) {
	case box_t::EMPTY: return (line_index + column_index)%2 ? white_str : black_str;
	case box_t::QUEEN: return queen_str;
	}
  }
};

/// @class chessboard
/// @tparam SIZE the size of the board
template<size_t SIZE = DEFAULT_SIZE>
class chessboard_t final {
private:

  /// @var box to string operator
  box_stringifier_t box_stringifier{};

  /// @class inner board line
  class line_t final {
  private:
	/// @typedef data alias
	using data_t = std::array<box_t, SIZE>;

	/// @var line allocation
	data_t data{};

	/// @var position of the queen on the line
	size_t pos{};

  public:
	/// @fn place queen
	/// @brief place a queen at given index
	/// @param index position to place the queen on the line
	/// @throw out of range exception if index not in line
	void place_queen(size_t index) noexcept(false) {
	  if (index >= SIZE) {
		throw std::out_of_range("");
	  }
	  data.at(pos) = box_t::EMPTY;
	  data.at(index) = box_t::QUEEN;
	  pos = index;
	}

	/// @fn at const access
	/// @brief access box from line at given index
	/// @param index position to access
	/// @throw out of range exception if index not in line
	const box_t &at(size_t index) const noexcept(false) {
	  if (index >= SIZE) {
		throw std::out_of_range("");
	  }
	  return data.at(index);
	}

	/// @fn threaten
	/// @brief project the threatening of the queen to other line
	/// @param delta_index the distance to the other line
	/// @return the indexes on the other line threatened by queen on current line
	std::vector<size_t> threaten(size_t delta_index) const {
	  std::vector<size_t> boxes{};
	  for (auto i = -1; i <= 1; ++i) {
		const auto projection = pos + i*delta_index;
		if (projection >= 0 and projection < SIZE) {
		  boxes.push_back(projection);
		}
	  }
	  return boxes;
	}

  };

  /// @typedef grid type alias. @see line_t
  using grid_t = std::array<line_t, SIZE>;

  /// @var grid allocation
  grid_t grid{};

  /// @fn candidate positions
  /// @brief compute all the positions that can be used to place a queen at a given line
  /// @param line_index the index of the line
  /// @return the position
  /// @throw out of range exception if line index not in grid
  std::set<size_t> candidate_positions(size_t line_index) {
	if (line_index >= SIZE) {
	  throw std::out_of_range("");
	}
	// populate the candidates
	std::set<size_t> candidates{};
	for (auto column_index = 0U; column_index < SIZE; ++column_index) {
	  candidates.insert(column_index);
	}
	// remove threats from already placed queens
	std::set<size_t> threats{};
	for (auto previous_line_index = 0U; previous_line_index < line_index; ++previous_line_index) {
	  const auto dist = line_index - previous_line_index;
	  const auto &line = grid.at(previous_line_index);
	  for (const auto &threat: line.threaten(dist)) {
		threats.insert(threat);
	  }
	}
	for (const auto &threat: threats) {
	  candidates.erase(threat);
	}
	return candidates;
  }

  /// @fn at access
  /// @brief access line at given index
  /// @param index position to access
  /// @throw out of range exception if index not in grid
  line_t &at(size_t line_index) noexcept(false) {
	if (line_index >= SIZE) {
	  throw std::out_of_range("");
	}
	return grid.at(line_index);
  }

  /// @fn at const access
  /// @brief access line at given index
  /// @param index position to access
  /// @throw out of range exception if index not in grid
  const line_t &at(size_t line_index) const noexcept(false) {
	if (line_index >= SIZE) {
	  throw std::out_of_range("");
	}
	return grid.at(line_index);
  }

  /// @fn at access
  /// @brief access box at given indexes
  /// @param line_index line position to access
  /// @param column_index column position to access
  /// @throw out of range exception if index not in grid
  box_t &at(size_t line_index, size_t column_index) noexcept(false) {
	if (column_index >= SIZE) {
	  throw std::out_of_range("");
	}
	return at(line_index).at(column_index);
  }

  /// @fn at const access
  /// @brief access box at given indexes
  /// @param line_index line position to access
  /// @param column_index column position to access
  /// @throw out of range exception if index not in grid
  const box_t &at(size_t line_index, size_t column_index) const noexcept(false) {
	if (column_index >= SIZE) {
	  throw std::out_of_range("");
	}
	return at(line_index).at(column_index);
  }

public:

  /// @fn constructor
  /// @brief default constructor
  chessboard_t() = default;

  /// @fn place queens
  /// @brief place the queens on board
  /// @return true if queens could have been placed, else false
  bool place_queens() {
	std::stack<std::tuple<size_t, std::set<size_t>>> stack;
	stack.push({0U, candidate_positions(0U)});
	size_t index = 0U;
	while (index < SIZE and not stack.empty()) {
	  auto top = stack.top();
	  stack.pop();
	  index = std::get<0>(top);
	  auto candidates = std::get<1>(top);
	  if (not candidates.empty()) {
		auto candidate = std::begin(candidates);
		auto &line = at(index);
		candidates.erase(candidate);
		line.place_queen(*candidate);
		stack.push({index, candidates});
		index++;
		if (index < SIZE) {
		  candidates = candidate_positions(index);
		  stack.push({index, candidates});
		}
	  }
	}
	return index==SIZE;
  }

  /// @fn output stream operator
  /// @brief output a chessboard
  /// @brief os the stream to output in
  /// @brief chessboard the chessboard to output
  /// @brief return the stream with the chessboard representation in
  friend std::ostream &operator<<(std::ostream &os, const chessboard_t &chessboard) {
	for (auto line_index = 0U; line_index < SIZE; ++line_index) {
	  for (auto column_index = 0U; column_index < SIZE; ++column_index) {
		const auto &box = chessboard.at(line_index, column_index);
		os << chessboard.box_stringifier(box, line_index, column_index);
	  }
	  os << std::endl;
	}
	return os;
  }
};

} // namespace n_queens

int main() {
  // create chessboard
  n_queens::chessboard_t<> chessboard{};

  // try to solve the problem
  const auto solved = chessboard.place_queens();

  // output result
  if (solved) {
	std::cout << chessboard << std::endl;
  } else {
	std::cout << "No solution" << std::endl;
  }

  return solved ? EXIT_SUCCESS : EXIT_FAILURE;
}