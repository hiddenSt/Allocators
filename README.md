# Allocators
Allocators is a tool that allows you to do efficient memory management in your project.
The main goal of this project is to provide some common memory allocation/free logic.

## Prerequisites
Before you begin, ensure you have met the following requirements:
* You have installed ```clang``` version 10 or higher
* You have installed the latest version of ```cmake```
* You have installed `make` or another build system supported by `cmake`



## Installing allocators library
To install allocators library, follow these steps:<br>
Linux and macOS:
```shell script
git clone https://github.com/hdnVrso/Allocators.git
```
Populate library targets to your project<br>
After that you need to add populated targets to your targets that is using this library
```cmake
target_include_directories(your_target PRIVATE {allocators_SOURCE_DIR})
target_link_libraries(your_target PRIVATE allocators)
```

## Running tests
This project use [Google Test](https://github.com/google/googletest) for unit tests in this project. To run tests follow these steps:
1. Run cmake with `-D ALLOCATORS_TESTS` option
2. Build using `make` or the other build system 
3. In your build directory find executable called `Run_Allocators_Tests`
4. Execute it

## Contributing to Allocators
To contribute to Allocators, you need these steps:
1. Fork this repository
2. Create a branch 
3. Follow code style conventions
4. Make sure you have installed `clang-format` and `clang-tidy` localy
5. Use `-D ALLOCATORS_DEVELOPER` cmake option to generate `allocators_clang_tidy` and `allocators_clang_format` custom targets
6. Run `allocators_clang_format` custom target using your build system to autoformat your code to match codestyle conventions
7. Run `allocators_clang_tidy` custom target using your build system to see `clang-tidy` recomendations
8. Make a pull request

## Code style
This project follows [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
This project use `clang-format` tool to auto formatting and `calng-tidy` tool to static analysis.

## Contact
If you want to contact me you can reach me at 
* Email `hiddenstmail@gmail.com`<br>
* Telegram `@hiddenSt1` 
