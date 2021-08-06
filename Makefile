
ifdef CXX
     GCC_VERSION = $(shell $(CXX) -dumpversion)                                                                                               
else
     GCC_VERSION = $(shell g++ -dumpversion)
endif

all:
	echo $(GCC_VERSION)