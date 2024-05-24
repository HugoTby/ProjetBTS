#include "moduleTestIHM.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    moduleTestIHM w;
    w.show();
    return a.exec();
}
