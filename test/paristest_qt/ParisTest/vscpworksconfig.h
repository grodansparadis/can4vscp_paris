#ifndef VSCPWORKSCONFIG_H
#define VSCPWORKSCONFIG_H

//QT
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardItem>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStandardPaths>
#include <QColor>
#include <QFont>
#include <QtEndian>

// General
#include <inttypes.h>

// VSCP stuff
#include <vscp.h>
#include <vscphelper.h>
#include <guid.h>

#define VSCPWORKS_CONFIG_FILE_NAME   _("vscpworks.conf")

#define VSCPWORKS_MAIN_WINDOW_DEFAULT_WIDTH     600
#define VSCPWORKS_MAIN_WINDOW_DEFAULT_HEGHT     311

#define MAX_NUMBER_OF_NODES         256

#define DAEMON_LOGMSG_DEBUG         0
#define DAEMON_LOGMSG_INFO          1
#define DAEMON_LOGMSG_NOTICE        2
#define DAEMON_LOGMSG_WARNING       3
#define DAEMON_LOGMSG_ERROR         4
#define DAEMON_LOGMSG_CRITICAL      5
#define DAEMON_LOGMSG_ALERT         6
#define DAEMON_LOGMSG_EMERGENCY     7

#define VCSP_TRMIT_FIELD_COUNT      6

#define VCSP_TRMIT_FIELD_WIDTH_0   30
#define VCSP_TRMIT_FIELD_WIDTH_1   200
#define VCSP_TRMIT_FIELD_WIDTH_2   60
#define VCSP_TRMIT_FIELD_WIDTH_3   60
#define VCSP_TRMIT_FIELD_WIDTH_4   120
#define VCSP_TRMIT_FIELD_WIDTH_5   900

#define VCSP_TRMIT_FIELD_TEXT_0  _("x")
#define VCSP_TRMIT_FIELD_TEXT_1  _("Name")
#define VCSP_TRMIT_FIELD_TEXT_2  _("Period")
#define VCSP_TRMIT_FIELD_TEXT_3  _("Count")
#define VCSP_TRMIT_FIELD_TEXT_4  _("Trigger")
#define VCSP_TRMIT_FIELD_TEXT_5  _("Event")

#define VCSP_RSCV_FIELD_COUNT     4

#ifdef WIN32
#define VCSP_RSCV_FIELD_DEFAULT_HEIGHT   20
#else
#define VCSP_RSCV_FIELD_DEFAULT_HEIGHT   20
#endif

#define VCSP_RSCV_FIELD_WIDTH_0   30
#define VCSP_RSCV_FIELD_WIDTH_1   170
#define VCSP_RSCV_FIELD_WIDTH_2   170
#define VCSP_RSCV_FIELD_WIDTH_3   700

#define VCSP_RSCV_FIELD_TEXT_0    _("Dir")
#define VCSP_RSCV_FIELD_TEXT_1    _("Class")
#define VCSP_RSCV_FIELD_TEXT_2    _("Type")
#define VCSP_RSCV_FIELD_TEXT_3    _("Note")

// Default values for read/write register functions
// used in device config and scan.
#define VSCP_REGISTER_READ_RESEND_TIMEOUT       2000
#define VSCP_REGISTER_READ_ERROR_TIMEOUT        5000
#define VSCP_REGISTER_READ_MAX_TRIES            2

#define VSCP_DEVCONFIG_NUMBERBASE_HEX			0
#define VSCP_DEVCONFIG_NUMBERBASE_DECIMAL		1

#define INTERFACE_CANAL   0
#define INTERFACE_VSCP    1

///////////////////////////////////////////////////////////////////////////////
/// \brief The canalInterface class
///

class canalInterface
{
public:

    canalInterface();

    QString m_strDescription;   // Decription of driver
    QString m_strPath;          // Path to driver
    QString m_strConfig;        // Driver configuration string
    uint32_t m_flags;           // Driver flags
};

///////////////////////////////////////////////////////////////////////////////
/// \brief The tcpipInterface class
///

class tcpipInterface
{
public:

    tcpipInterface();

    QString m_strDescription;		// Description of VSCP interface
    QString m_strHost;				// Host where server lives
    QString m_strUser;				// Username
    QString m_strPassword;			// Password
    bool m_bLevel2;					// Full Level II communication
    uint16_t m_port;                // Port to use on server
    QString m_strInterfaceName;     // Name for remote interface
    cguid m_GUID;                   // GUID for interface
    vscpEventFilter m_vscpfilter;	// Filter to apply
};





class vscpworksconfig
{
public:

    vscpworksconfig();

    // General
    uint16_t m_sizeWidth;           // Initial main frame width
    uint16_t m_sizeHeight;          // Initial main frame height
    uint16_t m_xpos;                // Initial main frame x position
    uint16_t m_ypos;                // Initial main frame y position

    QString m_strPathTemp;          // Path to temporary storage

    // Logfile
    bool m_bEnableLog;              // True for writes to logfile
    QString m_strPathLogFile;       // Path to logfile
    uint8_t m_logLevel;             // Log level

    // CANAL Frames
    QColor m_CanalRcvFrameTextColour;   // Background colour for CANAL grid
    QColor m_CanalRcvFrameBgColour;     // Background colour for CANAL grid
    QColor m_CanalRcvFrameLineColour;   // Foreground colour for CANAL grid
    QFont m_CanalRcvFrameFont;          // Font for CANAL grid

    bool m_CanalRcvShowField[8];        // Flag to show field.
    QString m_CanalRcvFieldText[8];     // Header text for field
    uint8_t m_CanalRcvFieldOrder[8];    // Order for fields
    uint16_t m_CanalRcvFieldWidth[8];   // Width for fields

    QColor m_CanalTrmitFrameTextColour; // Background colour for CANAL transmit grid
    QColor m_CanalTrmitFrameBgColour;   // Background colour for CANAL transmit grid
    QColor m_CanalTrmitFrameLineColour; // Foreground colour for CANAL transmit grid
    QFont m_CanalTrmitFrameFont;        // Font for VSCP grid

    bool m_CanalTrmitShowField[5];      // Flag to show field.
    QString m_CanalTrmitFieldText[5];  // Header text for field
    uint8_t m_CanalTrmitFieldOrder[5];  // Order for fields
    uint16_t m_CanalTrmitFieldWidth[5]; // Order for fields

    // VSCP Frames
    QColor m_VscpRcvFrameRxTextColour;  // Text colour for VSCP grid rx Line
    QColor m_VscpRcvFrameRxBgColour;    // Background colour for VSCP grid rx line
    QColor m_VscpRcvFrameTxTextColour;  // Text colour for VSCP grid tx Line
    QColor m_VscpRcvFrameTxBgColour;    // Background colour for VSCP grid tx line
    QColor m_VscpRcvFrameLineColour;    // Line colour for VSCP grid
    QFont m_VscpRcvFrameFont;           // Font for VSCP grid
    uint16_t m_VscpRcvFrameRowLineHeight;   // Line height for rows

    bool m_VscpRcvShowField[ VCSP_RSCV_FIELD_COUNT ];      // Flag to show field.
    QString m_VscpRcvFieldText[ VCSP_RSCV_FIELD_COUNT ];   // Header text for field
    uint8_t m_VscpRcvFieldOrder[ VCSP_RSCV_FIELD_COUNT ];  // Order for fields
    uint16_t m_VscpRcvFieldWidth[ VCSP_RSCV_FIELD_COUNT ]; // Width for fields

    QColor m_VscpTrmitFrameTextColour;      // Default Text colour for VSCP grid
    QColor m_VscpTrmitFrameBgColour;        // Background colour for VSCP grid
    QColor m_VscpTrmitFrameLineColour;      // Foreground colour for VSCP grid
    QFont m_VscpTrmitFrameFont;             // Font for VSCP grid

    bool m_VscpTrmitShowField[ VCSP_TRMIT_FIELD_COUNT ];       // Flag to show field.
    QString m_VscpTrmitFieldText[ VCSP_TRMIT_FIELD_COUNT ];    // Header text for field
    uint8_t m_VscpTrmitFieldOrder[ VCSP_TRMIT_FIELD_COUNT ];   // Order for fields
    uint16_t m_VscpTrmitFieldWidth[ VCSP_TRMIT_FIELD_COUNT ];  // Width for fields

    bool m_bAutoscollRcv;                   // True to scroll upp so last added row
                                            // always is shown
    bool m_VscpRcvFrameRxbPyamas;           // every second row grey if true

    bool m_UseSymbolicNames;                // Use symbolic names for class and type

    // Interfaces
    QList<canalInterface> m_canalIfList;
    QList<tcpipInterface> m_vscpIfList;

    uint32_t m_VscpRegisterReadResendTimeout;	// Timeout before register read retries
    uint32_t m_VscpRegisterReadErrorTimeout;	// Timeout before register read is considered and error
    uint8_t	m_VscpRegisterReadMaxRetries;		// Max number of retries to read a register.

    // device configuration
    uint8_t m_Numberbase;						// Number base for register values

    // Confirm switch
    bool m_bConfirmDelete;						// Must confirm session rx/tx etc list delete

};


#endif // VSCPWORKSCONFIG_H
