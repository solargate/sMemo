#include "CatConfig.h"
//============================================================================
CategoryConfig::CategoryConfig()
{
  CheckStorage();
  BuildList();
}
//============================================================================
void CategoryConfig::CheckStorage()
{
  QString dirHome("sMemo");
  QString dirCat1("Personal");
  QString dirCat2("Business");
  QString dirCat3("Unfiled");
  QString dirCat4("All");
  QString fileCat(QDir::homeDirPath()+"/sMemo/categories");

  QDir pd1 = QDir::home();
  if (!pd1.exists(QString(dirHome), FALSE))
  {
    if (!pd1.mkdir(dirHome, FALSE))
    {
      QMessageBox::critical(0, "sMemo", QString("Can't create directory: \n"+dirHome));
      exit(1);
    }
    if (!pd1.cd(dirHome, FALSE))
    {
      QMessageBox::critical(0, "sMemo", QString("Can't change directory: \n"+dirHome));
      exit(1);
    }
    if (!pd1.mkdir(dirCat1, FALSE))
    {
      QMessageBox::critical(0, "sMemo", QString("Can't create category: \n"+dirCat1));
      exit(1);
    }
    if (!pd1.mkdir(dirCat2, FALSE))
    {
      QMessageBox::critical(0, "sMemo", QString("Can't create category: \n"+dirCat2));
      exit(1);
    }
    if (!pd1.mkdir(dirCat3, FALSE))
    {
      QMessageBox::critical(0, "sMemo", QString("Can't create category: \n"+dirCat3));
      exit(1);
    }
    if (!pd1.mkdir(dirCat4, FALSE))
    {
      QMessageBox::critical(0, "sMemo", QString("Can't create category: \n"+dirCat4));
      exit(1);
    }

    QFile file(fileCat);

    if(!file.open(IO_WriteOnly))
    {
      QString message = "Could not write category file!";
      QMessageBox::warning(0, "File i/o error", message);
    }
    else
    {
      QTextStream outStream(&file);
      outStream << (dirCat1+"\n").utf8();
      outStream << dirCat1+"\n";
      outStream << (dirCat2+"\n").utf8();
      outStream << dirCat2+"\n";
      file.close();
    }
  }
}
//============================================================================
void CategoryConfig::BuildList()
{
  QFile catFile(QDir::homeDirPath()+"/sMemo/categories");
  QDir catDir = QDir::home();
  
  categories.clear();
  folders.clear();
    
  categories << "All";
  folders << "All"; 
  
  if (catFile.open(IO_ReadOnly))
  {
    QTextStream txt(&catFile);
    while (!txt.eof())
    {
      categories << QString::fromUtf8(txt.readLine());
      folders << txt.readLine();
    }
    catFile.close();
  }
  else
  {
    QString message = "Could not read category file!";
    QMessageBox::warning(0, "File i/o error", message);    
  }    
    
  categories << "Unfiled";
  folders << "Unfiled";
}
//============================================================================
void CategoryConfig::BuildCategoryCombo(QComboBox *list, bool withAll)
{
  unsigned int i;

  list->clear();

  if (withAll==TRUE)
  {
    for(i=0; i<categories.count(); i++)
    {
      list->insertItem(categories[i]);
    }
  }
  else
  {
    for(i=1; i<categories.count(); i++)
    {
      list->insertItem(categories[i]);
    }
  }
}
//============================================================================
void CategoryConfig::BuildCategoryListBox(QListBox *list, bool withAllUnfiled)
{
  unsigned int i;

  list->clear();

  if (withAllUnfiled==TRUE)
  {
    for(i=0; i<categories.count(); i++)
    {
      list->insertItem(categories[i]);
    }
  }
  else
  {
    for(i=1; i<categories.count()-1; i++)
    {
      list->insertItem(categories[i]);
    }
  }
}
//============================================================================
void CategoryConfig::AddCategory(QString category, QString folder)
{
  QString fileCat(QDir::homeDirPath()+"/sMemo/categories");
  QFile file(fileCat);

  if(!file.open(IO_WriteOnly | IO_Append))
  {
    QString message = "Could not write category file!";
    QMessageBox::warning(0, "File i/o error", message);
  }
  else
  {
    QTextStream outStream(&file);
    outStream << (category+"\n").utf8();
    outStream << folder+"\n";
    file.close();
  }
}
//============================================================================
void CategoryConfig::RenameCategory(int index, QString newName, bool withAllUnfiled)
{
  if (withAllUnfiled==FALSE)
    index++;
  categories[index] = newName;
  WriteCategories();
}
//============================================================================
void CategoryConfig::DeleteCategory(unsigned int index)
{
  //index++; // May be better to use withAllUnfiled!
  categories.remove(categories.at(index));
  folders.remove(folders.at(index));
  WriteCategories();
}
//============================================================================
void CategoryConfig::WriteCategories()
{
  unsigned int i;
  QString fileCat(QDir::homeDirPath()+"/sMemo/categories");
  QFile file(fileCat);

  if(!file.open(IO_WriteOnly))
  {
    QString message = "Could not write category file!";
    QMessageBox::warning(0, "File i/o error", message);
  }
  else
  {
    QTextStream outStream(&file);

    for(i=1; i<categories.count()-1; i++)
    {
      outStream << (categories[i]+"\n").utf8();
      outStream << folders[i]+"\n";
    }    

    file.close();
  }
}
