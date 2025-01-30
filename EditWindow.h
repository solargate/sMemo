#include <qwidget.h>
#include <qdialog.h>
#include <qlayout.h>
#include <qmultilineedit.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qcombobox.h>
#include <qpushbutton.h>

class EditWindowWidget : public QDialog
{
  Q_OBJECT

public:
  QString fileName;
  QComboBox *comboCategories;
  unsigned int catIndex;

  EditWindowWidget::EditWindowWidget(QWidget* parent=0, const char* name=0, bool modal=FALSE, WFlags fl=0);

  void LoadMemo();
  void SaveMemo();
  void RefreshWindow();

public slots:
  void PressedOk();
  void PressedCancel();
  void ChangeCategory();

private:
  QMultiLineEdit *editArea;
};
