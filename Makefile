CXX=g++
LFLAGS        = -m64 -std=c++11
LFLAGS2       = -std=c++11
CXXFLAGS      = -m64 -std=c++11 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
INCPATH2      = -I.
LIBS          = -lQtCore -L/usr/lib/x86_64-linux-gnu/ -lm -lQtGui
LIBS2         = -lGL -lGLU -lglut
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB
TARGET        = main draw draw2 ThreeToTwo TwoToThree

# directories
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin


all : $(BINDIR)/draw $(BINDIR)/draw2 $(BINDIR)/main

$(BINDIR)/draw:  $(OBJDIR)/draw.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/draw.o: $(SRCDIR)/draw.cpp $(SRCDIR)/ThreeToTwo.cpp $(SRCDIR)/TwoToThree.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@ $(INCPATH)

$(BINDIR)/draw2:  $(OBJDIR)/draw2.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS2)

$(OBJDIR)/draw2.o: $(SRCDIR)/draw2.cpp $(SRCDIR)/ThreeToTwo.cpp $(SRCDIR)/TwoToThree.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@ $(INCPATH2)

$(BINDIR)/main: $(SRCDIR)/main.cpp $(SRCDIR)/draw.cpp $(SRCDIR)/draw2.cpp $(SRCDIR)/ThreeToTwo.cpp $(SRCDIR)/TwoToThree.cpp
	g++ -o main $(SRCDIR)/main.cpp



.PHONY: clean

clean: 
	rm -f *.o $(TARGET)
	rm -r $(OBJDIR)/*
