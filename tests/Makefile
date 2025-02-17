#====================================================
#     Variables
#====================================================
ifeq ($(OS),Windows_NT)
	SYSTEM := system_tests.exe
	UNIT := unit_tests.exe
	THREAD := threading_tests.exe
else
	SYSTEM := system_tests
	UNIT := unit_tests
	THREAD := threading_tests
endif

#====================================================
#     FLAGS
#====================================================
WARNINGS := -Wall -Wextra -pedantic
EXTRAFLAGS := -std=c++17 -MMD -MP
LDFLAGS := -pthread

#====================================================
#     Compilation
#====================================================
.PHONY: clean all

all: bin/$(SYSTEM) bin/$(THREAD) bin/$(UNIT) clang

# System tests
bin/$(SYSTEM): system_tests.o
	g++ system_tests.o -o $(SYSTEM)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv *.d obj
	@ mv system_tests bin

system_tests.o: system_tests.cpp
	g++ -c system_tests.cpp $(EXTRAFLAGS) $(WARNINGS) 

# Threading tests
bin/$(THREAD): threading_tests.o
	g++ threading_tests.o -o $(THREAD) $(LDFLAGS)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv *.d obj
	@ mv threading_tests bin

threading_tests.o: threading_tests.cpp
	g++ -c threading_tests.cpp $(EXTRAFLAGS) $(WARNINGS) 

# Unit tests
bin/$(UNIT): unit_tests.o
	g++ unit_tests.o -o $(UNIT)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv *.d obj
	@ mv unit_tests bin

unit_tests.o: unit_tests.cpp
	g++ -c unit_tests.cpp $(EXTRAFLAGS) $(WARNINGS) 

# Clang tests
clang:
	clang++ -c system_tests.cpp $(EXTRAFLAGS) $(WARNINGS) 
	@ mv *.o obj
	@ mv *.d obj

# Clean
clean:
	rm -rf obj bin *.o *d