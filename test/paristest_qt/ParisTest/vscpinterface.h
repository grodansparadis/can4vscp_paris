// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 2 of the License, or (at your option) any later version.
//
// This file is part of the VSCP (http://www.vscp.org)
// Copyright (C) 2000-2014
// Ake Hedman, Grodans Paradis AB,<akhe@grodansparadis.com>
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this file see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//

#ifndef VSCPINTERFACE_H
#define VSCPINTERFACE_H

#include "inttypes.h"
#include <guid.h>
#include <QString>
#include <QFileInfo>

/// Driver types
enum drivertype {
  UNDEFINED,
  LEVEL1,
  DAEMON
} ;

///////////////////////////////////////////////////////////////////////////////
/// \brief The VSCPInterface class
/// This class holds information about either a Level I driver (CANAL)
/// or a VSCP daemon connection.
///

class VSCPInterface
{
public:
  VSCPInterface();

  /// Driver type
  enum drivertype m_driverType;

  /// Driver description
  QString m_description;

  // * * * Level I (CANAL) driver * * *

  /// Path to Level I/CANAL driver
  QFileInfo m_path;

  /// Driver configuration string
  QString m_configuration;

  /// Level II driver flags
  uint32_t m_flags;

  // * * * Daemon connection * * *

  /// Server URL
  QString m_url;

  /// Server port to use. Default: 9598
  uint16_t m_port;

  /// Username. Default: admin
  QString m_username;

  /// Password. Default: secret
  QString m_password;

  /// Interface name
  QString m_interfaceName;

  /// Interface GUID
  cguid m_interfaceGUID;

};

#endif // VSCPINTERFACE_H
