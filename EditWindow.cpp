#include "EditWindow.h"
#include "CatConfig.h"
//============================================================================
EditWindowWidget::EditWindowWidget(QWidget* parent, const char* name, bool modal, WFlags fl ): QDialog(parent, name, modal, fl)
{
  setCaption("Edit memo");

  QGridLayout *gridLayout = new QGridLayout(this, 2, 3, 5, 5);
  editArea = new QMultiLineEdit(this, "editArea");
  gridLayout->addMultiCellWidget(editArea, 0, 0, 0, 2);

  QPushButton *btnOk = new QPushButton("OK", this, "btnOk");
  gridLayout->addWidget(btnOk, 1, 0);
  QPushButton *btnCancel = new QPushButton("Cancel", this, "btnCancel");
  gridLayout->addWidget(btnCancel, 1, 1);

  comboCategories = new QComboBox(this, "comboCategories");
  gridLayout->addWidget(comboCategories, 1, 2);

  RefreshWindow();
  
  showMaximized();

  QObject::connect(btnOk, SIGNAL(clicked()), this, SLOT(PressedOk()));
  QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(PressedCancel()));
  QObject::connect(comboCategories, SIGNAL(activated(int)), this, SLOT(ChangeCategory()));
}
//============================================================================
void EditWindowWidget::LoadMemo()
{
  setCaption("Edit memo");

  QFile file(fileName);

  if (file.exists())
  {
    if (!file.open(IO_ReadOnly))
    {
      QString message = "Could not read file '" + fileName + "'";
      QMessageBox::warning(0, "File i/o error", message);
    }
    else
    {
      QTextStream inStream(&file);
      editArea->setText(QString::fromUtf8(inStream.read()));
      file.close();
    }
  }
}
//============================================================================
void EditWindowWidget::SaveMemo()
{
  QFile file(fileName);

  if(!file.open(IO_WriteOnly))
  {
    QString message = "Could not write file '" + fileName + "'";
    QMessageBox::warning(0, "File i/o error", message);
  }
  else
  {
    QTextStream outStream(&file);
    outStream << editArea->text().utf8();
    file.close();
    this->accept();
  }
}
//============================================================================
void EditWindowWidget::PressedOk()
{
  accept();
}
//============================================================================
void EditWindowWidget::PressedCancel()
{
  reject();
}
//============================================================================
void EditWindowWidget::ChangeCategory()
{
  catIndex = comboCategories->currentItem(); 
}
//============================================================================
void EditWindowWidget::RefreshWindow()
{
  CategoryConfig *catConfig = new CategoryConfig();
  catConfig->BuildCategoryCombo(comboCategories, FALSE);
  comboCategories->setCurrentItem(catIndex);
  delete(catConfig);
}
