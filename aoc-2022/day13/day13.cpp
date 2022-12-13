#include <fstream>
#include <iostream>
#include <variant>
#include <vector>
#include <tl/getlines.hpp>
#include <tl/chunk.hpp>
#include <tl/enumerate.hpp>
#include <tl/functional/curry.hpp>
#include <tl/fold.hpp>
#include <tl/to.hpp>
#include <string_view>
#include <charconv>
#include <cassert>

template<typename ... Ts>  
struct overload : Ts ... {
    using Ts::operator() ...;
};
template<class... Ts> overload(Ts...) -> overload<Ts...>;

struct value {
    std::variant<int, std::vector<value>> data;

    explicit value(int i) : data(i) {}
    explicit value(std::vector<value> v) : data(std::move(v)) {}
    value(value const& rhs) = default;

    friend bool operator<(value const& lhs, value const& rhs) {
        auto func = overload(
            [](int l, int r) { return l < r; },
            [](std::vector<value> const& l, std::vector<value> const& r) { return l < r; },
            [](int l, std::vector<value> const& r) { return std::vector<value>{value{ l } } < r; },
            [](std::vector<value> const& l, int r) { return l < std::vector<value>{value{ r }}; }
        );
        
        return std::visit(func, lhs.data, rhs.data);
    }

    friend bool operator==(value const& lhs, value const& rhs) = default;
};

int parse_int(auto& it, auto end) {
    auto end_of_int = std::ranges::find_if(it, end, [](auto c) {
        return c == ',' || c == ']';
        });
    int ret = std::stoi(std::string{ it, end });

    it = end_of_int;
    return ret;
}

std::vector<value> parse_list(auto& it, auto end) {
    assert(*it == '[');
    ++it;

    std::vector<value> ret;

    while (it != end && *it != ']') {
        if (std::isdigit(*it)) {
            ret.emplace_back(parse_int(it, end));
        }
        else if(*it == '[') {
            ret.emplace_back(parse_list(it, end));
        }

        if (*it == ',') {
            ++it;
        }
    }

    assert(*it == ']');
    ++it;

    return ret;
}

value parse_value(std::string_view line) {
    auto it = line.begin();
    auto end = line.end();

    return value{ parse_list(it, end) };
}

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day13/input.txt" };

    auto lines = tl::views::getlines(in)
        | std::views::filter([](auto& line) { return !line.empty(); })
        | std::views::transform([](auto& line) { return parse_value(line); })
        | tl::to<std::vector>();

    auto indices = lines
        | tl::views::chunk(2)
        | tl::views::enumerate
        | std::views::filter([](auto const& p) {
        return p.second[0] < p.second[1];
            })
        | std::views::keys
        | std::views::transform([](auto i) { return i + 1; });

    std::cout << tl::sum(indices);
}

void part2() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day13/input.txt" };

    auto lines = tl::views::getlines(in)
        | std::views::filter([](auto& line) { return !line.empty(); })
        | std::views::transform([](auto& line) { return parse_value(line); })
        | tl::to<std::vector>();

    auto pack1 = parse_value("[[2]]");
    auto pack2 = parse_value("[[6]]");
    lines.push_back(pack1);
    lines.push_back(pack2);

    std::sort(begin(lines), end(lines));

    auto pack1_loc = std::ranges::find(lines, pack1);
    auto pack2_loc = std::ranges::find(lines, pack2);

    std::cout << (std::ranges::distance(begin(lines), pack1_loc) + 1) *
        (std::ranges::distance(begin(lines), pack2_loc) + 1);
}

int main() {
    part2();
}
