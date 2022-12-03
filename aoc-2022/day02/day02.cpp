#include <fstream>
#include <iostream>
#include <experimental/mdspan>
#include <tl/getlines.hpp>
#include <tl/fold.hpp>

enum class choice {
    rock, paper, scissors
};

enum class result {
    lose, draw, win
};

choice from_theirs(char c) {
    using enum choice;
    switch (c) {
    case 'A': return rock;
    case 'B': return paper;
    case 'C': return scissors;
    }
}

choice choice_from_mine(char c) {
    using enum choice;
    switch (c) {
    case 'X': return rock;
    case 'Y': return paper;
    case 'Z': return scissors;
    }
}

result result_from_mine(char c) {
    using enum result;
    switch (c) {
    case 'X': return lose;
    case 'Y': return draw;
    case 'Z': return win;
    }
}

int score_from_result(result r) {
    using enum result;
    switch (r) {
    case lose: return 0;
    case draw: return 3;
    case win: return 6;
    }
}

int calculate_score_part1(std::string line) {
    auto theirs = from_theirs(line[0]);
    auto mine = choice_from_mine(line[2]);

    using enum choice;
    std::array<int, 9> score_map = {
        3, 0, 6, //rock
        6, 3, 0, //paper
        0, 6, 3  //scissors
    };

    using ext_t = std::experimental::extents<int, 3, std::experimental::dynamic_extent>;
    std::experimental::mdspan<int, ext_t> score_span(score_map.data(), 3);

    auto score = score_span(std::to_underlying(mine), std::to_underlying(theirs));

    return score + std::to_underlying(mine) + 1;
}

int calculate_score_part2(std::string line) {
    auto theirs = from_theirs(line[0]);
    auto mine = result_from_mine(line[2]);

    using enum choice;
    std::array<choice, 9> score_map = {
        scissors, rock, paper, //rock
        rock, paper, scissors, //paper
        paper, scissors, rock  //scissors
    };

    using ext_t = std::experimental::extents<int, 3, 3>;
    std::experimental::mdspan<choice, ext_t> score_span(score_map.data());

    auto score = score_from_result(mine);
    auto my_choice = score_span(std::to_underlying(theirs), std::to_underlying(mine));

    return score + std::to_underlying(my_choice) + 1;
}


void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day02/input.txt" };

    auto scores = tl::views::getlines(in)
        | std::views::transform(calculate_score_part1);
    std::cout << tl::sum(scores);
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day02/input.txt" };

    auto scores = tl::views::getlines(in)
        | std::views::transform(calculate_score_part2);
    std::cout << tl::sum(scores);
}

int main() {
    part1();
}
