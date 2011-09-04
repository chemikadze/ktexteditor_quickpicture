/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  Nickolay Sokolov <chemikadze@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef DIRECTCAMERAACCESSCONTROLLER_H
#define DIRECTCAMERAACCESSCONTROLLER_H

#include <QtGui/QDialog>
#include <auto_ptr.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "controller.h"


class QLabel;
class QLineEdit;
class QPushButton;
class ImageCaptureDialog;
class QDialogButtonBox;

using cv::VideoCapture;

class DirectCameraAccessController: public Controller
{
Q_OBJECT
public:
	explicit DirectCameraAccessController(KTextEditor::View* view);
    virtual ~DirectCameraAccessController();
	virtual void readConfig();
	virtual void writeConfig();

	QString formatImageInclude(const QString& imageName);
	QString saveImage(const QImage& image, const QString& imageName);
	
public Q_SLOTS:
	virtual void requestInserting();
	void insertingAccepted();
	void insertingRejected();
	
private:
	KTextEditor::View* m_view;
	ImageCaptureDialog* m_dialog;
};


class ImageCaptureDialog: public QDialog {
Q_OBJECT
public:
	ImageCaptureDialog(QWidget* parent=0);
	~ImageCaptureDialog();

	QImage getImage();
	QString getImageName();
	
public Q_SLOTS:
	void capture();
	void saveImage();
	void saveAndStop();

private:
	void timerEvent(QTimerEvent*);
	
	int m_timer_id;
	int m_captured;
	QImage m_image;
	std::auto_ptr<VideoCapture> m_cap;
	
	QLineEdit *m_filename_edit;
	QLabel *m_captured_image;
	QPushButton *m_capture_button;
	QDialogButtonBox *m_buttons;
};

#endif // DIRECTCAMERAACCESSCONTROLLER_H
