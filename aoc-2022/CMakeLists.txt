cmake_minimum_required (VERSION 3.21)

file(GLOB_RECURSE SOURCES "**.cpp")

foreach(FILE IN LISTS SOURCES)
  cmake_path(GET FILE STEM FILE_STEM)
  add_executable(${FILE_STEM} ${FILE})
  target_link_libraries(${FILE_STEM} PRIVATE tl::ranges ctre::ctre std::mdspan)
  set_target_properties(${FILE_STEM} PROPERTIES CXX_STANDARD 23)
  target_compile_options(${FILE_STEM} PRIVATE /utf-8)
endforeach()