# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/marianoaponte/Documents/Uni/ProgettoCalcolo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProgettoCalcolo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProgettoCalcolo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProgettoCalcolo.dir/flags.make

CMakeFiles/ProgettoCalcolo.dir/main.c.o: CMakeFiles/ProgettoCalcolo.dir/flags.make
CMakeFiles/ProgettoCalcolo.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ProgettoCalcolo.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProgettoCalcolo.dir/main.c.o -c /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/main.c

CMakeFiles/ProgettoCalcolo.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProgettoCalcolo.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/main.c > CMakeFiles/ProgettoCalcolo.dir/main.c.i

CMakeFiles/ProgettoCalcolo.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProgettoCalcolo.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/main.c -o CMakeFiles/ProgettoCalcolo.dir/main.c.s

CMakeFiles/ProgettoCalcolo.dir/utils.c.o: CMakeFiles/ProgettoCalcolo.dir/flags.make
CMakeFiles/ProgettoCalcolo.dir/utils.c.o: ../utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ProgettoCalcolo.dir/utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProgettoCalcolo.dir/utils.c.o -c /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/utils.c

CMakeFiles/ProgettoCalcolo.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProgettoCalcolo.dir/utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/utils.c > CMakeFiles/ProgettoCalcolo.dir/utils.c.i

CMakeFiles/ProgettoCalcolo.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProgettoCalcolo.dir/utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/utils.c -o CMakeFiles/ProgettoCalcolo.dir/utils.c.s

# Object files for target ProgettoCalcolo
ProgettoCalcolo_OBJECTS = \
"CMakeFiles/ProgettoCalcolo.dir/main.c.o" \
"CMakeFiles/ProgettoCalcolo.dir/utils.c.o"

# External object files for target ProgettoCalcolo
ProgettoCalcolo_EXTERNAL_OBJECTS =

ProgettoCalcolo: CMakeFiles/ProgettoCalcolo.dir/main.c.o
ProgettoCalcolo: CMakeFiles/ProgettoCalcolo.dir/utils.c.o
ProgettoCalcolo: CMakeFiles/ProgettoCalcolo.dir/build.make
ProgettoCalcolo: CMakeFiles/ProgettoCalcolo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ProgettoCalcolo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProgettoCalcolo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProgettoCalcolo.dir/build: ProgettoCalcolo

.PHONY : CMakeFiles/ProgettoCalcolo.dir/build

CMakeFiles/ProgettoCalcolo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProgettoCalcolo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProgettoCalcolo.dir/clean

CMakeFiles/ProgettoCalcolo.dir/depend:
	cd /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/marianoaponte/Documents/Uni/ProgettoCalcolo /Users/marianoaponte/Documents/Uni/ProgettoCalcolo /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug /Users/marianoaponte/Documents/Uni/ProgettoCalcolo/cmake-build-debug/CMakeFiles/ProgettoCalcolo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProgettoCalcolo.dir/depend

