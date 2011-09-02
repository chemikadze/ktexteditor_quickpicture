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

#include "quickpicture.h"

#include <kpluginfactory.h>
#include <kpluginloader.h>

#include <kaction.h>
#include <kactioncollection.h>

#include <ktexteditor/configinterface.h>
#include <kmessagebox.h>
#include <klocalizedstring.h>
#include <iostream>
#include <kconfiggroup.h>
#include <kaboutdata.h>

K_PLUGIN_FACTORY_DEFINITION(QuickPicturePluginFactory,
        registerPlugin<QuickPicturePlugin>("ktexteditor_quickpicture");
        )
K_EXPORT_PLUGIN(QuickPicturePluginFactory(KAboutData("ktexteditor_quickpicture", "ktexteditor_plugins", ki18n("Quick picture"), "0.1", ki18n("Quick picture"), KAboutData::License_LGPL_V2 ) ) )

QuickPicturePlugin::QuickPicturePlugin(QObject *parent, const QVariantList &args)
    : KTextEditor::Plugin(parent)
{
}

QuickPicturePlugin::~QuickPicturePlugin()
{
}

void QuickPicturePlugin::addView(KTextEditor::View *view)
{
    QuickPicturePluginView *nview = new QuickPicturePluginView (view, "Insert File Plugin");
    m_views.append (nview);
}

void QuickPicturePlugin::removeView(KTextEditor::View *view)
{
  int z=0;
    // Loop written for the unlikely case of a view being added more than once
    while (z < m_views.count())
    {
      QuickPicturePluginView *nview = m_views.at(z);
      if (nview->parentClient() == view)
      {
         m_views.removeAll (nview);
         delete nview;
      }
      else
         ++z;
    }
}

void QuickPicturePlugin::readConfig()
{
    KConfigGroup cg(KGlobal::config(), "QuickPicture Plugin");
    // Read configuration parameters, make them false by default
    // TODO: set to true by default once https://bugs.kde.org/show_bug.cgi?id=234525 got resolved
}

void QuickPicturePlugin::writeConfig()
{
    KConfigGroup cg(KGlobal::config(), "QuickPicture Plugin");
    // cg.writeEntry("name", value);
}

/// QuickPicturePluginDocument

QuickPicturePluginView::QuickPicturePluginView( KTextEditor::View *view, const char *name )
  : QObject( view ),
    KXMLGUIClient( view )
{
    setObjectName( name );

    setComponentData( QuickPicturePluginFactory::componentData() );

    KAction *action = new KAction( i18n("Insert picture..."), this );
    actionCollection()->addAction( "tools_insert_picture", action );
    
    setXMLFile( "ktexteditor_quickpicture.rc" );
}



#include "quickpicture.moc"
