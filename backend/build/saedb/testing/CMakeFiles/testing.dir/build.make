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
include saedb/testing/CMakeFiles/testing.dir/depend.make

# Include the progress variables for this target.
include saedb/testing/CMakeFiles/testing.dir/progress.make

# Include the compile flags for this target's objects.
include saedb/testing/CMakeFiles/testing.dir/flags.make

saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o: saedb/testing/CMakeFiles/testing.dir/flags.make
saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o: /home/yecao/newsae/sae/saedb/testing/testharness.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedemo/backend/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/testing.dir/testharness.cpp.o -c /home/yecao/newsae/sae/saedb/testing/testharness.cpp

saedb/testing/CMakeFiles/testing.dir/testharness.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing.dir/testharness.cpp.i"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedb/testing/testharness.cpp > CMakeFiles/testing.dir/testharness.cpp.i

saedb/testing/CMakeFiles/testing.dir/testharness.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing.dir/testharness.cpp.s"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedb/testing/testharness.cpp -o CMakeFiles/testing.dir/testharness.cpp.s

saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.requires:
.PHONY : saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.requires

saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.provides: saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.requires
	$(MAKE) -f saedb/testing/CMakeFiles/testing.dir/build.make saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.provides.build
.PHONY : saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.provides

saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.provides.build: saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o

# Object files for target testing
testing_OBJECTS = \
"CMakeFiles/testing.dir/testharness.cpp.o"

# External object files for target testing
testing_EXTERNAL_OBJECTS =

saedb/testing/libtesting.a: saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o
saedb/testing/libtesting.a: saedb/testing/CMakeFiles/testing.dir/build.make
saedb/testing/libtesting.a: saedb/testing/CMakeFiles/testing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libtesting.a"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing && $(CMAKE_COMMAND) -P CMakeFiles/testing.dir/cmake_clean_target.cmake
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
saedb/testing/CMakeFiles/testing.dir/build: saedb/testing/libtesting.a
.PHONY : saedb/testing/CMakeFiles/testing.dir/build

saedb/testing/CMakeFiles/testing.dir/requires: saedb/testing/CMakeFiles/testing.dir/testharness.cpp.o.requires
.PHONY : saedb/testing/CMakeFiles/testing.dir/requires

saedb/testing/CMakeFiles/testing.dir/clean:
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing && $(CMAKE_COMMAND) -P CMakeFiles/testing.dir/cmake_clean.cmake
.PHONY : saedb/testing/CMakeFiles/testing.dir/clean

saedb/testing/CMakeFiles/testing.dir/depend:
	cd /home/yecao/newsae/sae/saedemo/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yecao/newsae/sae/saedemo/backend /home/yecao/newsae/sae/saedb/testing /home/yecao/newsae/sae/saedemo/backend/build /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing /home/yecao/newsae/sae/saedemo/backend/build/saedb/testing/CMakeFiles/testing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : saedb/testing/CMakeFiles/testing.dir/depend

