from os import system
from sys import argv

def cmd(command_string: str):
	r = system(command_string)
	if r != 0:
		print("error: command failed")
		exit(1)

OUTPUT = "file_to_cpp.exe"

test = False
optimize = 0
compiler = 0

for arg in argv[1:]:
	if arg == "-O":
		optimize = 2
	elif arg == "win32":
		compiler = 1
	elif arg == "test":
		test = True

if test:
	cmd(f"g++ test.cpp -o test.exe")
	exit(0)

if compiler == 0:
	cmd(f"gcc main.c -O{optimize} -o {OUTPUT}")

# https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
elif compiler == 1:
	if optimize == 0: optimize = 'd';
	cmd(f"cl main.c /O{optimize} /nologo /std:c11 /MT /Fe:{OUTPUT}")
