#include "facepvms.h"
#include "database.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     facePvms w;
     w.show();

    return a.exec();
}
