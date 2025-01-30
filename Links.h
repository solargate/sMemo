#include <qstring.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class Links
{
public:
  Links();

  void MakeLinkInAll(QString origFilename, unsigned int catIndex);
};
