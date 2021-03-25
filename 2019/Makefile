CXX = g++

CXXFLAGS = -std=c++11 -O3

DAYS = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

$(DAYS):
	@echo "\nDAY $@"
	@/usr/bin/time --format="Took %E to compile." ${CXX} ${CXXFLAGS} Day\ $@/main.cpp -o Bin/day$@
	@millisecond-time ./Bin/day$@
all: ${DAYS}

clean:
	rm -f Bin/*
	@echo "Removed all binaries!"
	