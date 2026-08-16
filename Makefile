# Build configuration for the car-registration console program.
#
# The sources target Windows (they use <windows.h>, SetConsoleCP, _stricmp,
# setlocale(..., "Russian")), so on Linux we cross-compile them with the
# MinGW-w64 toolchain into a real Windows executable and run it under Wine.
#
# The source files are UTF-8 while the data files (cars.txt / registrations.txt)
# are CP1251. On a Russian Windows build MSVC compiles narrow string literals
# into the system ANSI code page (CP1251), matching the data. We reproduce that
# faithfully with -finput-charset=UTF-8 -fexec-charset=CP1251 so the whole
# program output is uniform CP1251 (correct on a CP1251 console). Convert it to
# UTF-8 for a Linux terminal with:  make run | iconv -f CP1251 -t UTF-8

CXX      := x86_64-w64-mingw32-g++
CXXFLAGS := -std=c++17 -O2 -static -static-libgcc -static-libstdc++ \
            -finput-charset=UTF-8 -fexec-charset=CP1251
SRC      := main.cpp file_io.cpp search_by_field.cpp search_core.cpp export_all.cpp
TARGET   := program.exe

.PHONY: all run clean

all: $(TARGET) regs.txt

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# The program reads its registration data from regs.txt (see Text::FILE_REGS),
# while the repository ships the same data as registrations.txt. Derive the
# file the program expects from the shipped source of truth.
regs.txt: registrations.txt
	cp registrations.txt regs.txt

# Run the program under Wine (interactive). Pipe through
# `iconv -f CP1251 -t UTF-8` to read the Cyrillic output on a UTF-8 terminal.
run: all
	WINEDEBUG=-all WINEDLLOVERRIDES="mscoree=d;mshtml=d" wine ./$(TARGET)

clean:
	rm -f $(TARGET) regs.txt result.txt
