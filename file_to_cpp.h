// file_to_cpp.h - v1.0 - public domain lazergenixdev@gmail.com 2023
// Generates C++ header from a file, useful for embedding data into programs
//
// note(lazergenix):
//    I am tired of re-writing this program all the time,
//    it is time to put these binaries on Github so I have
//    a nice place to just download this whenever need it.
//
#ifndef FILE_TO_CPP_H
#define FILE_TO_CPP_H
#include <stdint.h>

int ftcpp_generate_from_data(
	char const* output_file_path,
	void* data, uint64_t size
);

#ifdef FILE_TO_CPP_IMPLEMENTATION
#include <stdio.h>
#include <memory.h>

#define FTCPP_HEADER \
"/*\n\tGenerated with file_to_cpp by lazergenixdev@gmail.com\n*/\n"

#define FTCPP_BEGIN \
"static constexpr unsigned int size = %llu;\n" \
"static constexpr unsigned int data[] = {\n"

#define ftcpp_printf(F, ...) if (fprintf(output_file, F, __VA_ARGS__) == -1) return 1
#define ftcpp_puts(S) if (fputs(S, output_file)) return 1
#define ftcpp_putc(C) if (fputc(C, output_file) != C) return 1
#define ftcpp_range(C) (int i = 0; i < (C); ++i)

char const* ftcpp_int_to_str(char* dst, uint32_t n, uint32_t* count) {
    if (n == 0) { // stupid special case
        dst[0] = '0';
        dst[1] = 0;
		++*count;
        return dst;
    }
    int i = 9;
    for (; n != 0; --i, n /= 10, ++*count) {
        dst[i] = '0' + n % 10;
    }
    return dst + i + 1;
}

int ftcpp_write_from_data(
	FILE* output_file,
	void* data, uint64_t size
) {
	ftcpp_puts(FTCPP_HEADER);
	
	if (size != 0) {
		ftcpp_printf(FTCPP_BEGIN, size);

		int int_count = size/4;
		uint32_t* ints = data;

		char buffer[12];
		memset(buffer, 0, sizeof(buffer));

		uint32_t col_count = 0;
		for ftcpp_range(int_count) {
			ftcpp_puts(ftcpp_int_to_str(buffer, ints[i], &col_count));
			ftcpp_putc(',');

			++col_count;
			if (col_count >= 64) {
				col_count = 0;
				ftcpp_putc('\n');
			}
		}

		if (size != int_count*4) {
			uint32_t last;
			memcpy(&last, ints + int_count, size%4);
			ftcpp_printf("%u", last);
		}

		ftcpp_putc('\n');
		ftcpp_putc('}');
	}

	else ftcpp_puts(
		"static constexpr unsigned int  size = 0;\n"
		"static constexpr unsigned int* data = nullptr\n"
	);

	ftcpp_putc(';');
	ftcpp_putc('\n');

	return 0;
}

int ftcpp_generate_from_data(
	char const* output_file_path,
	void* data, uint64_t size
) {
	FILE* file = fopen(output_file_path, "wb");
	if (file == NULL) return 1;

	int r = ftcpp_write_from_data(file, data, size);

	fclose(file);
	return r;
}

#undef ftcpp_printf
#undef ftcpp_puts
#undef ftcpp_putc
#undef ftcpp_range

#endif//FILE_TO_CPP_IMPLEMENTATION
#endif//FILE_TO_CPP_HPP