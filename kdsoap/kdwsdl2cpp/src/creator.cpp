/****************************************************************************
** Copyright (C) 2010-2010 Klaralvdalens Datakonsult AB.  All rights reserved.
**
** This file is part of the KD SOAP library.
**
** Licensees holding valid commercial KD Soap licenses may use this file in
** accordance with the KD Soap Commercial License Agreement provided with
** the Software.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 and version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE.GPL included.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Contact info@kdab.com if any conditions of this licensing are not
** clear to you.
**
**********************************************************************/

/*
    Copyright (c) 2005 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include <libkode/file.h>
#include <libkode/printer.h>

#include "settings.h"

#include "creator.h"

#include <QDebug>

using namespace KWSDL;

Creator::Creator()
{
}

void Creator::create( const KODE::Class::List &classes )
{
  KODE::Printer printer;
  printer.setOutputDirectory( Settings::self()->outputDirectory() );

  // Set generated header details.
  printer.setCreationWarning( true );
  printer.setGenerator( QLatin1String( "KDAB's kdwsdl2cpp" ) );
  printer.setSourceFile( Settings::self()->wsdlFileName() );

  // Qt-like coding style
  printer.setLabelsDefineIndent( false );
  printer.setIndentLabels( false );

  KODE::File file;

  if (Settings::self()->generateImplementation()) {
      file.setImplementationFilename( Settings::self()->outputFileName() );
      file.setHeaderFilename(Settings::self()->headerFile());
  } else {
      file.setHeaderFilename( Settings::self()->outputFileName() );
  }

  KODE::Class::List::ConstIterator it;
  for ( it = classes.constBegin(); it != classes.constEnd(); ++it ) {
      file.insertClass( *it );
  }

  if (Settings::self()->generateImplementation())
      printer.printImplementation( file );
  else
      printer.printHeader( file );
}