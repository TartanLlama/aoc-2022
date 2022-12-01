import os
from datetime import date

day = 'day' + str(date.today().day).zfill(2)
os.mkdir('aoc-2022/'+day)

input_file = "\"C:/Users/sybrand/projects/aoc-2022/aoc-2022/" + day + "/input.txt\""
with open('aoc-2022/'+day+'/'+day+'.cpp', 'w') as f:
    f.write(f"""#include <fstream>
#include <iostream>

void part1() {{
    std::ifstream in {{ {input_file} }};
}}

void part2() {{
    std::ifstream in {{ {input_file} }};
}}

int main() {{
    part1();
}}
""")

with open('aoc-2022/'+day+'/'+'input.txt', 'w') as f:
    pass

