#include "Links.h"
#include "CatConfig.h"
//============================================================================
Links::Links()
{
}
//============================================================================
void Links::MakeLinkInAll(QString origFilename, unsigned int catIndex)
{
  int res, pos, status;
  QString filename = origFilename;

  pos = filename.findRev("/", -1, FALSE);
  filename.remove(0, pos+1);

  CategoryConfig *catConfig = new CategoryConfig();

  QString link = QDir::homeDirPath()+"/sMemo/All/"+filename;
  QString target = QDir::homeDirPath()+"/sMemo/"+catConfig->folders[catIndex]+"/"+filename;

  pid_t pid = fork();

  switch (pid)
  {
    case 0:
      res = execlp("ln", "ln", "-s", target.latin1(), link.latin1(), NULL);
      break;
    default:
      while (pid!=wait(&status))
        ;
      break;
  }    

  delete(catConfig);
}
