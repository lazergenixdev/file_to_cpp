#define FILE_TO_CPP_IMPLEMENTATION
#include "file_to_cpp.h"
#include <stdlib.h>

#define fail(...) printf(__VA_ARGS__), exit(1)

char const* get_filename(char const* path) {
	char const* end = path;
	while(*end != 0) ++end;
	end -= 1;

	while(end > path && end[-1] != '\\' && end[-1] != '/') --end;
	return end;
}

int main(int argc, char** argv) {
	if (argc != 3)
		fail("valid usage: \"%s <Output File Path> <Input File Path>\"\n", get_filename(argv[0]));

	FILE* file = fopen(argv[2], "rb");

	if (file == NULL)
		fail("error: failed to open file \"%s\"\n", argv[2]);

	fseek(file, 0, SEEK_END);
	uint64_t mem_size = ftell(file);

	if (mem_size == 0)
		printf("warning: file is empty \"%s\"\n", argv[2]);

	void* mem = malloc(mem_size);

	fseek(file, 0, SEEK_SET);
	fread(mem, 1, mem_size, file);
	fclose(file);

	int r = ftcpp_generate_from_data(argv[1], mem, mem_size);

	free(mem);

	if (r) fail("error: failed to write to file \"%s\"\n", argv[1]);
	return 0;
}
