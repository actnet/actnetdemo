# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yecao/newsae/sae/saedemo/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yecao/newsae/sae/saedemo/backend/build

# Include any dependencies generated for this target.
include saedb/storage/CMakeFiles/mmap_file.dir/depend.make

# Include the progress variables for this target.
include saedb/storage/CMakeFiles/mmap_file.dir/progress.make

# Include the compile flags for this target's objects.
include saedb/storage/CMakeFiles/mmap_file.dir/flags.make

saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o: saedb/storage/CMakeFiles/mmap_file.dir/flags.make
saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o: /home/yecao/newsae/sae/saedb/storage/mmap_file_posix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedemo/backend/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o -c /home/yecao/newsae/sae/saedb/storage/mmap_file_posix.cpp

saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.i"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedb/storage/mmap_file_posix.cpp > CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.i

saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.s"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedb/storage/mmap_file_posix.cpp -o CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.s

saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.requires:
.PHONY : saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.requires

saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.provides: saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.requires
	$(MAKE) -f saedb/storage/CMakeFiles/mmap_file.dir/build.make saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.provides.build
.PHONY : saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.provides

saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.provides.build: saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o

# Object files for target mmap_file
mmap_file_OBJECTS = \
"CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o"

# External object files for target mmap_file
mmap_file_EXTERNAL_OBJECTS =

saedb/storage/libmmap_file.a: saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o
saedb/storage/libmmap_file.a: saedb/storage/CMakeFiles/mmap_file.dir/build.make
saedb/storage/libmmap_file.a: saedb/storage/CMakeFiles/mmap_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libmmap_file.a"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage && $(CMAKE_COMMAND) -P CMakeFiles/mmap_file.dir/cmake_clean_target.cmake
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mmap_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
saedb/storage/CMakeFiles/mmap_file.dir/build: saedb/storage/libmmap_file.a
.PHONY : saedb/storage/CMakeFiles/mmap_file.dir/build

saedb/storage/CMakeFiles/mmap_file.dir/requires: saedb/storage/CMakeFiles/mmap_file.dir/mmap_file_posix.cpp.o.requires
.PHONY : saedb/storage/CMakeFiles/mmap_file.dir/requires

saedb/storage/CMakeFiles/mmap_file.dir/clean:
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage && $(CMAKE_COMMAND) -P CMakeFiles/mmap_file.dir/cmake_clean.cmake
.PHONY : saedb/storage/CMakeFiles/mmap_file.dir/clean

saedb/storage/CMakeFiles/mmap_file.dir/depend:
	cd /home/yecao/newsae/sae/saedemo/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yecao/newsae/sae/saedemo/backend /home/yecao/newsae/sae/saedb/storage /home/yecao/newsae/sae/saedemo/backend/build /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage /home/yecao/newsae/sae/saedemo/backend/build/saedb/storage/CMakeFiles/mmap_file.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : saedb/storage/CMakeFiles/mmap_file.dir/depend

