#ifndef DIALOGINTERFACESELECT_H
#define DIALOGINTERFACESELECT_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardItem>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStandardPaths>

namespace Ui {
  class DialogInterfaceSelect;
}

class DialogInterfaceSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInterfaceSelect(QWidget *parent = 0);
    ~DialogInterfaceSelect();

    /*!
     * \brief readVSCPInterfaceConfig
     * \return true on success false otherwise.
     * Read defines interfaces from a VSCP Works
     * configuration file.
     */
    bool readVSCPInterfaceConfig( QList< QMap<QString,QString> > &config_vscpworks );

    /*!
     * \brief writeVSCPInterfaceConfig
     * \return true on success false otherwise.
     * Write defined interfaces from a VSCP Works
     * configuration file.
     */
    bool writeVSCPInterfaceConfig( QList< QMap<QString,QString> > &config_vscpworks );

    /*!
     * \brief parseInterfaceGeneral
     * \param xml
     * \return interface
     * Parse VSCP Works general section.
     */
    QMap<QString, QString> parseGeneral( QXmlStreamReader& xml );

    /*!
     * \brief parseInterfaceClient
     * \param xml
     * \return interface
     * Parse VSCP Works vscpclient section.
     */
    QMap<QString, QString> parseClient( QXmlStreamReader& xml );

    /*!
     * \brief parseInterfaceCanal
     * \param xml
     * \return interface
     * Parse CANAL driver entry.
     */
    QMap<QString, QString> parseInterfaceCanal( QXmlStreamReader& xml );

    /*!
     * \brief parseInterfaceTcpip
     * \param xml
     * \return interface
     * Parse VSCP Daemon TCP/IP driver entry.
     */
    QMap<QString, QString> parseInterfaceTcpip( QXmlStreamReader& xml );

    /*!
     * \brief addElementDataToMap
     * \param xml
     * \param map
     */
    void addElementDataToMap( QXmlStreamReader& xml, QMap<QString, QString>& map ) const;

private slots:
    void on_treeViewInterfaces_doubleClicked(const QModelIndex &index);

private:
  Ui::DialogInterfaceSelect *ui;
};

#endif // DIALOGINTERFACESELECT_H
