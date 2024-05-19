# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic -Iheader

# Phony target
.PHONY : all
all : main test


# Compile the source files and links them to create the executable 'main' and 'test'
main : main.cpp librarian.o person.o member.o book.o date.o validation.o librarian_functions.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test: test.cpp member.o librarian.o person.o date.o book.o librarian_functions.o validation.o
	$(CXX) $(CXXFLAGS) -o $@ $^


# Compilation rules for individual object files

librarian.o : cpp/librarian.cpp header/librarian_functions.h 
	$(CXX) $(CXXFLAGS) -c  $<
person.o : cpp/person.cpp header/person.h
	$(CXX) $(CXXFLAGS) -c  $<
member.o : cpp/member.cpp header/member.h 
	$(CXX) $(CXXFLAGS) -c  $<
book.o : cpp/book.cpp header/book.h 
	$(CXX) $(CXXFLAGS) -c  $<
date.o : cpp/date.cpp header/date.h
	$(CXX) $(CXXFLAGS) -c  $<
validation.o : cpp/validation.cpp header/validation.h
	$(CXX) $(CXXFLAGS) -c  $<
librarian_functions.o: cpp/librarian_functions.cpp header/librarian_functions.h
	$(CXX) $(CXXFLAGS) -c  $<

# Clean-up rule to remove object files and the executable files
.PHONY : clean
clean :
	$(RM) *.o
	$(RM) main test