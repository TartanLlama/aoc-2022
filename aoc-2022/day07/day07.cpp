#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <tl/getlines.hpp>
#include <tl/to.hpp>
#include <string_view>
#include "../split.hpp"
#include <algorithm>

struct node {
    std::string name;
    std::size_t size = 0;
    node* parent = nullptr;
    std::vector<std::unique_ptr<node>> children;

    bool is_file() {
        return children.empty();
    }

    bool is_dir() {
        return !is_file();
    }

    node(node* parent, std::string name) : parent(parent), name(std::move(name)) {}
    node(node* parent, std::string name, std::size_t size) : parent(parent), name(std::move(name)), size(size) {}
};

class command_line {
    std::unique_ptr<node> root_ = std::make_unique<node>(nullptr, "/");
    node* current_dir_;
    std::vector<std::string>::iterator current_;
    std::vector<std::string>::iterator end_;

    node* mkdir(std::string name) {
        auto new_node = std::make_unique<node>(current_dir_, std::move(name));
        auto node_p = new_node.get();
        current_dir_->children.push_back(std::move(new_node));
        return node_p;
    }

    node* mkfile(std::string name, std::size_t size) {
        auto new_node = std::make_unique<node>(current_dir_, std::move(name), size);
        auto node_p = new_node.get();
        current_dir_->children.push_back(std::move(new_node));

        for (node* parent = current_dir_; parent != nullptr; parent = parent->parent) {
            parent->size += node_p->size;
        }

        return node_p;
    }

    void change_dir(std::string_view name) {
        if (name == "/") {
            current_dir_ = root_.get();
        }
        else if (name == "..") {
            current_dir_ = current_dir_->parent;
        }
        else {
            auto it = std::ranges::find_if(current_dir_->children,
                [=](auto& n) { return n->name == name; });

            if (it == std::ranges::end(current_dir_->children)) {
                current_dir_ = mkdir(std::string(name));
            }
            else {
                current_dir_ = it->get();
            }
        }
    }

    void list_dir() {
        ++current_;

        for (; current_ != end_ && current_->front() != '$'; ++current_) {
            auto entry = split<std::string>(*current_, ' ');
            if (entry[0] == "dir") {
                mkdir(entry[1]);
            }
            else {
                mkfile(entry[1], std::stoi(entry[0]));
            }
        }

        --current_;
    }

public:
    void process(std::istream& in) {
        auto lines = tl::views::getlines(in) | tl::to<std::vector>();

        current_ = std::begin(lines);
        current_dir_ = root_.get();
        end_ = std::end(lines);

        while (current_ != std::end(lines)) {
            auto commands = split<std::string>(*current_, ' ');

            if (commands[1] == "cd") {
                change_dir(commands[2]);
            }
            else {
                list_dir();
            }
            ++current_;
        }
    }

    template <class F>
    void walk_tree(F& f, node* current) {
        f(current);

        for (auto& child : current->children) {
            walk_tree(f, child.get());
        }
    }

    template <class F>
    void walk_tree(F& f) {
        return walk_tree(f, root_.get());
    }

    std::size_t root_size() {
        return root_->size;
    }
};

void part1() {
    std::ifstream in { "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day07/input.txt" };
    command_line cl;
    cl.process(in);
    std::size_t size = 0;
    auto size_walker = [&size](node* n) { 
        if (n->is_dir() && n->size <= 100000) size += n->size;
    };
    cl.walk_tree(size_walker);
    std::cout << size;
}

struct delete_walker {
    std::vector<std::size_t> options;
    std::size_t to_free;

    delete_walker(std::size_t to_free) : to_free(to_free) {}

    void operator() (node* n) {
        if (n->is_dir() && n->size >= to_free) {
            options.push_back(n->size);
        }
    }

    std::size_t best_option() {
        return std::ranges::min(options);
    }
};

void part2() {
    std::ifstream in{ "C:/Users/sybrand/projects/aoc-2022/aoc-2022/day07/input.txt" };
    command_line cl;
    cl.process(in);

    auto size_to_free = 30'000'000 - (70'000'000 - cl.root_size());
    delete_walker walk(size_to_free);
    cl.walk_tree(walk);
    std::cout << walk.best_option();
}

int main() {
    part2();
}
