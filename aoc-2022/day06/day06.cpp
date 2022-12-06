#include <fstream>
#include <iostream>
#include <tl/adjacent.hpp>
#include <array>
#include <algorithm>
#include <tuple>
#include <type_traits>
#include <tl/functional/lift.hpp>

template <std::size_t N>
bool are_unique(std::array<char, N> arr) {
    std::ranges::sort(arr);
    return std::ranges::adjacent_find(arr) == std::ranges::end(arr);
}

template <class Tuple>
auto tuple_to_array(Tuple&& t) {
    return std::apply([](auto... chars) { return std::array{ chars... }; },
        std::forward<Tuple>(t));
}

template <std::size_t N>
void process_data(std::istream& in) {
    std::string data;
    in >> data;

    auto windows = data
        | tl::views::adjacent<N>
        | std::views::transform(TL_LIFT(tuple_to_array));
    auto marker_pos = std::ranges::find_if(windows, are_unique<N>);
    std::cout << std::ranges::distance(std::ranges::begin(windows), marker_pos) + N;
}

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day06/input.txt" };
    process_data<4>(in);
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day06/input.txt" };
    process_data<14>(in);
}

int main() {
    part2();
}
