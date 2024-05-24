#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_moduleTestIHM.h"
#include <qobject.h>
#include "inveo.h"

class moduleTestIHM : public QMainWindow
{
    Q_OBJECT

public:
    moduleTestIHM(QWidget *parent = nullptr);
    ~moduleTestIHM();

private:
    Ui::moduleTestIHMClass ui;
    inveo* o;

private slots :
    
    void onButtonAcceptSoundClicked();
};
