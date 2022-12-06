#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include <vector>
#include <tl/to.hpp>
#include <tl/enumerate.hpp>
#include <algorithm>
#include <stack>
#include "../split.hpp"

using stacks_t = std::vector<std::stack<char>>;

void move_9000(stacks_t& stacks, std::size_t n, std::size_t from, std::size_t to) {
    for (auto i = 0; i < n; ++i) {
        auto top = stacks[from].top();
        stacks[from].pop();
        stacks[to].push(top);
    }
}

void move_9001(stacks_t& stacks, std::size_t n, std::size_t from, std::size_t to) {
    std::stack<char> temp;
    for (auto i = 0; i < n; ++i) {
        auto top = stacks[from].top();
        stacks[from].pop();
        temp.push(top);
    }

    while (!temp.empty()) {
        stacks[to].push(temp.top());
        temp.pop();
    }
}

template <class F>
void run_input(std::istream& in, F move_func) {
    auto lines = tl::views::getlines(in) | tl::to<std::vector>();
    auto end = std::ranges::find(lines, "");

    auto stack_numbers = *(--end);
    auto n_stacks = *(std::end(stack_numbers) - 2) - '0';

    stacks_t stacks(n_stacks);

    for (auto& line : std::ranges::subrange(begin(lines), end) | std::views::reverse) {
        for (auto [i, stack] : tl::views::enumerate(stacks)) {
            auto c = line[(i * 4) + 1];
            if (c != ' ') stack.push(c);
        }
    }

    for (auto& line : std::ranges::subrange(end + 2, std::end(lines))) {
        auto input = split<std::string>(line, ' ');
        auto n = std::stoi(input[1]);
        auto from = std::stoi(input[3]) - 1;
        auto to = std::stoi(input[5]) - 1;

        move_func(stacks, n, from, to);
    }

    auto res = stacks
        | std::views::transform([](auto& stack) { return stack.top(); })
        | tl::to<std::string>();
    std::cout << res;
}

void part1() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day05/input.txt" };
    run_input(in, move_9000);
}

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day05/input.txt" };
    run_input(in, move_9001);
}

int main() {
    part2();
}
