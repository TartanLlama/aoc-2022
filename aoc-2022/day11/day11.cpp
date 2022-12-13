#include <fstream>
#include <iostream>
#include <ctre.hpp>
#include <tl/getlines.hpp>
#include <queue>
#include <functional>
#include <tl/functional/lift.hpp>
#include <tl/to.hpp>
#include "../split.hpp"

using worry = std::uint64_t;
struct monkey {
    std::deque<worry> items;
    std::function<worry(worry)> operation;
    int divisor;
    int on_true;
    int on_false;
};

monkey parse_monkey(auto& it) {
    ++it;
    monkey ret;

    ret.items = split<int>((*it++).substr(18), ',')
        | tl::to<std::deque<worry>>();
    
    auto expr = (*it++).substr(19);
//    auto s = split(expr, ' ');


    return ret;
}

void part1() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day11/input.txt" };
    auto lines = tl::views::getlines(in);
    auto it = std::ranges::begin(lines);

    std::vector<monkey> monkeys;

    while (it != std::ranges::end(lines)) {
        monkeys.push_back(parse_monkey(it));
    }
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day11/input.txt" };
}

int main() {
    part1();
}
