# Regression Use-after-free
RegressionUAF is a regression greybox fuzzer which utilizes constructed precondition maps, adds inputs that lead to new precondition transitions to the queue for further testing, and combines with AFLChurn’s power schedule, ACO search heuristic, and weighted sampling method, to effectively discover regression use-after-free vulnerabilities.

# Directory Structure
- regressionUAF_precond_doublelink: version 1, which constructs a precondition map with single-directional transitions between patch and free basic blocks;
- regressionUAF_precond_singlelink: version 2, which accounts for bi-directional transitions between patch and free basic blocks.

# Benchmark Subjects
The following table presents the details of the selected subjects for our benchmark.

| Project    | Test Commit | Regression | Reported Date | Distance Commits | Count   | Bug Type |
|------------|-------------|------------|---------------|------------------|---------|----------|
| readelf    | 923c6a7     | 0a59dec    | 31.Dec’18     | 167              | 96,395  | UAF      |
| mjs        | b1b6eac     | e0faf9f    | 31.Dec’21     | 85               | 573     | UAF      |
| jpegoptim  | d23abf2     | 83dfad1    | 24.May’18     | 7                | 154     | DF       |
| nasm       | 9516cf3f    | f640b61    | 29.Jun’17     | 454              | 3,566   | UAF      |
| mjs        | 9eae0e6     | 5c9fd64    | 26.Dec’17     | 213              | 454     | UAF      |
| xmllint    | 798bdf13    | 0e1a49c    | 21.Mar’22     | 245              | 5,086   | UAF      |
| gifsicle   | fad477c     | not found  | 04.Jan’18     | INF              | 814     | DF       |

We tested the code on Ubuntu 22.04 64-bit system and used git version 2.34.1.

# Project
RegressionUAF is developed based on American Fuzzy Lop (AFL) which was originally developed by Michal Zalewski lcamtuf@google.com, and AFLChurn which was originally developed by Xiaogang Zhu xiaogangzhu@swin.edu.au.

## Build RegressionUAF
```shell
git clone https://github.com/Francesca0901/RegressionUAF.git
cd regressionUAF_precond_doublelink/
export RegressionUAF=$PWD
make clean all
cd llvm_mode
make clean all
```

## Instrument 
Build your project with $RegressionUAF/afl-clang-fast for C code and $RegressionUAF/afl-clang-fast++ for C++ code. For instance,
```shell
CC=$RegressionUAF/afl-clang-fast CXX=$RegressionUAF/afl-clang-fast++ ./configure [...options...]
make
```

## Run RegressionUAF on your program
```shell
afl-fuzz -i <input_dir> -o <out_dir> -- <file_path> [...parameters...]
```
You should see things like:
[]
The "aflchurn factor" is the fitness of the current seed as decided by the AFLChurn power schedule.
