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
include saedb/external/gflags/CMakeFiles/gflags.dir/depend.make

# Include the progress variables for this target.
include saedb/external/gflags/CMakeFiles/gflags.dir/progress.make

# Include the compile flags for this target's objects.
include saedb/external/gflags/CMakeFiles/gflags.dir/flags.make

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o: saedb/external/gflags/CMakeFiles/gflags.dir/flags.make
saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o: /home/yecao/newsae/sae/saedb/external/gflags/src/gflags.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedemo/backend/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gflags.dir/src/gflags.cc.o -c /home/yecao/newsae/sae/saedb/external/gflags/src/gflags.cc

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gflags.dir/src/gflags.cc.i"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedb/external/gflags/src/gflags.cc > CMakeFiles/gflags.dir/src/gflags.cc.i

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gflags.dir/src/gflags.cc.s"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedb/external/gflags/src/gflags.cc -o CMakeFiles/gflags.dir/src/gflags.cc.s

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.requires:
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.requires

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.provides: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.requires
	$(MAKE) -f saedb/external/gflags/CMakeFiles/gflags.dir/build.make saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.provides.build
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.provides

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.provides.build: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o: saedb/external/gflags/CMakeFiles/gflags.dir/flags.make
saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o: /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_reporting.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedemo/backend/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gflags.dir/src/gflags_reporting.cc.o -c /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_reporting.cc

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gflags.dir/src/gflags_reporting.cc.i"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_reporting.cc > CMakeFiles/gflags.dir/src/gflags_reporting.cc.i

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gflags.dir/src/gflags_reporting.cc.s"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_reporting.cc -o CMakeFiles/gflags.dir/src/gflags_reporting.cc.s

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.requires:
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.requires

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.provides: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.requires
	$(MAKE) -f saedb/external/gflags/CMakeFiles/gflags.dir/build.make saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.provides.build
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.provides

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.provides.build: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o: saedb/external/gflags/CMakeFiles/gflags.dir/flags.make
saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o: /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_completions.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedemo/backend/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gflags.dir/src/gflags_completions.cc.o -c /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_completions.cc

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gflags.dir/src/gflags_completions.cc.i"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_completions.cc > CMakeFiles/gflags.dir/src/gflags_completions.cc.i

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gflags.dir/src/gflags_completions.cc.s"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedb/external/gflags/src/gflags_completions.cc -o CMakeFiles/gflags.dir/src/gflags_completions.cc.s

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.requires:
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.requires

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.provides: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.requires
	$(MAKE) -f saedb/external/gflags/CMakeFiles/gflags.dir/build.make saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.provides.build
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.provides

saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.provides.build: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o

# Object files for target gflags
gflags_OBJECTS = \
"CMakeFiles/gflags.dir/src/gflags.cc.o" \
"CMakeFiles/gflags.dir/src/gflags_reporting.cc.o" \
"CMakeFiles/gflags.dir/src/gflags_completions.cc.o"

# External object files for target gflags
gflags_EXTERNAL_OBJECTS =

saedb/external/gflags/lib/libgflags.a: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o
saedb/external/gflags/lib/libgflags.a: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o
saedb/external/gflags/lib/libgflags.a: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o
saedb/external/gflags/lib/libgflags.a: saedb/external/gflags/CMakeFiles/gflags.dir/build.make
saedb/external/gflags/lib/libgflags.a: saedb/external/gflags/CMakeFiles/gflags.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library lib/libgflags.a"
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && $(CMAKE_COMMAND) -P CMakeFiles/gflags.dir/cmake_clean_target.cmake
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gflags.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
saedb/external/gflags/CMakeFiles/gflags.dir/build: saedb/external/gflags/lib/libgflags.a
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/build

saedb/external/gflags/CMakeFiles/gflags.dir/requires: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags.cc.o.requires
saedb/external/gflags/CMakeFiles/gflags.dir/requires: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_reporting.cc.o.requires
saedb/external/gflags/CMakeFiles/gflags.dir/requires: saedb/external/gflags/CMakeFiles/gflags.dir/src/gflags_completions.cc.o.requires
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/requires

saedb/external/gflags/CMakeFiles/gflags.dir/clean:
	cd /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags && $(CMAKE_COMMAND) -P CMakeFiles/gflags.dir/cmake_clean.cmake
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/clean

saedb/external/gflags/CMakeFiles/gflags.dir/depend:
	cd /home/yecao/newsae/sae/saedemo/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yecao/newsae/sae/saedemo/backend /home/yecao/newsae/sae/saedb/external/gflags /home/yecao/newsae/sae/saedemo/backend/build /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags /home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags/CMakeFiles/gflags.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : saedb/external/gflags/CMakeFiles/gflags.dir/depend

