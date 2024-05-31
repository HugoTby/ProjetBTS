#pragma once
#include <qobject.h>
#include "inveo.h"
class test : public QObject
{
	Q_OBJECT
public :
	void envoiTrame();
	test();
	
private:
	inveo* o;
};

