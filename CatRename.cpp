#include "CatRename.h"
//============================================================================
CategoryRename::CategoryRename(QWidget *parent, const char *name, bool modal, WFlags fl, QString text): QDialog(parent, name, modal, fl)
{
  setCaption("Rename");

  QGridLayout *layout = new QGridLayout(this, 1, 1, 10, 10);

  editCat = new QLineEdit(text, this, 0);
  editCat->setSelection(0, text.length());
  layout->addWidget(editCat, 0, 0);
}
//============================================================================
QString CategoryRename::GetText()
{
  return editCat->text();
}

