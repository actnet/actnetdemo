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
include src/CMakeFiles/weiboimporter.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/weiboimporter.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/weiboimporter.dir/flags.make

src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o: src/CMakeFiles/weiboimporter.dir/flags.make
src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o: ../src/weiboimporter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedemo/backend/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o"
	cd /home/yecao/newsae/sae/saedemo/backend/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o -c /home/yecao/newsae/sae/saedemo/backend/src/weiboimporter.cpp

src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/weiboimporter.dir/weiboimporter.cpp.i"
	cd /home/yecao/newsae/sae/saedemo/backend/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedemo/backend/src/weiboimporter.cpp > CMakeFiles/weiboimporter.dir/weiboimporter.cpp.i

src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/weiboimporter.dir/weiboimporter.cpp.s"
	cd /home/yecao/newsae/sae/saedemo/backend/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedemo/backend/src/weiboimporter.cpp -o CMakeFiles/weiboimporter.dir/weiboimporter.cpp.s

src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.requires:
.PHONY : src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.requires

src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.provides: src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/weiboimporter.dir/build.make src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.provides.build
.PHONY : src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.provides

src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.provides.build: src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o

# Object files for target weiboimporter
weiboimporter_OBJECTS = \
"CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o"

# External object files for target weiboimporter
weiboimporter_EXTERNAL_OBJECTS =

weiboimporter: src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o
weiboimporter: saedb/storage/libmgraph.a
weiboimporter: saedb/storage/libmmap_file.a
weiboimporter: src/CMakeFiles/weiboimporter.dir/build.make
weiboimporter: src/CMakeFiles/weiboimporter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../weiboimporter"
	cd /home/yecao/newsae/sae/saedemo/backend/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/weiboimporter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/weiboimporter.dir/build: weiboimporter
.PHONY : src/CMakeFiles/weiboimporter.dir/build

src/CMakeFiles/weiboimporter.dir/requires: src/CMakeFiles/weiboimporter.dir/weiboimporter.cpp.o.requires
.PHONY : src/CMakeFiles/weiboimporter.dir/requires

src/CMakeFiles/weiboimporter.dir/clean:
	cd /home/yecao/newsae/sae/saedemo/backend/build/src && $(CMAKE_COMMAND) -P CMakeFiles/weiboimporter.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/weiboimporter.dir/clean

src/CMakeFiles/weiboimporter.dir/depend:
	cd /home/yecao/newsae/sae/saedemo/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yecao/newsae/sae/saedemo/backend /home/yecao/newsae/sae/saedemo/backend/src /home/yecao/newsae/sae/saedemo/backend/build /home/yecao/newsae/sae/saedemo/backend/build/src /home/yecao/newsae/sae/saedemo/backend/build/src/CMakeFiles/weiboimporter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/weiboimporter.dir/depend

