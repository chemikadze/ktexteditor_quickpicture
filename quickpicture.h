/**
  * This file is part of the KDE libraries
  * Copyright (C) 2011 Sokolov Nikolay <chemikadze@gmail.com>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Library General Public
  * License version 2 as published by the Free Software Foundation.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Library General Public License for more details.
  *
  * You should have received a copy of the GNU Library General Public License
  * along with this library; see the file COPYING.LIB.  If not, write to
  * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  * Boston, MA 02110-1301, USA.
  */

#ifndef QUICKPICTURE_H
#define QUICKPICTURE_H

#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QVariantList>

#include <ktexteditor/plugin.h>
#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <kpluginfactory.h>

class QuickPicturePlugin
    : public KTextEditor::Plugin
{
  Q_OBJECT

  public:
    explicit QuickPicturePlugin(QObject *parent = 0, const QVariantList &args = QVariantList());
    virtual ~QuickPicturePlugin();

    void addView (KTextEditor::View *view);
    void removeView (KTextEditor::View *view);

    void readConfig();
    void writeConfig();

    virtual void readConfig (KConfig *) {}
    virtual void writeConfig (KConfig *) {}

  private:
    QList<class QuickPicturePluginView*> m_views;
};

class QuickPicturePluginView : public QObject, public KXMLGUIClient
{
  Q_OBJECT
  public:
    explicit QuickPicturePluginView( KTextEditor::View *view, const char *name=0 );
    ~QuickPicturePluginView() {}
  private:
    void insertFile();
};

K_PLUGIN_FACTORY_DECLARATION(QuickPicturePluginFactory)

#endif // QUICKPICTURE_H
