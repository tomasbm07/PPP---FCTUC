# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /cygdrive/c/Users/tomas/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/tomas/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/d/UC/PPP/Aula 11"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Aula_11.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Aula_11.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Aula_11.dir/flags.make

CMakeFiles/Aula_11.dir/main.c.o: CMakeFiles/Aula_11.dir/flags.make
CMakeFiles/Aula_11.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Aula_11.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Aula_11.dir/main.c.o   -c "/cygdrive/d/UC/PPP/Aula 11/main.c"

CMakeFiles/Aula_11.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Aula_11.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/UC/PPP/Aula 11/main.c" > CMakeFiles/Aula_11.dir/main.c.i

CMakeFiles/Aula_11.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Aula_11.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/UC/PPP/Aula 11/main.c" -o CMakeFiles/Aula_11.dir/main.c.s

# Object files for target Aula_11
Aula_11_OBJECTS = \
"CMakeFiles/Aula_11.dir/main.c.o"

# External object files for target Aula_11
Aula_11_EXTERNAL_OBJECTS =

Aula_11.exe: CMakeFiles/Aula_11.dir/main.c.o
Aula_11.exe: CMakeFiles/Aula_11.dir/build.make
Aula_11.exe: CMakeFiles/Aula_11.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Aula_11.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Aula_11.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Aula_11.dir/build: Aula_11.exe

.PHONY : CMakeFiles/Aula_11.dir/build

CMakeFiles/Aula_11.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Aula_11.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Aula_11.dir/clean

CMakeFiles/Aula_11.dir/depend:
	cd "/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/d/UC/PPP/Aula 11" "/cygdrive/d/UC/PPP/Aula 11" "/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug" "/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug" "/cygdrive/d/UC/PPP/Aula 11/cmake-build-debug/CMakeFiles/Aula_11.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Aula_11.dir/depend

