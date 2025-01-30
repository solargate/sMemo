#include <qdialog.h>
#include <qlayout.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qtextstream.h>

class CategoriesDialog: public QDialog
{
  Q_OBJECT
  
public:
  QListBox *listCat;
  QLineEdit *editCatAdd;

  CategoriesDialog(QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags fl=0);

public slots:
  void AddCategory();
  void RenameCategory();
  void DeleteCategory();

private:
  void RefreshCategories();
};

