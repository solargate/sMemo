#include <qdir.h>
#include <qmessagebox.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <qcombobox.h>
#include <qlistbox.h>

class CategoryConfig
{
public:
  QStringList categories;
  QStringList folders;

  CategoryConfig();

  void CheckStorage();
  void BuildList();
  void BuildCategoryCombo(QComboBox *list, bool withAll);
  void BuildCategoryListBox(QListBox *list, bool withAllUnfiled);
  void AddCategory(QString category, QString folder);
  void RenameCategory(int index, QString newName, bool withAllUnfiled);
  void DeleteCategory(unsigned int index);

private:
  void WriteCategories();
};
