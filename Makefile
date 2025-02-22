#############################################################################
# Makefile for building sMemo
# Generated by tmake at 20:13, 2006/12/22
#     Project: sMemo
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	gcc
CXX	=	g++
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG
CXXFLAGS=	-pipe -DQT_QWS_SL3000 -DQT_QWS_CUSTOM -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG
INCPATH	=	-I$(QTDIR)/include/Qtopia
LINK	=	gcc
LFLAGS	=	
LIBS	=	$(SUBLIBS) -L$(QTDIR)/lib -lqpe -lqte -lqpe
MOC	=	moc
UIC	=	

TAR	=	tar -cf
GZIP	=	gzip -9f

####### Files

HEADERS =	MainWindow.h \
		EditWindow.h \
		CatDialog.h \
		CatRename.h \
		CatConfig.h \
		Links.h
SOURCES =	MainWindow.cpp \
		EditWindow.cpp \
		CatDialog.cpp \
		CatRename.cpp \
		CatConfig.cpp \
		Links.cpp \
		sMemo.cpp
OBJECTS =	MainWindow.o \
		EditWindow.o \
		CatDialog.o \
		CatRename.o \
		CatConfig.o \
		Links.o \
		sMemo.o
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	moc_MainWindow.cpp \
		moc_EditWindow.cpp \
		moc_CatDialog.cpp \
		moc_CatRename.cpp
OBJMOC	=	moc_MainWindow.o \
		moc_EditWindow.o \
		moc_CatDialog.o \
		moc_CatRename.o
DIST	=	
TARGET	=	sMemo
INTERFACE_DECL_PATH = .

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules


all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

moc: $(SRCMOC)

tmake: Makefile

Makefile: sMemo.pro
	tmake sMemo.pro -o Makefile

dist:
	$(TAR) sMemo.tar sMemo.pro $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) sMemo.tar

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core

####### Sub-libraries


###### Combined headers


####### Compile

MainWindow.o: MainWindow.cpp \
		MainWindow.h \
		EditWindow.h \
		CatDialog.h \
		CatConfig.h \
		Links.h

EditWindow.o: EditWindow.cpp \
		EditWindow.h \
		CatConfig.h

CatDialog.o: CatDialog.cpp \
		CatDialog.h \
		CatRename.h \
		CatConfig.h

CatRename.o: CatRename.cpp \
		CatRename.h

CatConfig.o: CatConfig.cpp \
		CatConfig.h

Links.o: Links.cpp \
		Links.h \
		CatConfig.h

sMemo.o: sMemo.cpp \
		MainWindow.h

moc_MainWindow.o: moc_MainWindow.cpp \
		MainWindow.h

moc_EditWindow.o: moc_EditWindow.cpp \
		EditWindow.h

moc_CatDialog.o: moc_CatDialog.cpp \
		CatDialog.h

moc_CatRename.o: moc_CatRename.cpp \
		CatRename.h

moc_MainWindow.cpp: MainWindow.h
	$(MOC) MainWindow.h -o moc_MainWindow.cpp

moc_EditWindow.cpp: EditWindow.h
	$(MOC) EditWindow.h -o moc_EditWindow.cpp

moc_CatDialog.cpp: CatDialog.h
	$(MOC) CatDialog.h -o moc_CatDialog.cpp

moc_CatRename.cpp: CatRename.h
	$(MOC) CatRename.h -o moc_CatRename.cpp

