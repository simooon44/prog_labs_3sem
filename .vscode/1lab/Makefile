CXX = g++
CXXFLAGS = -I. -I../googletest/include -I../googletest

all: app.exe test.exe

app.exe: obj obj/main.o obj/Fraction.o
	$(CXX) obj/main.o obj/Fraction.o -o app.exe

test.exe: obj obj/fraction_tests.o obj/Fraction.o obj/gtest-all.o
	$(CXX) obj/fraction_tests.o obj/Fraction.o obj/gtest-all.o -o test.exe

obj:
	mkdir obj

obj/Fraction.o: Fraction.cpp Fraction.h
	$(CXX) $(CXXFLAGS) -c Fraction.cpp -o obj/Fraction.o

obj/main.o: main.cpp Fraction.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o obj/main.o

obj/fraction_tests.o: fraction_tests.cpp Fraction.h
	$(CXX) $(CXXFLAGS) -c fraction_tests.cpp -o obj/fraction_tests.o

obj/gtest-all.o: ../googletest/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) -c ../googletest/src/gtest-all.cc -o obj/gtest-all.o

run: app.exe
	.\app.exe

test: test.exe
	.\test.exe

clean:
	rmdir /s /q obj
	del /f /q app.exe test.exe
