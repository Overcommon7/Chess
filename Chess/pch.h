#pragma once

#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"

#include "Utilities/Vector2Int.h"
#include "Utilities/magic_enum.hpp"

#include <array>
#include <chrono>
#include <algorithm>
#include <any>
#include <atomic>
#include <bitset>
#include <charconv>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <concepts>
#include <execution>
#include <stdlib.h>

using std::cout;
using std::string;
using std::vector;
using std::list;
using std::fstream;
using std::ifstream;
using std::ostream;
using std::stringstream;
using std::ofstream;
using std::unordered_map;
using std::string_view;
using std::stringstream;
using std::function;
using std::pair;
using std::function;
using std::wstring;
using std::queue;
using std::set;
using std::unordered_set;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::stoi;
using std::stof;
using std::stod;
using std::stold;
using std::stol;
using std::stoll;
using std::stoull;
using std::to_string;
using std::find;
using std::make_unique;

namespace ch = std::chrono;
namespace fs = std::filesystem;

inline static constexpr int TILE_SIZE = 100;