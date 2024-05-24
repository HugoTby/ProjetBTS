#include "moduleTestIHM.h"

moduleTestIHM::moduleTestIHM(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    o = new inveo("192.168.65.240", 502, this);
    o->connectToHost();
    QObject::connect(ui.acceptSoundButton, SIGNAL(clicked()), this, SLOT(onButtonAcceptSoundClicked()));
}

void moduleTestIHM::onButtonAcceptSoundClicked()
{
    o->emitAcceptSound();
}

moduleTestIHM::~moduleTestIHM()
{
}


