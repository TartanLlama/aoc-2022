cmake_minimum_required (VERSION 3.8)

project ("aoc-2022")
find_package(tl-ranges CONFIG REQUIRED)
find_package(ctre CONFIG REQUIRED)
find_package(mdspan CONFIG REQUIRED)

# Include sub-projects.
add_subdirectory ("aoc-2022")