#include "MainWindow.h"

int main(int argc, char **argv)
{
  QPEApplication sMemoApp(argc, argv);

  MainWindowWidget mainWindow(0, "mainWindow");

  sMemoApp.setMainWidget(&mainWindow);

  mainWindow.showMaximized();

  return sMemoApp.exec();
}
