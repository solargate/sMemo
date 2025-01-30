#include <qdialog.h>
#include <qlayout.h>
#include <qlineedit.h>

class CategoryRename: public QDialog
{
  Q_OBJECT
  
public:
  QLineEdit *editCat;

  CategoryRename(QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags fl=0, QString text="");
  QString GetText();
};

