#ifndef SIMPLE_CONTROLLER_H
#define SIMPLE_CONTROLLER_H

#include "controller.h"

class SimpleController: public Controller {
Q_OBJECT
public:
	explicit SimpleController ( KTextEditor::View* view );
		
	virtual void readConfig();
	virtual void writeConfig();
public Q_SLOTS:
	virtual void requestInserting();
private:
	KTextEditor::View *m_view;
};

#endif