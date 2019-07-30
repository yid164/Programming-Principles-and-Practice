# Makefile for Cmpt214 Lab 10
#  Author: Tony Kusalik

CFLAGS = -Wall -Wextra -g
CXXFLAGS = $(CFLAGS)

# Example of using a conditional and an environment variable
# within a makefile.  Here we use a unique tar
# command appropriate to each of two different systems.
# This definition is for illustrative purposes,
# so Cmpt214 students don't actually have to use it or
# modify it in the lab.
ifeq "$(OSTYPE)" "linux"
  TARCMD = tar
else ifeq "$(OSTYPE)" "darwin"
  TARCMD = /usr/local/bin/gnutar
endif

TAR = Lab10Files.tar
FILES_IN_DOT_TAR = power.cc makefile infile.txt 

.PHONY: clean tar sanitize

power: power.cc

buggy_power.o: power.cc
	g++ -g -c -o buggy_power.o power.cc

tar: $(TAR)

# Example of using a makefile to build something other than an
# executable program from C/C++ source, as well as having
# multiple actions in a rule.  This rule is for illustrative purposes
# only, Cmpt214 students don't actually have to use it or
# modify it in the lab.
$(TAR): $(FILES_IN_DOT_TAR)
	cp makefile.org makefile
	cp power.org.cc power.cc
ifeq "$(OSTYPE)" "darwin"
	xattr -c $(FILES_IN_DOT_TAR)
endif
	$(TARCMD) -cvf $(TAR) $(FILES_IN_DOT_TAR)

clean:
	rm -f *.o core.*

sanitize: clean
	rm -f power factorial $(TAR)

