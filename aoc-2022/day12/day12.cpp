#include <fstream>
#include <iostream>
#include <tl/getlines.hpp>
#include <tl/to.hpp>
#include <queue>
#include <set>
#include <array>
#include <vector>

struct coord {
    int x;
    int y;

    friend auto operator<=>(coord const&, coord const&) = default;
};

std::pair<coord,coord> get_start_end_pos(auto& lines) {
    coord start;
    coord end;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            if (lines[i][j] == 'S') start = { j,i };
            else if (lines[i][j] == 'E') end = { j,i };
        }
    }

    return std::pair(start, end);
}

auto get_neighbours(coord c) {
    return std::array{
        coord{c.x + 1, c.y},
        coord{c.x - 1, c.y},
        coord{c.x, c.y + 1},
        coord{c.x, c.y - 1},
    };
}

struct entry {
    coord c;
    int n_steps;
};

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day12/input.txt" };

    auto lines = tl::views::getlines(in) | tl::to<std::vector>();
    auto [start, end] = get_start_end_pos(lines);

    std::queue<entry> q;
    q.push({ start,0 });
    std::set<coord> visited{ start };

    auto valid = [&](coord from, coord to) {
        auto in_bounds = to.x >= 0 && to.x < lines[0].size()
            && to.y >= 0 && to.y < lines.size();

        if (!in_bounds) return false;

        auto to_char = lines[to.y][to.x];
        to_char = (to_char == 'E') ? 'z' : to_char;

        auto from_char = lines[from.y][from.x];
        from_char = (from_char == 'S') ? 'a' : from_char;

        return (to_char - from_char <= 1)
            && !visited.contains(to);
    };

    while (q.front().c != end) {
        auto [front_coord, front_steps] = q.front();
        q.pop();
        
        for (coord neighbour : get_neighbours(front_coord)) {
            if (valid(front_coord, neighbour)) {
                visited.insert(neighbour);
                q.push(entry{ neighbour, front_steps + 1 });
            }
        }
    }

    std::cout << q.front().n_steps;
}

void part2() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day12/input.txt" };

    auto lines = tl::views::getlines(in) | tl::to<std::vector>();
    auto [start, end] = get_start_end_pos(lines);

    std::queue<entry> q;
    q.push({ end,0 });
    std::set<coord> visited{ end };

    auto valid = [&](coord from, coord to) {
        auto in_bounds = to.x >= 0 && to.x < lines[0].size()
            && to.y >= 0 && to.y < lines.size();

        if (!in_bounds) return false;

        auto to_char = lines[to.y][to.x];
        to_char = (to_char == 'E') ? 'z' : to_char;

        auto from_char = lines[from.y][from.x];
        from_char = (from_char == 'S') ? 'a' : from_char;

        return (from_char - to_char <= 1)
            && !visited.contains(to);
    };

    while (lines[q.front().c.y][q.front().c.x] != 'a') {
        auto [front_coord, front_steps] = q.front();
        q.pop();

        for (coord neighbour : get_neighbours(front_coord)) {
            if (valid(front_coord, neighbour)) {
                visited.insert(neighbour);
                q.push(entry{ neighbour, front_steps + 1 });
            }
        }
    }

    std::cout << q.front().n_steps;
}

int main() {
    part2();
}
