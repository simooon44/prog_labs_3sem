CXX = g++
CXXFLAGS = -I. -I../googletest/include -I../googletest

all: app.exe test.exe

app.exe: obj obj/Fraction.o obj/EvaluatedFraction.o obj/MixedFraction.o obj/main.o
	$(CXX) obj/Fraction.o obj/EvaluatedFraction.o obj/MixedFraction.o obj/main.o -o app.exe

test.exe: obj obj/fraction_tests.o obj/Fraction.o obj/EvaluatedFraction.o obj/MixedFraction.o obj/gtest-all.o
	$(CXX) obj/fraction_tests.o obj/Fraction.o obj/EvaluatedFraction.o obj/MixedFraction.o obj/gtest-all.o -o test.exe

obj:
	mkdir obj

obj/Fraction.o: Fraction.cpp Fraction.h
	$(CXX) $(CXXFLAGS) -c Fraction.cpp -o obj/Fraction.o

obj/EvaluatedFraction.o: EvaluatedFraction.cpp EvaluatedFraction.h Fraction.h
	$(CXX) $(CXXFLAGS) -c EvaluatedFraction.cpp -o obj/EvaluatedFraction.o

obj/MixedFraction.o: MixedFraction.cpp MixedFraction.h Fraction.h
	$(CXX) $(CXXFLAGS) -c MixedFraction.cpp -o obj/MixedFraction.o

obj/main.o: main.cpp Fraction.h EvaluatedFraction.h MixedFraction.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o obj/main.o

obj/fraction_tests.o: fraction_tests.cpp Fraction.h EvaluatedFraction.h MixedFraction.h
	$(CXX) $(CXXFLAGS) -c fraction_tests.cpp -o obj/fraction_tests.o

obj/gtest-all.o: ../googletest/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) -c ../googletest/src/gtest-all.cc -o obj/gtest-all.o

run: app.exe
	./app.exe

test: test.exe
	./test.exe

test1: test.exe
	./test.exe --gtest_filter=FractionTest.*

test2: test.exe
	./test.exe --gtest_filter=FractionTest2.*

test3: test.exe
	./test.exe --gtest_filter=FractionTest3.*

test4: test.exe
	./test.exe --gtest_filter=FractionTest4.*

clean:
	rm -rf obj
	rm -f test.exe app.exe
	rm -f fractions.bin
	rm -f fractions.txt

clean_files:
	rm -f fractions.bin
	rm -f fractions.txt