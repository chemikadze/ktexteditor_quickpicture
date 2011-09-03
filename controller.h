#ifndef QUICKPICTURE_CONTROLLER_H
#define QUICKPICTURE_CONTROLLER_H

#include <QtCore/QObject>
#include <ktexteditor/view.h>

class Controller: public QObject {
Q_OBJECT
public:
	explicit Controller(KTextEditor::View* view);
	virtual ~Controller();
	virtual void readConfig() = 0;
	virtual void writeConfig() = 0;

public Q_SLOTS:
	virtual void requestInserting() = 0;
};

#endif