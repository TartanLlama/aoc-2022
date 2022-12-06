#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include "../regex.hpp"
#include <algorithm>

struct range {
    int from;
    int to;
};

auto parse_line(std::string line) {
    auto groups = ctre::match<"([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)">(line);
    return std::pair<range, range>{ 
        { as_int<1>(groups), as_int<2>(groups) },
        { as_int<3>(groups), as_int<4>(groups) }
    };
}

bool one_is_subset(std::pair<range, range> ranges) {
    auto [a, b] = ranges;
    return (a.from <= b.from && a.to >= b.to) ||
        (b.from <= a.from && b.to >= a.to);
}

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day04/input.txt" };
    auto parse_lines = tl::views::getlines(in)
        | std::views::transform(parse_line);
    std::cout << std::ranges::count_if(parse_lines, one_is_subset);
        
}

bool overlap(std::pair<range, range> ranges) {
    auto [a, b] = ranges;
    return !((a.to < b.from) || (b.to < a.from));
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day04/input.txt" };
    auto parse_lines = tl::views::getlines(in)
        | std::views::transform(parse_line);
    std::cout << std::ranges::count_if(parse_lines, overlap);
}

int main() {
    part2();
}
