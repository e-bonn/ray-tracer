# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/fsaa.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/fsaa.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/fsaa.dir/flags.make

tests/CMakeFiles/fsaa.dir/fsaa.c.o: tests/CMakeFiles/fsaa.dir/flags.make
tests/CMakeFiles/fsaa.dir/fsaa.c.o: ../tests/fsaa.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/fsaa.dir/fsaa.c.o"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/fsaa.dir/fsaa.c.o   -c /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/tests/fsaa.c

tests/CMakeFiles/fsaa.dir/fsaa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fsaa.dir/fsaa.c.i"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/tests/fsaa.c > CMakeFiles/fsaa.dir/fsaa.c.i

tests/CMakeFiles/fsaa.dir/fsaa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fsaa.dir/fsaa.c.s"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/tests/fsaa.c -o CMakeFiles/fsaa.dir/fsaa.c.s

tests/CMakeFiles/fsaa.dir/fsaa.c.o.requires:
.PHONY : tests/CMakeFiles/fsaa.dir/fsaa.c.o.requires

tests/CMakeFiles/fsaa.dir/fsaa.c.o.provides: tests/CMakeFiles/fsaa.dir/fsaa.c.o.requires
	$(MAKE) -f tests/CMakeFiles/fsaa.dir/build.make tests/CMakeFiles/fsaa.dir/fsaa.c.o.provides.build
.PHONY : tests/CMakeFiles/fsaa.dir/fsaa.c.o.provides

tests/CMakeFiles/fsaa.dir/fsaa.c.o.provides.build: tests/CMakeFiles/fsaa.dir/fsaa.c.o

tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o: tests/CMakeFiles/fsaa.dir/flags.make
tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o: ../deps/getopt.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/fsaa.dir/__/deps/getopt.c.o   -c /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/deps/getopt.c

tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fsaa.dir/__/deps/getopt.c.i"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/deps/getopt.c > CMakeFiles/fsaa.dir/__/deps/getopt.c.i

tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fsaa.dir/__/deps/getopt.c.s"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/deps/getopt.c -o CMakeFiles/fsaa.dir/__/deps/getopt.c.s

tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.requires:
.PHONY : tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.requires

tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.provides: tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.requires
	$(MAKE) -f tests/CMakeFiles/fsaa.dir/build.make tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.provides.build
.PHONY : tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.provides

tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.provides.build: tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o

# Object files for target fsaa
fsaa_OBJECTS = \
"CMakeFiles/fsaa.dir/fsaa.c.o" \
"CMakeFiles/fsaa.dir/__/deps/getopt.c.o"

# External object files for target fsaa
fsaa_EXTERNAL_OBJECTS =

tests/fsaa: tests/CMakeFiles/fsaa.dir/fsaa.c.o
tests/fsaa: tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o
tests/fsaa: tests/CMakeFiles/fsaa.dir/build.make
tests/fsaa: src/libglfw3.a
tests/fsaa: /usr/lib/x86_64-linux-gnu/libX11.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libXrandr.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libXinerama.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libXi.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/librt.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libm.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libXcursor.so
tests/fsaa: /usr/lib/x86_64-linux-gnu/libGL.so
tests/fsaa: tests/CMakeFiles/fsaa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable fsaa"
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fsaa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/fsaa.dir/build: tests/fsaa
.PHONY : tests/CMakeFiles/fsaa.dir/build

tests/CMakeFiles/fsaa.dir/requires: tests/CMakeFiles/fsaa.dir/fsaa.c.o.requires
tests/CMakeFiles/fsaa.dir/requires: tests/CMakeFiles/fsaa.dir/__/deps/getopt.c.o.requires
.PHONY : tests/CMakeFiles/fsaa.dir/requires

tests/CMakeFiles/fsaa.dir/clean:
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/fsaa.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/fsaa.dir/clean

tests/CMakeFiles/fsaa.dir/depend:
	cd /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1 /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/tests /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests /home/ericbonn/Documents/uni/w16/cs488/a0/cs488/shared/glfw-3.1.1/build/tests/CMakeFiles/fsaa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/fsaa.dir/depend

