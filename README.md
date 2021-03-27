# Allocators
Allocators is a tool that allows you to do efficient memory management in your project.
The main goal of this project is to provide some common memory allocation/free logic.

## Prerequisites
Before you begin, ensure you have met the following requirements:
* You have installed ```clang``` version 10 or higher
* You have installed the latest version of ```cmake```



## Installing allocators library
To install allocators library, follow these steps:<br>
Linux and macOS:
```shell script
git clone https://github.com/hdnVrso/Allocators.git
``` 
After that you need to add Allocator_targets to your targets that is using this library
```cmake
target_include_directories(your_target PRIVATE {allocators_SOURCE_DIR})
target_link_libraries(your_target PRIVATE allocators)
```

## Running tests
We use googletest for unit tests in this project. To run tests follow these steps:
1. Build project
2. In your build directory find executable called ```Run_Allocators_Tests```
3. Execute it

## Contributing to Allocators
To contribute to Allocators, you need these steps:
1. Fork this repository
2. Create a branch 
3. Follow code style conventions
4. Make a pull request

## Code style
We are using [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
We using clang-format tool to auto formatting. 

## Contact
If you want to contact me you can reach me at ```hiddenstmail@gmail.com```
