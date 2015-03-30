# Cristallum Server Core Native MAkefile

################# VARIABLE DEFINITIONS #################

DOC	= doxygen
CC = clang++
PROJROOT = $(PWD)

# PATHS

###################### Libraries! ######################
# SIMULATOR_LIBS =

############################ Includes #########################

#################### BUILD PARAMETER VARIABLES ################

CFLAGS = -Wall -Werror -m64 -std=c++11 -stdlib=libc++
PROG = CristallumServerCore
OBJS = CristallumServerCore.o
SRCS = CristallumServerCore.cpp

CTAGS = ctags -xR >tags
DEPEND = makedepend $(CFLAGS)

###################### Main Targets ###########################
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $ $@ $(OBJS)

CristallumServerCore.o: CristallumServerCore.cpp
	$(CC) $(CFLAGS) -c CristallumServerCore.cpp -o $@

###################### Target Specific Variables #######################
debug: CFLAGS += -DDEBUG -g -O0
debug: $(PROG)

ship: CFLAGS += -O2
ship: $(PROG)


###################### CLEANING RULES #########################
.PHONY: clean

clean: 
	rm -f $(OBJS) $(PROG)

###################### MISC Targets ###########################
tags: $(SRCS)
	${CTAGS} $(SRCS)

depend: $(SRCS)
	$(DEPEND) $(SRCS)

html_doc:
	$(DOC) doxygen.conf

