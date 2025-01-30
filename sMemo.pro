TEMPLATE = app
#CONFIG   = qt warn_on debug
CONFIG   = qt warn_on release
HEADERS  = MainWindow.h EditWindow.h CatDialog.h CatRename.h CatConfig.h Links.h
SOURCES  = MainWindow.cpp EditWindow.cpp CatDialog.cpp CatRename.cpp CatConfig.cpp Links.cpp sMemo.cpp
LIBS    += -lqpe
TARGET   = sMemo

