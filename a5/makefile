#TYPE:=TASK
OUTPUT:=OUTPUT

CXX = u++					# compiler
CXXFLAGS = -g -multi -O2 -std=c++11 -Wall -Wextra -MMD -D${TYPE} -D${OUTPUT} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q2tallyVotes${TYPE}.o q2voter.o q2printer.o q2main.o # list of object files for question 1 prefixed with "q1"
EXEC1 = vote

OBJECTS = ${OBJECTS1}				# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}				# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

-include ImplKind

ifeq (${IMPLKIND},${TYPE})			# same implementation type as last time ?
${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${TYPE},)					# no implementation type specified ?
# set type to previous type
TYPE=${IMPLKIND}
${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC1}
${EXEC1} :
	rm -f ImplKind
	touch q2tallyVotes.h
	sleep 1
	${MAKE} ${EXEC1} KIND="${TYPE}"
endif
endif

ImplKind :
	echo "IMPLKIND=${TYPE}" > ImplKind
	sleep 1

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplKind
