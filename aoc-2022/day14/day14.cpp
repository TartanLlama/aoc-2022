#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include <ranges>
#include <set>
#include "../split.hpp"
#include <tl/adjacent.hpp>

struct coord {
    int x = 0;
    int y = 0;

    coord() = default;
    coord(int x, int y) : x(x), y(y) {}

    friend std::istream& operator>>(std::istream& is, coord& c) {
        is >> c.x;
        is.ignore();
        is >> c.y;
        return is;
    }

    friend auto operator<=>(coord const& lhs, coord const& rhs) = default;
};

std::optional<coord> get_target(std::set<coord> const& occupied, coord sand) {
    if (!occupied.contains(coord{ sand.x, sand.y + 1 })) {
        return coord{ sand.x, sand.y + 1 };
    }

    if (!occupied.contains(coord{ sand.x - 1, sand.y + 1 })) {
        return coord{ sand.x - 1, sand.y + 1 };
    }

    if (!occupied.contains(coord{ sand.x + 1, sand.y + 1 })) {
        return coord{ sand.x + 1, sand.y + 1 };
    }

    return std::nullopt;
}

std::set<coord> get_grid(std::istream& in) {
    auto lines = tl::views::getlines(in)
        | std::views::transform([](auto& line) {
        return split<coord>(line, " -> ");
            });

    std::set<coord> occupied;

    for (auto&& line : lines) {
        for (auto [first, second] : line | tl::views::pairwise) {
            if (first.x == second.x) {
                auto [low, high] = std::minmax(first.y, second.y);
                for (auto i : std::views::iota(low, high + 1)) {
                    occupied.emplace(first.x, i);
                }
            }
            else if (first.y == second.y) {
                auto [low, high] = std::minmax(first.x, second.x);
                for (auto i : std::views::iota(low, high + 1)) {
                    occupied.emplace(i, first.y);
                }
            }
        }
    }

    return occupied;
}

int run_simulation(std::set<coord> occupied, bool return_on_floor) {
    auto low_point = *std::ranges::max_element(occupied, std::ranges::less(), &coord::y);
    int n_sand = 0;

    while (true) {
        coord sand{ 500,0 };

        auto target = get_target(occupied, sand);
        if (!target) {
            return n_sand + 1;
        }

        while (target != std::nullopt) {
            if (target->y >= low_point.y + 2) {
                if (return_on_floor) return n_sand;
                else break;
            }
            sand = *target;
            target = get_target(occupied, sand);
        }

        occupied.insert(sand);
        ++n_sand;
    }
}

int main() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day14/input.txt" };
    auto occupied = get_grid(in);
    std::cout << run_simulation(occupied, true) << '\n';
    std::cout << run_simulation(std::move(occupied), false);
}
