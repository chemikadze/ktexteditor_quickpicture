#include <ktexteditor/document.h>
#include <ktexteditor/editor.h>

#include "simple_controller.h"

SimpleController::SimpleController ( KTextEditor::View* view ) : Controller ( view ), m_view(view) 
{
}

void SimpleController::readConfig()
{
}

void SimpleController::writeConfig()
{
}

void SimpleController::requestInserting()
{
	QString test = "<there can be your picture>";
	m_view->document()->insertText(m_view->cursorPosition(), test);
}

#include "simple_controller.moc"