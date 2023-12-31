# file_to_cpp
Generates C++ header from a file, useful for embedding data into programs.

# How to use Generated Output
```cpp
// use with namespace
namespace vertex_shader {
// $ ./file_to_cpp shader.vert.inl shader.vert
#include "shader.vert.inl"
}

// or use with struct
struct fragment_shader {
// $ ./file_to_cpp shader.frag.inl shader.frag
#include "shader.frag.inl"
};

int main() {
	auto vs = compile_shader(vertex_shader::data, vertex_shader::size);
	auto fs = compile_shader(fragment_shader::data, fragment_shader::size);
}

```

# Compiling Source Code
Compile `main.c` with any C compiler or use `build.py` to build with `gcc`

`test.cpp` is just an example program
