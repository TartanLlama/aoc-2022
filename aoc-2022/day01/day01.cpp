#include <fstream>
#include <iostream>
#include <vector>
#include <tl/to.hpp>
#include <tl/fold.hpp>
#include <tl/getlines.hpp>

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day01/input.txt" };

    auto lines = tl::views::getlines(in) | tl::to<std::vector>();

    auto rng = lines
        | std::views::split("")
        | std::views::transform([](auto group) {
        return tl::fold(group, 0, [](int acc, auto s) { return acc + std::stoi(s);  });
            });

    std::cout << std::ranges::max(rng);
}

void part2() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day01/input.txt" };

    auto lines = tl::views::getlines(in) | tl::to<std::vector>();

    auto rng = lines
        | std::views::split("")
        | std::views::transform([](auto group) {
        return tl::fold(group, 0, [](int acc, auto s) { return acc + std::stoi(s);  });
            })
        | tl::to<std::vector>();

    std::ranges::partial_sort(rng, begin(rng) + 3, std::greater());
    std::cout << tl::fold(rng | std::views::take(3), 0, std::plus());
}

int main() {
    part2();
}
