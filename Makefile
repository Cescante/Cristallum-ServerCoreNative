# Cristallum Server Core Native Makefile

################# VARIABLE DEFINITIONS #################

DOC	= doxygen
CC = clang++

# Paths 
PROJROOT = $(PWD)
DATAPROVIDER = DataProvider

DEP_SUFFIX = dep

###################### Libraries! ######################
# SIMULATOR_LIBS =

################# DETERMINATION OF INCLUSION BEHAVIORS #####################
ifeq (0,$(words $(filter %clean,$(MAKECMDGOALS))))
DO_INCLUDE_DEPS=1
endif

#################### BUILD PARAMETER VARIABLES ################

CFLAGS = -Wall -Werror -m64 -std=c++11 -stdlib=libc++
PROG = CristallumServerCore

INCLUDES = -I$(PROJROOT)

ROOT_OBJ = CristallumServerCore.o
OBJS = $(DATAPROVIDER)/DataProvider.o 
ALL_OBJS = $(OBJS:%=./%) 
ALL_OBJS_DEPS = $(ALL_OBJS:%.o=%.$(DEP_SUFFIX))

ALL_OBJS += $(ROOT_OBJ)

CTAGS = ctags -xR >tags
DEPEND = makedepend $(CFLAGS)

###################### Main Targets ###########################
$(PROG): $(ALL_OBJS)
	$(CC) $(CFLAGS) -o $ $@ $(ALL_OBJS)

%.$(DEP_SUFFIX): %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT $(<:.cpp=.o) $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

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

html_doc:
	$(DOC) doxygen.conf

########### DEPENDENCY FILE INCLUSION ############
ifeq (1,$(DO_INCLUDE_DEPS))
ifneq (,$(ALL_OBJS))
	-include $(ALL_OBJS_DEPS)
endif
endif
