# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build

# Include any dependencies generated for this target.
include src/CMakeFiles/WikipediaSearch.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/WikipediaSearch.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/WikipediaSearch.dir/flags.make

src/CMakeFiles/WikipediaSearch.dir/main.cpp.o: src/CMakeFiles/WikipediaSearch.dir/flags.make
src/CMakeFiles/WikipediaSearch.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/WikipediaSearch.dir/main.cpp.o"
	cd /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WikipediaSearch.dir/main.cpp.o -c /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/src/main.cpp

src/CMakeFiles/WikipediaSearch.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WikipediaSearch.dir/main.cpp.i"
	cd /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/src/main.cpp > CMakeFiles/WikipediaSearch.dir/main.cpp.i

src/CMakeFiles/WikipediaSearch.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WikipediaSearch.dir/main.cpp.s"
	cd /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/src/main.cpp -o CMakeFiles/WikipediaSearch.dir/main.cpp.s

# Object files for target WikipediaSearch
WikipediaSearch_OBJECTS = \
"CMakeFiles/WikipediaSearch.dir/main.cpp.o"

# External object files for target WikipediaSearch
WikipediaSearch_EXTERNAL_OBJECTS =

src/WikipediaSearch: src/CMakeFiles/WikipediaSearch.dir/main.cpp.o
src/WikipediaSearch: src/CMakeFiles/WikipediaSearch.dir/build.make
src/WikipediaSearch: src/search/libsearch.a
src/WikipediaSearch: src/indexing/libindexing.a
src/WikipediaSearch: src/CMakeFiles/WikipediaSearch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WikipediaSearch"
	cd /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WikipediaSearch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/WikipediaSearch.dir/build: src/WikipediaSearch

.PHONY : src/CMakeFiles/WikipediaSearch.dir/build

src/CMakeFiles/WikipediaSearch.dir/clean:
	cd /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src && $(CMAKE_COMMAND) -P CMakeFiles/WikipediaSearch.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/WikipediaSearch.dir/clean

src/CMakeFiles/WikipediaSearch.dir/depend:
	cd /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/src /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src /home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/build/src/CMakeFiles/WikipediaSearch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/WikipediaSearch.dir/depend

