PROGRAM         = combine.exe

LIBDIRARCH      = lib/archive

CXX             = g++
CXXFLAGS        = -Wall -fPIC #-ggdb

LD              = g++
SOFLAGS         = -shared -Wno-deprecated

#=========================
#### ROOT 
#=========================
CXXFLAGS        += $(shell root-config --cflags)
LIBS            = $(shell root-config --libs)
#=========================
#### FASTJET
#=========================
INCS += $(shell $(FASTJET)/bin/fastjet-config --cxxflags )
LIBS += $(shell $(FASTJET)/bin/fastjet-config --libs --plugins ) $(INCS)
#=========================
#### PYTHIA8
#=========================
#LIBS	       += -L$(PYTHIA8)/$(LIBDIRARCH) -lpythia8 -llhapdfdummy
#INCS           += -I$(PYTHIA8)/include 
#CXXFLAGS       += $(INCS)
#=========================
#### PYTHIA6
#=========================
LIBS		   += -lEG -lEGPythia6 -L$(PYTHIA6) -lPythia6
#LIBS		   += -lEG -L$(PYTHIA6) -lPythia6

HDRS =  

SRCS 		= $(HDRS:.h=.C)
OBJS		= $(HDRS:.h=.o)

PROGRAMSRC	= $(PROGRAM:.exe=.cxx)

%.o: %.cxx %.h
	$(COMPILE.C) $(OUTPUT_OPTION) $(INCS) -c $<

#%.o:	$(SRCS) $(HDRS)           
#		$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

$(PROGRAM):     $(OBJS) $(HDRS) $(PROGRAMSRC)
		$(CXX) $(CXXFLAGS) $(OBJS) $(PROGRAMSRC) $(LIBS) $(INCS) -o $(PROGRAM)
		@echo "$(PROGRAM) done"

.PHONY : clean debug

clean : 
	@echo cleaning up
	rm -f $(OBJS) core *Dict*  $(PROGRAM).o $(PROGRAM) || echo "already cleaned"

cl:  clean $(PROGRAM)

debug:
	echo $(OBJS)
