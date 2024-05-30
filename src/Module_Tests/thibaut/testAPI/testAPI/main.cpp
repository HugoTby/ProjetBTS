#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include "callAPI.h"
#include "TestAPI.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    TestAPI test;
   
   // premier module de test
   test.startTestsInsert();
    
    // deuxième module de test
    //test.startTestsCheckTimeAndQuota();

    // troisième module de test
    // test.startTestsGetInfos();
    

    return a.exec();
}
