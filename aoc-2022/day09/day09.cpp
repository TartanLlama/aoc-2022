#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include "../split.hpp"
#include <set>
#include <array>
#include <tl/adjacent.hpp>
#include <ranges>

struct coord {
    long x=0;
    long y=0;
    friend auto operator<=>(const coord&, const coord&) = default;
};

long dir_mod(long head, long tail) {
    if (head > tail) return 1;
    return -1;
}

void move(char dir, coord& head) {
    switch (dir) {
    case 'R': head.x++; break;
    case 'L': head.x--; break;
    case 'U': head.y--; break;
    case 'D': head.y++; break;
    }
}

void update(coord& head, coord& tail) {
    if (std::abs(head.x - tail.x) > 1) {
        if (std::abs(head.y - tail.y) >= 1) {
            tail.y += 1 * dir_mod(head.y, tail.y);
        }
        tail.x += 1 * dir_mod(head.x, tail.x);
    }
    else if (std::abs(head.y - tail.y) > 1) {
        if (std::abs(head.x - tail.x) >= 1) {
            tail.x += 1 * dir_mod(head.x, tail.x);
        }
        tail.y += 1 * dir_mod(head.y, tail.y);
    }
}

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day09/input.txt" };

    coord head;
    coord tail;
    std::set<coord> positions_visited;
    positions_visited.insert(coord{ 0,0 });

    auto instructions = tl::views::getlines(in);

    for (auto& instr : instructions) {
        auto s = split<std::string>(instr, ' ');
        auto dir = s[0][0];
        auto amount = std::stoi(s[1]);

        for (auto i = 0; i < amount; ++i) {
            move(dir, head);
            update(head, tail);
            positions_visited.insert(tail);
        }
    }

    std::cout << positions_visited.size();
}

void output_state(auto& knots, int x, int y) {
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            auto topmost = std::ranges::find(knots, coord{ j, -i });
            if (topmost != knots.end()) {
                std::cout << std::distance(knots.begin(), topmost);
            }
            else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day09/input.txt" };

    std::array<coord, 10> knots;
    std::set<coord> positions_visited;
    positions_visited.insert(coord{ 0,0 });

    auto instructions = tl::views::getlines(in);

    for (auto& instr : instructions) {
        auto s = split<std::string>(instr, ' ');
        auto dir = s[0][0];
        auto amount = std::stoi(s[1]);

        for (auto i = 0; i < amount; ++i) {
            move(dir, knots[0]);
            for (auto&& [lead, follow] : tl::views::pairwise(knots)) {
                update(lead, follow);
            }
            positions_visited.insert(knots.back());
        }
    }

    std::cout << positions_visited.size();
}

int main() {
    part2();
}
