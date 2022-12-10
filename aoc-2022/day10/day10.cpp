#include <fstream>
#include <iostream>
#include <tl/functional/curry.hpp>
#include <tl/fold.hpp>
#include <tl/generator.hpp>
#include <tl/getlines.hpp>
#include "../split.hpp"
#include <optional>
#include <tl/enumerate.hpp>
#include "generator.hpp"
#include <cmath>
#include <tl/zip.hpp>

tl::generator<int> simulator(std::istream& in) {
    auto lines = tl::views::getlines(in);
    auto current = std::ranges::begin(lines);
    std::optional<int> to_add = std::nullopt;
    int x = 1;

    while (current != std::ranges::end(lines)) {
        co_yield x;

        if (to_add) {
            x += *std::exchange(to_add, std::nullopt);
        }
        else {
            auto command = split<std::string>(*current, ' ');
            if (command[0] == "addx") to_add = std::stoi(command[1]);
            ++current;
        }
    }
}

void part1(std::istream& in) {
    auto signal_strengths = tl::views::zip(std::views::iota(1), simulator(in))
        | std::views::transform(tl::uncurry(std::multiplies()))
        | std::views::drop(19)
        | std::views::stride(40);

    std::cout << tl::sum(signal_strengths);
}

void part2(std::istream& in) {
    for (auto [i, x] : simulator(in) | tl::views::enumerate) {
        int pixel = i % 40;
        std::cout << ((std::abs(x - pixel) < 2) ? '#' : ' ');
        if (pixel == 39) std::cout << '\n';
    }
}

int main() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day10/input.txt" };
    //part1(in);
    part2(in);
}
