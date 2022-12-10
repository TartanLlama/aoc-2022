#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include <tl/to.hpp>
#include <set>
#include <algorithm>

auto parse_height_map(std::istream& in) {
    return tl::views::getlines(in)
        | std::views::transform([](auto str) {
        return str
        | std::views::transform([](auto c) { return static_cast<int>(c - '0'); })
            | tl::to<std::vector>();
            })
        | tl::to<std::vector>();
}

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day08/input.txt" };

    auto height_map = parse_height_map(in);

    std::set<std::pair<int, int>> visible;
    auto map_size = height_map.size();

    for (auto y = 1; y < map_size-1; ++y) {
        auto max = 0;
        for (auto x = 0; x < map_size-1; ++x) {
            max = std::max(max, height_map[y][x]);
            if (max < height_map[y][x+1]) {
                visible.insert(std::pair(x+1, y));
            }
        }
    }

    for (auto y = 1; y < map_size - 1; ++y) {
        auto max = 0;
        for (auto x = map_size - 1; x > 1; --x) {
            max = std::max(max, height_map[y][x]);
            if (max < height_map[y][x - 1]) {
                visible.insert(std::pair(x-1, y));
            }
        }
    }

    for (auto x = 1; x < map_size - 1; ++x) {
        auto max = 0;
        for (auto y = 0; y < map_size - 1; ++y) {
            max = std::max(max, height_map[y][x]);
            if (max < height_map[y + 1][x]) {
                visible.insert(std::pair(x, y+1));
            }
        }
    }

    for (auto x = 1; x < map_size - 1; ++x) {
        auto max = 0;
        for (auto y = map_size - 1; y > 1; --y) {
            max = std::max(max, height_map[y][x]);
            if (max < height_map[y - 1][x]) {
                visible.insert(std::pair(x, y-1));
            }
        }
    }

    auto red = "\u001b[31;1m";
    auto reset = "\u001b[0m";


    for (auto y = 0; y < map_size; ++y) {
            visible.insert(std::pair(y, 0));
            visible.insert(std::pair(0, y));
            visible.insert(std::pair(map_size-1, y));
            visible.insert(std::pair(y, map_size - 1));
        
    }

    for (auto y = 0; y < map_size; ++y) {
        for (auto x = 0; x < map_size; ++x) {
            if (visible.contains(std::make_pair(x, y))) {
                std::cout << red << height_map[y][x];
            }
            else {
                std::cout << reset << height_map[y][x];
            }
        }
        std::cout << '\n';
    }

    std::cout << visible.size();
}

long calculate_score(auto& map, int y, int x) {
    auto score = 1;
    auto height = map[y][x];

    auto new_score = 0;
    for (auto i = y+1; i < map.size(); ++i) {
        ++new_score;
        if (map[i][x] >= height) break;
    }
    score *= new_score;

    new_score = 0;
    for (auto i = y-1; i >= 0; --i) {
        ++new_score;
        if (map[i][x] >= height) break;
    }
    score *= new_score;

    new_score = 0;
    for (auto i = x+1; i < map.size(); ++i) {
        ++new_score;
        if (map[y][i] >= height) break;
    }
    score *= new_score;

    new_score = 0;
    for (auto i = x-1; i >= 0; --i) {
        ++new_score;
        if (map[y][i] >= height) break;
    }
    score *= new_score;

    return score;
}

void part2() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day08/input.txt" };

    auto height_map = parse_height_map(in);

    long max_score = 0;
    for (auto i = 0; i < height_map.size(); ++i) {
        for (auto j = 0; j < height_map.size(); ++j) {
            max_score = std::max(max_score, calculate_score(height_map, i, j));
        }
    }

    std::cout << max_score;
}

int main() {
    part1();
}
