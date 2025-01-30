#include <qpe/qpeapplication.h>
#include <qpe/qpemenubar.h>
#include <qmainwindow.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qdialog.h>
#include <qpixmap.h>

class MainWindowWidget: public QMainWindow
{
  Q_OBJECT

public:
  QListBox *listMemos;
  QComboBox *comboCategories;
  QDir fileList;

  MainWindowWidget(QWidget *parent=0, const char *name=0);

public slots:
  void NewMemo();
  void OpenMemo();
  void DeleteMemo();
  void ChangeCategory();
  void MenuMemoNew();
  void MenuMemoOpen();
  void MenuMemoDelete();
  void MenuHelpAbout();
  void MenuHelpAboutQt();
  void MenuOptionsSettings();
  void MenuOptionsCategories();

private:
  void EditMemo(QString filename, int create);
  void RefreshList(QListBox *list);
  int  selected;
};
