# Makefile for regex to graphviz project

CPP = g++
CPPFLAGS = -Wall -std=c++20
FLEXCPP = flexc++
BISONCPP = bisonc++
OBJS = lex.o parse.o main.o
BASE = regex

all: $(BASE)

flexcpp: # lex.cc
	$(FLEXCPP) scanner.l

bisoncpp: # parse.cc
	$(BISONCPP) grammar.y

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

$(BASE): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(BASE) $(OBJS)

clean:
	rm -f $(BASE) $(OBJS)
