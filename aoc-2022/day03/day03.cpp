#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include <tl/fold.hpp>
#include <algorithm>
#include <vector>
#include <tl/to.hpp>

int priority(char c) {
    if (std::islower(c)) {
        return c - 'a' + 1;
    }
    return c - 'A' + 27;
}

int score_line(std::string line) {
    auto midpoint = line.size() / 2;
    auto first_half = line.substr(0, midpoint);
    auto second_half = line.substr(midpoint, midpoint);
    auto common = std::ranges::find_first_of(first_half, second_half);
    return priority(*common);
}

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day03/input.txt" };
    auto scores = tl::views::getlines(in)
        | std::views::transform(score_line);
    std::cout << tl::sum(scores);
}
        
int score_group(auto&& group) {
    auto groups = group | tl::to<std::vector>();
    for (auto& group : groups) std::ranges::sort(group);
    std::vector<char> res;
    std::ranges::set_intersection(groups[0], groups[1], std::back_inserter(res));
    auto common = std::ranges::find_first_of(res, groups[2]);
    return priority(*common);
}

void part2() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day03/input.txt" };
    auto scores = tl::views::getlines(in)
        | std::views::chunk(3)
        | std::views::transform([](auto&& rng) { return score_group(rng); });
    std::cout << tl::sum(scores);
}

int main() {
    part2();
}
