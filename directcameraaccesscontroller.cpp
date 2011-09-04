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


#include <QtCore/QTimerEvent>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include <QtGui/QGridLayout>
#include <QtGui/QDialogButtonBox>
#include <ktexteditor/view.h>
#include <ktexteditor/document.h>

#include <opencv/cv.h>

#include "directcameraaccesscontroller.h"

using cv::Mat;

namespace {
	int timeout = 100;
}

DirectCameraAccessController::DirectCameraAccessController(KTextEditor::View* view): 
	Controller(view), m_view(view), m_dialog(0)
{

}


DirectCameraAccessController::~DirectCameraAccessController()
{

}

void DirectCameraAccessController::readConfig()
{
	
}

void DirectCameraAccessController::writeConfig()
{

}

void DirectCameraAccessController::requestInserting()
{
	if (m_dialog) {
		m_dialog->show();
	}
	else {
		m_dialog = new ImageCaptureDialog();
		connect(m_dialog, SIGNAL(accepted()), this, SLOT(insertingAccepted()));
		connect(m_dialog, SIGNAL(rejected()), this, SLOT(insertingRejected()));
		m_dialog->show();
	}
}

void DirectCameraAccessController::insertingAccepted()
{
	QImage image = m_dialog->getImage();
	QString imageName = m_dialog->getImageName();
	
	QString savedName = saveImage(image, imageName);
	if (!savedName.isEmpty()) {
		m_view->document()->insertText(m_view->cursorPosition(), formatImageInclude(savedName));
	}
	else {
		QMessageBox::critical(0, tr("QuickPicture plugin"), tr("Can not save image %1").arg(imageName));
	}
	
	m_dialog->deleteLater();
	m_dialog = 0;
}

void DirectCameraAccessController::insertingRejected()
{
	m_dialog->deleteLater();
	m_dialog = 0;
}

QString DirectCameraAccessController::formatImageInclude(const QString& imageName)
{
	return QString("\\includegraphics{%1}").arg(imageName);
}

QString DirectCameraAccessController::saveImage(const QImage& image, const QString& imageName)
{
	QString documentDir = m_view->document()->url().directory();
	QString basename = imageName;
	if (!(basename.endsWith(".jpg") || basename.endsWith(".jpeg"))) {
		basename += ".jpg";
	}
	QString fullName = documentDir+'/'+basename;
	qDebug() << "Saving to " << fullName;
	if (image.save(fullName)) {
		return basename;
	}
	else {
		return QString();
	}
}





ImageCaptureDialog::ImageCaptureDialog(QWidget* parent):
	QDialog(parent), m_captured(false)
{
	m_cap.reset(new VideoCapture(0));
	m_cap->set(CV_CAP_PROP_FORMAT, CV_8UC3);
	
	if (!m_cap->isOpened()) {
		QMessageBox::critical(0, tr("QuickPicture plugin"), tr("Can not open video device."));
		return;
	}
	m_timer_id = startTimer(timeout);
	
	m_filename_edit = new QLineEdit(this);
	m_captured_image = new QLabel(this);
	m_captured_image->setMinimumSize(640, 480);
	m_capture_button = new QPushButton(this);
	m_capture_button->setText(tr("Capture"));
	m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);
	
	QGridLayout *la = new QGridLayout(this);
	la->addWidget(m_captured_image, 0, 0, 1, 2);
	la->addWidget(m_capture_button, 1, 1, 1, 1);
	la->addWidget(m_filename_edit, 1, 0, 1, 1);
	la->addWidget(m_buttons, 2, 0, 1, 2);
	la->setColumnStretch(1, 1);
	la->setColumnStretch(1, 0);
	this->setLayout(la);
	
	connect(m_capture_button, SIGNAL(clicked()), this, SLOT(capture()));
	connect(m_buttons, SIGNAL(accepted()), this, SLOT(accept()));
	connect(m_buttons, SIGNAL(rejected()), this, SLOT(reject()));
	connect(this, SIGNAL(accepted()), this, SLOT(saveImage()));
}

void ImageCaptureDialog::capture()
{
	if (!m_captured) {
		killTimer(m_timer_id);
		m_capture_button->setText(tr("Capture again"));
	}
	else {
		m_timer_id = startTimer(timeout);
		m_capture_button->setText(tr("Capture"));
	}
	m_captured = !m_captured;
}

void ImageCaptureDialog::saveAndStop()
{
	saveImage();
	killTimer(m_timer_id);
	m_captured = false; capture();
}


void ImageCaptureDialog::saveImage()
{
	Mat frame;
	Mat raw;
	m_cap->grab();
	m_cap->retrieve(raw);
	frame = raw; // need transform here
	m_image = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
	qDebug() << "Frame captured...";
}


ImageCaptureDialog::~ImageCaptureDialog()
{
	killTimer(m_timer_id);
}

void ImageCaptureDialog::timerEvent(QTimerEvent* e)
{
	if (e->timerId() == m_timer_id) {
		saveImage();
		m_captured_image->setPixmap(QPixmap::fromImage(m_image));
		repaint();
	}
    QObject::timerEvent(e);
}

QImage ImageCaptureDialog::getImage()
{
	return QImage(m_image);
}

QString ImageCaptureDialog::getImageName()
{
	return m_filename_edit->text();
}




#include "directcameraaccesscontroller.moc"


