CXX = g++

CXXFLAGS = -std=c++20 -O3 -g

DAYS = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

all: ${DAYS}
$(DAYS):
	@echo "\nDAY $@"
	@/usr/bin/time --format="Took %E to compile." ${CXX} ${CXXFLAGS} Day\ $@/main.cpp -o Bin/day$@
	@./Bin/day$@


clean:
	rm -f Bin/*
	@echo "Removed all binaries!"