#!/bin/bash
find src tests include -type f -name "*.hpp" | xargs clang-format -i --style=file
find src tests include -type f -name "*.cpp" | xargs clang-format -i --style=file