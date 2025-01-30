#include "MainWindow.h"
#include "EditWindow.h"
#include "CatDialog.h"
#include "CatConfig.h"
#include "Links.h"
//============================================================================
MainWindowWidget::MainWindowWidget(QWidget *parent, const char *name)
{
  setCaption("sMemo");
  setIcon(QPixmap::QPixmap("sMemo.png"));
  setIconText("sMemo");

  CategoryConfig *catConfig = new CategoryConfig();

  QVBox *center = new QVBox(this, 0, 0, FALSE);

  listMemos = new QListBox(center, "listMemos");

  QHBox *buttons = new QHBox(center, 0, 0, FALSE);
  
  QPushButton *btnNew = new QPushButton("New", buttons, "btnNew");
  QPushButton *btnViewEdit = new QPushButton("View/Edit", buttons, "btnViewEdit");
  QPushButton *btnDelete = new QPushButton("Delete", buttons, "btnDelete");

  comboCategories = new QComboBox(buttons, "comboCategories");

  catConfig->BuildCategoryCombo(comboCategories, TRUE);

  setCentralWidget(center);

  this->selected = -1;
  RefreshList(listMemos);

  QObject::connect(btnNew, SIGNAL(clicked()), this, SLOT(NewMemo()));
  QObject::connect(btnViewEdit, SIGNAL(clicked()), this, SLOT(OpenMemo()));
  QObject::connect(btnDelete, SIGNAL(clicked()), this, SLOT(DeleteMemo()));
  QObject::connect(listMemos, SIGNAL(returnPressed(QListBoxItem*)), this, SLOT(OpenMemo()));
  QObject::connect(listMemos, SIGNAL(doubleClicked(QListBoxItem*)), this, SLOT(OpenMemo()));
  QObject::connect(comboCategories, SIGNAL(activated(int)), this, SLOT(ChangeCategory()));

  QPopupMenu *menuMemo = new QPopupMenu(this);
  menuMemo->insertItem("&New", this, SLOT(MenuMemoNew()));
  menuMemo->insertItem("&Open", this, SLOT(MenuMemoOpen()));
  menuMemo->insertItem("&Delete", this, SLOT(MenuMemoDelete()));

  QPopupMenu *menuOptions = new QPopupMenu(this);
  menuOptions->insertItem("&Settings", this, SLOT(MenuOptionsSettings()));
  menuOptions->insertItem("&Categories", this, SLOT(MenuOptionsCategories()));

  QPopupMenu *menuHelp = new QPopupMenu(this);
  menuHelp->insertItem("&About", this, SLOT(MenuHelpAbout()));
  menuHelp->insertItem("About &Qt", this, SLOT(MenuHelpAboutQt()));

  QPEMenuBar *menu = new QPEMenuBar(this);
  menu->setMargin(0);
  menu->insertItem("&Memo", menuMemo);
  menu->insertItem("&Options", menuOptions);
  menu->insertItem("&Help", menuHelp);

  delete(catConfig);
}
//============================================================================
void MainWindowWidget::NewMemo()
{
  unsigned int catIndex = 0;
  QDate today(QDate::currentDate());
  QTime now(QTime::currentTime());
  QString name;
  CategoryConfig *catConfig = new CategoryConfig();

  catIndex = comboCategories->currentItem();

  if (catIndex==0)
    catIndex++;

  this->EditMemo(name.sprintf(QDir::homeDirPath()+"/sMemo/"+catConfig->folders[catIndex]+"/%4i-%02i-%02i-%02i-%02i-%02i.smemo", today.year(), today.month(), today.day(), now.hour(), now.minute(), now.second()), true);

  delete(catConfig);
}
//============================================================================
void MainWindowWidget::EditMemo(QString filename, int create)
{
  EditWindowWidget *editWindow = new EditWindowWidget(0, "editWindow", true, 0);

  editWindow->fileName = filename;
  editWindow->LoadMemo();

  editWindow->catIndex = comboCategories->currentItem();
  if (editWindow->catIndex>0)
    editWindow->catIndex--;

  editWindow->RefreshWindow();
  
  QDialog::DialogCode retval = (QDialog::DialogCode)editWindow->exec();

  if (retval==QDialog::Accepted)
  {
    editWindow->SaveMemo();
    if (create)
    {
      Links *links = new Links();
      links->MakeLinkInAll(filename, editWindow->catIndex+1);
      delete(links);
      this->selected = listMemos->count();
    }

    // Here must be memo category renaming if the category was changed!!!
    
    comboCategories->setCurrentItem(editWindow->catIndex+1);
    editWindow->catIndex = 0;
  }

  RefreshList(listMemos);
}
//============================================================================
void MainWindowWidget::RefreshList(QListBox *list)
{
  unsigned int item;
  QString row;
  CategoryConfig *catConfig = new CategoryConfig();

  list->clear();
  
  fileList.setPath(QDir::homeDirPath()+"/sMemo/"+catConfig->folders[comboCategories->currentItem()]);
  fileList.setFilter(QDir::Files);
  fileList.setSorting(QDir::Name);
  fileList.setNameFilter("*.smemo");

  for (item=0; item<fileList.count(); item++)
  {
    QFile file(QDir::homeDirPath()+"/sMemo/"+catConfig->folders[comboCategories->currentItem()]+"/"+fileList[item]);

    if (!file.open(IO_ReadOnly))
    {
      QString message = "Could not read item '" + fileList[item] + "'";
      QMessageBox::warning(0, "File i/o error", message);
    }
    else
    {
      QTextStream inStream(&file);

      if (!inStream.atEnd())
      {
        row = QString::fromUtf8(inStream.readLine());
      } 
      else
      {
        row = "<empty memo>";
      }

      if (row.length()<1)
        row = "<no caption>";

      file.close();
  
      list->insertItem(row);
    }
  }
  
  if (listMemos->count()>0)
  {
    if (this->selected==-1)
    {
      listMemos->setCurrentItem(0);
    }
    else
    {
      if (listMemos->count()>this->selected)
      {
        listMemos->setCurrentItem(this->selected);
      }
      else
      {
        listMemos->setCurrentItem(listMemos->count()-1);
      }
    }
  }
  else
  {
    this->selected = -1;
  }

  delete(catConfig);
}
//============================================================================
void MainWindowWidget::OpenMemo()
{
  int number = listMemos->currentItem();
  CategoryConfig *catConfig = new CategoryConfig();

  if (listMemos->count()>0)
  {
    this->selected = number;
    this->EditMemo(QDir::homeDirPath()+"/sMemo/"+catConfig->folders[comboCategories->currentItem()]+"/"+fileList[number], false);
  }

  delete(catConfig);
}
//============================================================================
void MainWindowWidget::DeleteMemo()
{
  CategoryConfig *catConfig = new CategoryConfig();

  if (listMemos->count()>0)
  {
    switch (QMessageBox::warning(0, "Delete Memo", "Really delete\n'"+listMemos->currentText()+"'?", QMessageBox::Yes, QMessageBox::No))
    {
      case QMessageBox::Yes:
        this->selected = listMemos->currentItem();
        QFile::remove(QDir::homeDirPath()+"/sMemo/"+catConfig->folders[comboCategories->currentItem()]+"/"+fileList[listMemos->currentItem()]);
        // Delete link!!!
        RefreshList(listMemos);
        break;
      case QMessageBox::No:
        break;
    }
  }

  delete(catConfig);
}
//============================================================================
void MainWindowWidget::ChangeCategory()
{
  RefreshList(listMemos);
}
//============================================================================
void MainWindowWidget::MenuMemoNew()
{
  NewMemo();
}
//============================================================================
void MainWindowWidget::MenuMemoOpen()
{
  OpenMemo();
}
//============================================================================
void MainWindowWidget::MenuMemoDelete()
{
  DeleteMemo();
}
//============================================================================
void MainWindowWidget::MenuHelpAbout()
{
  QString aboutText;
  aboutText = "<b>sMemo 1.1</b><br>Based on noteZ<br>Written by Alexander Cheryomukhin aka SolarWind<br>solarwind.palm@gmail.com<br>Distributed under GPL";
  QMessageBox::about(this, "About", aboutText);
}
//============================================================================
void MainWindowWidget::MenuHelpAboutQt()
{
  QMessageBox::aboutQt(0, "About Qt");
}
//============================================================================
void MainWindowWidget::MenuOptionsSettings()
{

}
//============================================================================
void MainWindowWidget::MenuOptionsCategories()
{
  CategoriesDialog *categories = new CategoriesDialog(0, "", true, 0);

  categories->exec();
  CategoryConfig *catConfig = new CategoryConfig();
  catConfig->BuildCategoryCombo(comboCategories, TRUE);
  delete(catConfig);
  RefreshList(listMemos);
}
