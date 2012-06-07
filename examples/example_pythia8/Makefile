PROGRAM         = pythia8_pT

LIBDIRARCH      = lib/archive

CXX             = g++
CXXFLAGS        = -Wall -fPIC

LD              = g++
SOFLAGS         = -shared
CXXFLAGS        += $(shell root-config --cflags)
LIBS            = $(shell root-config --libs)

LIBS        		+= -L$(PYTHIA8)/$(LIBDIRARCH) -lpythia8 -llhapdfdummy
INCS            = -I$(PYTHIA8)/include

HDRS		= 
SRCS 		= $(HDRS:.h=.C)
OBJS		= $(HDRS:.h=.o)

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS) $(PROGRAM).C 
		$(CXX) $(CXXFLAGS) $(OBJS) $(PROGRAM).C $(LIBS) $(INCS) -o $(PROGRAM)
		@echo "$(PROGRAM) done"


clean:
		rm -f $(OBJS) core *Dict*  $(PROGRAM).o $(PROGRAM)

