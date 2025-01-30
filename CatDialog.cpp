#include "CatDialog.h"
#include "CatRename.h"
#include "CatConfig.h"
//============================================================================
CategoriesDialog::CategoriesDialog(QWidget *parent, const char *name, bool modal, WFlags fl): QDialog(parent, name, modal, fl)
{
  setCaption("Categories");

  QGridLayout *layout = new QGridLayout(this, 7, 2, 10, 10);

  listCat = new QListBox(this);
  layout->addMultiCellWidget(listCat, 0, 5, 0, 0);

  editCatAdd = new QLineEdit(this);
  layout->addWidget(editCatAdd, 6, 0);

  QPushButton *btnRename = new QPushButton("Rename", this);
  layout->addWidget(btnRename, 0, 1);

  QPushButton *btnDelete = new QPushButton("Delete", this);
  layout->addWidget(btnDelete, 1, 1);

  QPushButton *btnAdd = new QPushButton("Add", this);
  layout->addWidget(btnAdd, 6, 1);

  QObject::connect(btnAdd, SIGNAL(clicked()), this, SLOT(AddCategory()));
  QObject::connect(btnRename, SIGNAL(clicked()), this, SLOT(RenameCategory()));
  QObject::connect(btnDelete, SIGNAL(clicked()), this, SLOT(DeleteCategory()));

  RefreshCategories();
}
//============================================================================
void CategoriesDialog::RefreshCategories()
{
  CategoryConfig *catConfig = new CategoryConfig();
  catConfig->BuildCategoryListBox(listCat, FALSE);
  delete(catConfig);
}
//============================================================================
void CategoriesDialog::AddCategory()
{
  unsigned int i;
  unsigned int err = 0;	
  CategoryConfig *catConfig = new CategoryConfig();
  QDate today(QDate::currentDate());
  QTime now(QTime::currentTime());
  QString catFileName;
  QDir catDir = QDir::home();
  
  catDir.cd("sMemo", FALSE);
  
  catFileName.sprintf("%4i-%02i-%02i-%02i-%02i-%02i", today.year(), today.month(), today.day(), now.hour(), now.minute(), now.second());

  for (i=0; i<listCat->count(); i++)
  {
    if (listCat->text(i)==editCatAdd->text())
    {
      QMessageBox::warning(0, "sMemo", QString("Category \""+editCatAdd->text()+"\" exist!"));
      err = 1;
    }
  }

  if ((editCatAdd->text()!="") && (err==0))
  {
    listCat->insertItem(editCatAdd->text());
    catDir.mkdir(catFileName, FALSE);
    catConfig->AddCategory(editCatAdd->text(), catFileName);
    editCatAdd->clear();
  }

  delete(catConfig);
}
//============================================================================
void CategoriesDialog::RenameCategory()
{
  if (listCat->currentItem()!=-1)
  {
    CategoryRename *catRename = new CategoryRename(0, "", true, 0, listCat->currentText());

    if (catRename->exec()==QDialog::Accepted)
    {
      CategoryConfig *catConfig = new CategoryConfig();
      catConfig->RenameCategory(listCat->currentItem(), catRename->GetText(), FALSE);
      delete(catConfig);
      
      listCat->changeItem(catRename->GetText(), listCat->currentItem());
    }
  }
}
//============================================================================
void CategoriesDialog::DeleteCategory()
{
  unsigned int item;
  QDir inDir = QDir::home();
  QDir outDir = QDir::home();
  CategoryConfig *catConfig = new CategoryConfig();
  
  inDir.cd("sMemo", FALSE);
  //inDir.cd(listCat->currentText(), FALSE);
  inDir.cd(catConfig->folders[listCat->currentItem()+1], FALSE);
  outDir.cd("sMemo", FALSE);
  outDir.cd("Unfiled", FALSE);

  switch (QMessageBox::warning(0, "Delete Category", "Really delete category \""+listCat->currentText()+"\"?\nAll memos from this category will be moved to \"Unfiled\"", QMessageBox::Yes, QMessageBox::No))
  {
    case QMessageBox::Yes:

      inDir.setFilter(QDir::Files);
      inDir.setSorting(QDir::Name);
      inDir.setNameFilter("*.smemo");

      for (item=0; item<inDir.count(); item++)
      {
        QFile inFile(inDir.absPath()+"/"+inDir[item]);
        QFile outFile(outDir.absPath()+"/"+inDir[item]);
        inFile.open(IO_ReadOnly);
        outFile.open(IO_WriteOnly);
        QTextStream inStream(&inFile);
        QTextStream outStream(&outFile);
        outStream << inStream.read();
        inFile.close();
        outFile.close();

        inFile.remove();
      }

      inDir.cd("..");
      //inDir.rmdir(listCat->currentText(), FALSE);
      inDir.rmdir(catConfig->folders[listCat->currentItem()+1], FALSE);
      catConfig->DeleteCategory(listCat->currentItem()+1);
      listCat->removeItem(listCat->currentItem());

      break;

    case QMessageBox::No:
      break;
  }

  delete(catConfig);
}
