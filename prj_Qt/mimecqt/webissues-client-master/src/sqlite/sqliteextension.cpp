/**************************************************************************
* Extensible SQLite driver for Qt
* Copyright (C) 2011-2015 Michał Męciński
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License version 3
* as published by the Free Software Foundation.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library.  If not, see <http://www.gnu.org/licenses/>.
*
* This library is based on the QtSql module of the Qt Toolkit
* Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
**************************************************************************/

#include "sqliteextension.h"

#include <QString>
#include <QRegExp>

#if defined HAVE_SYSTEM_SQLITE
# include <sqlite3.h>
#else
# include "sqlite3.h"
#endif

static int localeCompare( void* /*arg*/, int len1, const void* data1, int len2, const void* data2 )
{
    QString string1 = QString::fromRawData( reinterpret_cast<const QChar*>( data1 ), len1 / sizeof( QChar ) );
    QString string2 = QString::fromRawData( reinterpret_cast<const QChar*>( data2 ), len2 / sizeof( QChar ) );

    return QString::localeAwareCompare( string1, string2 );
}

static int nocaseCompare( void* /*arg*/, int len1, const void* data1, int len2, const void* data2 )
{
    QString string1 = QString::fromRawData( reinterpret_cast<const QChar*>( data1 ), len1 / sizeof( QChar ) );
    QString string2 = QString::fromRawData( reinterpret_cast<const QChar*>( data2 ), len2 / sizeof( QChar ) );

    return QString::compare( string1, string2, Qt::CaseInsensitive );
}

static void regexpFunction( sqlite3_context* context, int /*argc*/, sqlite3_value** argv )
{
    int len1 = sqlite3_value_bytes16( argv[ 0 ] );
    const void* data1 = sqlite3_value_text16( argv[ 0 ] );
    int len2 = sqlite3_value_bytes16( argv[ 1 ] );
    const void* data2 = sqlite3_value_text16( argv[ 1 ] );

    if ( !data1 || !data2 )
        return;

    // do not use fromRawData for pattern string because it may be cached internally by the regexp engine
    QString string1( reinterpret_cast<const QChar*>( data1 ), len1 / sizeof( QChar ) );
    QString string2 = QString::fromRawData( reinterpret_cast<const QChar*>( data2 ), len2 / sizeof( QChar ) );

    QRegExp pattern( string1, Qt::CaseInsensitive );

    bool match = pattern.exactMatch( string2 );

    sqlite3_result_int( context, match ? 1 : 0 );
}

void installSQLiteExtension( sqlite3* db )
{
    sqlite3_create_collation( db, "LOCALE", SQLITE_UTF16, NULL, &localeCompare );
    sqlite3_create_collation( db, "NOCASE", SQLITE_UTF16, NULL, &nocaseCompare );

    sqlite3_create_function( db, "regexp", 2, SQLITE_UTF16, NULL, &regexpFunction, NULL, NULL );
}
