#include <ctre.hpp>

template <std::size_t N, class T>
int as_int(T const& groups) {
    return std::stoi(groups.get<N>().to_string());
}