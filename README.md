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
After that you need to add headers to ```cmake include directories```
```cmake
include_directories(${Allocators_SOURCE_DIR}/include)
```

### Running tests
We use googletest for unit tests in this project. To run test follow these steps:

## Contributing to Allocators
To contribute to Allocators, you need these steps:
1. Fork this repository
2. Create a branch 
3. Follow code style conventions.

### Code style
We are using [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
We using clang-format tool to auto formatting. 

## Contact
If you want to contact me you can reach me at ```hiddenstmail@gmail.com```
