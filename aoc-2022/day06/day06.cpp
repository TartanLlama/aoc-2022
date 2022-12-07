#include <fstream>
#include <iostream>
#include <tl/slide.hpp>
#include <array>
#include <algorithm>
#include <tuple>
#include <type_traits>
#include <tl/functional/lift.hpp>
#include <tl/to.hpp>

template <std::size_t N>
void process_data(std::istream& in) {
    std::string data;
    in >> data;

    auto windows = data | tl::views::slide(N);
    auto marker_pos = std::ranges::find_if(windows, [](auto&& window) {
        auto vec = window | tl::to<std::vector>();
        std::ranges::sort(vec);
        return std::ranges::adjacent_find(vec) == std::ranges::end(vec);
     });
    std::cout << std::ranges::distance(std::ranges::begin(windows), marker_pos) + N;
}

void part1() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day06/input.txt" };
    process_data<4>(in);
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day06/input.txt" };
    process_data<14>(in);
}

int main() {
    part2();
}
