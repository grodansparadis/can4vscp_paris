#include "dialoginterfaceselect.h"
#include "ui_dialoginterfaceselect.h"


///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::DialogInterfaceSelect
/// \param parent
///

DialogInterfaceSelect::DialogInterfaceSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInterfaceSelect)
{
    QList< QMap<QString,QString> > config_vscpworks;

    ui->setupUi(this);

    QString str =
        QStandardPaths::locate( QStandardPaths::DataLocation,
                                    "vscpworks.conf",
                                    QStandardPaths::LocateFile );
    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DataLocation);

    //QImage myImage;
    //myImage.load(":/icons/server");
    //ui-> ->frameConnectionState->setPixmap(QPixmap::fromImage(myImage));
    //ui->

    readVSCPInterfaceConfig( config_vscpworks );
    writeVSCPInterfaceConfig( config_vscpworks );

    QStandardItemModel* model = new QStandardItemModel();

    QStandardItem* unconnected = new QStandardItem(QIcon(":/icons/disconnect"), "Unconnected Mode");
    QStandardItem* level1 = new QStandardItem(QIcon(":/icons/tools"), "Level I (CANAL) driver");
    QStandardItem* remote = new QStandardItem(QIcon(":/icons/server"), "VSCP standard remote TCP/IP interface");
    QStandardItem* sub1 = new QStandardItem("sub1 item");
    QStandardItem* sub2 = new QStandardItem("sub 2 item");

    model->appendRow(unconnected);
    model->appendRow(level1);
    level1->appendRow(sub1);
    level1->appendRow(sub2);

    model->appendRow(remote);

    while ( !config_vscpworks.isEmpty() ) {

        QMap<QString,QString> interface = config_vscpworks.takeFirst();

        if ( interface["interfacetype"] == "canal" ) {
            QStandardItem* sub = new QStandardItem( interface["description"] );
            level1->appendRow( sub );
        }
        else if ( interface["interfacetype"] == "tcpip" ) {
            QStandardItem* sub = new QStandardItem( interface["description"] );
            remote->appendRow( sub );
        }
    }

    ui->treeViewInterfaces->setModel( model );
}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::~DialogInterfaceSelect
///

DialogInterfaceSelect::~DialogInterfaceSelect()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::on_treeViewInterfaces_doubleClicked
/// \param index
/// Handle selection of interface through doubleclick.
///

void DialogInterfaceSelect::on_treeViewInterfaces_doubleClicked(const QModelIndex &index)
{

}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::readVSCPInterfaceConfig
/// \return
///

bool DialogInterfaceSelect::readVSCPInterfaceConfig( QList< QMap<QString,QString> > &config_vscpworks )
{
    QFile* file = new QFile("C:/Users/akhe/AppData/Roaming/vscpworks/vscpworks.conf");

    // If we can't open it, let's show an error message.
    if ( !file->open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        QMessageBox::critical( this,
                                  "QXSRExample::parseXML",
                                  "Couldn't open vscpworks.conf",
                                  QMessageBox::Ok);
        return false;
    }

    QXmlStreamReader xml( file );


    // We'll parse the XML until we reach end of it.
    while ( !xml.atEnd() && !xml.hasError() ) {

        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();

        // If token is just StartDocument, we'll go to next.
        if ( token == QXmlStreamReader::StartDocument ) {
            continue;
        }

        // If token is StartElement, we'll see if we can read it.
        if ( token == QXmlStreamReader::StartElement ) {

            // Check for top
            if ( xml.name() == "vscpworksconfig") {
                continue;
            }

            if ( xml.name() == "general") {
                config_vscpworks.append( this->parseGeneral( xml ) );
            }

            if ( xml.name() == "vscpclient") {
                config_vscpworks.append( this->parseClient( xml ) );
            }

            // Check for an interface
            if ( xml.name() == "canaldriver" ) {
                config_vscpworks.append( this->parseInterfaceCanal( xml ) );
            }

            // Check for an interface
            if ( xml.name() == "vscpdaemon" ) {
                config_vscpworks.append( this->parseInterfaceTcpip( xml ) );
            }

            // Let's check that we're really getting a person.
            if ( xml.tokenType() != QXmlStreamReader::StartElement &&
                    xml.name() == "person") {
                //return person;
            }

        }

    }

    // Error handling.
    if ( xml.hasError() ) {
        QMessageBox::critical( this,
                                  "QXSRExample::parseXML",
                                  xml.errorString(),
                                  QMessageBox::Ok);
    }

    // Removes any device() or data from the reader
    // and resets its internal state to the initial state.
    xml.clear();

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::parseInterfaceCanal
/// \param xml
/// \return
///
///

QMap<QString, QString> DialogInterfaceSelect::parseInterfaceCanal( QXmlStreamReader& xml )
{
    QMap<QString, QString> interface;

    // Set section
    interface.insert("xmlsection","vscpinterface");

    // Mark as a CANAL interface
    interface.insert("interfacetype","canal");

    // Let's check that we're really getting a CANAL interface.
    if ( xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "canaldriver") {
        return interface;
    }

    // Next element...
    xml.readNext();

    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named canaldriver.
     */
    while( !(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "canaldriver" ) ) {

        if ( xml.tokenType() == QXmlStreamReader::StartElement ) {

            // Description
            if ( xml.name() == "description" ) {
                this->addElementDataToMap( xml, interface );
            }

            // Path
            if ( xml.name() == "path" ) {
                this->addElementDataToMap( xml, interface );
            }

            // Config
            if ( xml.name() == "config" ) {
                this->addElementDataToMap( xml, interface );
            }

            // Flags
            if ( xml.name() == "flags" ) {
                this->addElementDataToMap( xml, interface );
            }
        }

        // ...and next...
        xml.readNext();

    }

    return interface;

}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::parseInterfaceTcpip
/// \param xml
/// \return
///

QMap<QString, QString> DialogInterfaceSelect::parseInterfaceTcpip( QXmlStreamReader& xml )
{

    QMap<QString, QString> interface;

    // Set section
    interface.insert("xmlsection","vscpinterface");

    // Mark as a TCP/IP interface
    interface.insert("interfacetype","tcpip");

    // Let's check that we're really getting a TCP/IP interface.
    if ( xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "vscpdaemon") {
        return interface;
    }

    // Next element...
    xml.readNext();

    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named canaldriver.
     */
    while( !(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "vscpdaemon" ) ) {

        if ( xml.tokenType() == QXmlStreamReader::StartElement ) {

            // Description
            if ( xml.name() == "description" ) {
                this->addElementDataToMap(xml, interface);
            }

            // Path
            if ( xml.name() == "path" ) {
                this->addElementDataToMap(xml, interface);
            }

            // Config
            if ( xml.name() == "config" ) {
                this->addElementDataToMap(xml, interface);
            }

            // Flags
            if ( xml.name() == "flags" ) {
                this->addElementDataToMap(xml, interface);
            }
        }

        // ...and next...
        xml.readNext();

    }

    return interface;

}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::parseGeneral
/// \param xml
/// \return
///

QMap<QString, QString> DialogInterfaceSelect::parseGeneral( QXmlStreamReader& xml )
{
    QMap<QString, QString> general;

    // Set section
    general.insert("xmlsection","general");

    // Let's check that we're really getting a CANAL interface.
    if ( xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "general") {
        return general;
    }

    // Next element...
    xml.readNext();

    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named canaldriver.
     */
    while( !(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "general" ) ) {

        if ( xml.tokenType() == QXmlStreamReader::StartElement ) {

            // width
            if ( xml.name() == "width" ) {
                this->addElementDataToMap( xml, general );
            }

            // heigh
            if ( xml.name() == "heigh" ) {
                this->addElementDataToMap( xml, general );
            }

            // xpos
            if ( xml.name() == "xpos" ) {
                this->addElementDataToMap( xml, general );
            }

            // ypos
            if ( xml.name() == "ypos" ) {
                this->addElementDataToMap( xml, general );
            }

            // path2tempfile
            if ( xml.name() == "path2tempfile" ) {
                this->addElementDataToMap( xml, general );
            }

            // path2logfile
            if ( xml.name() == "path2logfile" ) {

                // Get attributes
                QXmlStreamAttributes attributes = xml.attributes();

                // enable
                if ( attributes.hasAttribute("enable") ) {
                    general["path2logfile_enable"] = attributes.value("enable").toString();
                }

                // level
                if ( attributes.hasAttribute("level") ) {
                    general["path2logfile_level"] = attributes.value("level").toString();
                }

                this->addElementDataToMap( xml, general );

            }

            // RegisterReadResendTimeout
            if ( xml.name() == "RegisterReadResendTimeout" ) {
                this->addElementDataToMap( xml, general );
            }

            // RegisterReadErrorTimeout
            if ( xml.name() == "RegisterReadErrorTimeout" ) {
                this->addElementDataToMap( xml, general );
            }

            // RegisterReadMaxRetries
            if ( xml.name() == "RegisterReadMaxRetries" ) {
                this->addElementDataToMap( xml, general );
            }

            // NumberBase
            if ( xml.name() == "NumberBase" ) {
                this->addElementDataToMap( xml, general );
            }

            // ConfirmDelete
            if ( xml.name() == "ConfirmDelete" ) {
                this->addElementDataToMap( xml, general );
            }
        }

        // ...and next...
        xml.readNext();

    }

    return general;

}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::parseClient
/// \param xml
/// \return
///

QMap<QString, QString> DialogInterfaceSelect::parseClient( QXmlStreamReader& xml )
{
    QMap<QString, QString> client;

    // Set section
    client.insert("xmlsection","client");

    // Let's check that we're really getting a CANAL interface.
    if ( xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "vscpclient") {
        return client;
    }

    // Next element...
    xml.readNext();

    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named canaldriver.
     */
    while( !(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "vscpclient" ) ) {

        if ( xml.tokenType() == QXmlStreamReader::StartElement ) {

            // Autoscroll
            if ( xml.name() == "Autoscroll" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvPyjamasStyle
            if ( xml.name() == "VscpRcvPyjamasStyle" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpUseSymbolicNames
            if ( xml.name() == "VscpUseSymbolicNames" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvRowLineHeight
            if ( xml.name() == "VscpRcvRowLineHeight" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvShowField0
            if ( xml.name() == "VscpRcvShowField0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvShowField1
            if ( xml.name() == "VscpRcvShowField1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvShowField2
            if ( xml.name() == "VscpRcvShowField2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvShowField3
            if ( xml.name() == "VscpRcvShowField3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldOrder0
            if ( xml.name() == "VscpRcvFieldOrder0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldOrder1
            if ( xml.name() == "VscpRcvFieldOrder1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldOrder2
            if ( xml.name() == "VscpRcvFieldOrder2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldOrder3
            if ( xml.name() == "VscpRcvFieldOrder3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldText0
            if ( xml.name() == "VscpRcvFieldText0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldText1
            if ( xml.name() == "VscpRcvFieldText1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldText2
            if ( xml.name() == "VscpRcvFieldText2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldText3
            if ( xml.name() == "VscpRcvFieldText3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldWidth0
            if ( xml.name() == "VscpRcvFieldWidth0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldWidth1
            if ( xml.name() == "VscpRcvFieldWidth1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldWidth2
            if ( xml.name() == "VscpRcvFieldWidth2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFieldWidth3
            if ( xml.name() == "VscpRcvFieldWidth3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitShowField0
            if ( xml.name() == "VscpTrmitShowField0 " ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitShowField1
            if ( xml.name() == "VscpTrmitShowField1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitShowField2
            if ( xml.name() == "VscpTrmitShowField2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitShowField3
            if ( xml.name() == "VscpTrmitShowField3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitShowField4
            if ( xml.name() == "VscpTrmitShowField4" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitShowField5
            if ( xml.name() == "VscpTrmitShowField5" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldOrder0
            if ( xml.name() == "VscpTrmitFieldOrder0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldOrder1
            if ( xml.name() == "VscpTrmitFieldOrder1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldOrder2
            if ( xml.name() == "VscpTrmitFieldOrder2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldOrder3
            if ( xml.name() == "VscpTrmitFieldOrder3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldOrder4
            if ( xml.name() == "VscpTrmitFieldOrder4" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldOrder5
            if ( xml.name() == "VscpTrmitFieldOrder5" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldText0
            if ( xml.name() == "VscpTrmitFieldText0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldText1
            if ( xml.name() == "VscpTrmitFieldText1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldText2
            if ( xml.name() == "VscpTrmitFieldText2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldText3
            if ( xml.name() == "VscpTrmitFieldText3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldText4
            if ( xml.name() == "VscpTrmitFieldText4" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldText5
            if ( xml.name() == "VscpTrmitFieldText5" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldWidth0
            if ( xml.name() == "VscpTrmitFieldWidth0" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldWidth1
            if ( xml.name() == "VscpTrmitFieldWidth1" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldWidth2
            if ( xml.name() == "VscpTrmitFieldWidth2" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldWidth3
            if ( xml.name() == "VscpTrmitFieldWidth3" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldWidth4
            if ( xml.name() == "VscpTrmitFieldWidth4" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpTrmitFieldWidth5
            if ( xml.name() == "VscpTrmitFieldWidth5" ) {
                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFrameRxTextColour
            if ( xml.name() == "VscpRcvFrameRxTextColour" ) {

                // Get attributes
                QXmlStreamAttributes attributes = xml.attributes();

                // r
                if ( attributes.hasAttribute("r") ) {
                    client["VscpRcvFrameRxTextColour_r"] = attributes.value("enable").toString();
                }

                // g
                if ( attributes.hasAttribute("g") ) {
                    client["VscpRcvFrameRxTextColour_g"] = attributes.value("level").toString();
                }

                // b
                if ( attributes.hasAttribute("b") ) {
                    client["VscpRcvFrameRxTextColour_b"] = attributes.value("level").toString();
                }

                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFrameRxBgColour
            if ( xml.name() == "VscpRcvFrameRxBgColour" ) {

                // Get attributes
                QXmlStreamAttributes attributes = xml.attributes();

                // r
                if ( attributes.hasAttribute("r") ) {
                    client["VscpRcvFrameRxBgColour_r"] = attributes.value("enable").toString();
                }

                // g
                if ( attributes.hasAttribute("g") ) {
                    client["VscpRcvFrameRxBgColour_g"] = attributes.value("level").toString();
                }

                // b
                if ( attributes.hasAttribute("b") ) {
                    client["VscpRcvFrameRxBgColour_b"] = attributes.value("level").toString();
                }

                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFrameTxTextColour
            if ( xml.name() == "VscpRcvFrameTxTextColour" ) {

                // Get attributes
                QXmlStreamAttributes attributes = xml.attributes();

                // r
                if ( attributes.hasAttribute("r") ) {
                    client["VscpRcvFrameTxTextColour_r"] = attributes.value("enable").toString();
                }

                // g
                if ( attributes.hasAttribute("g") ) {
                    client["VscpRcvFrameTxTextColour_g"] = attributes.value("level").toString();
                }

                // b
                if ( attributes.hasAttribute("b") ) {
                    client["VscpRcvFrameTxTextColour_b"] = attributes.value("level").toString();
                }

                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFrameTxBgColour
            if ( xml.name() == "VscpRcvFrameTxBgColour" ) {

                // Get attributes
                QXmlStreamAttributes attributes = xml.attributes();

                // r
                if ( attributes.hasAttribute("r") ) {
                    client["VscpRcvFrameTxBgColour_r"] = attributes.value("enable").toString();
                }

                // g
                if ( attributes.hasAttribute("g") ) {
                    client["VscpRcvFrameTxBgColour_g"] = attributes.value("level").toString();
                }

                // b
                if ( attributes.hasAttribute("b") ) {
                    client["VscpRcvFrameTxBgColour_b"] = attributes.value("level").toString();
                }

                this->addElementDataToMap( xml, client );
            }

            // VscpRcvFrameLineColour
            if ( xml.name() == "VscpRcvFrameLineColour" ) {

                // Get attributes
                QXmlStreamAttributes attributes = xml.attributes();

                // r
                if ( attributes.hasAttribute("r") ) {
                    client["VscpRcvFrameLineColour_r"] = attributes.value("enable").toString();
                }

                // g
                if ( attributes.hasAttribute("g") ) {
                    client["VscpRcvFrameLineColour_g"] = attributes.value("level").toString();
                }

                // b
                if ( attributes.hasAttribute("b") ) {
                    client["VscpRcvFrameLineColour_b"] = attributes.value("level").toString();
                }

                this->addElementDataToMap( xml, client );
            }

        }

        // ...and next...
        xml.readNext();

    }

    return client;

}

///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::addElementDataToMap
/// \param xml
/// \param map
///

void DialogInterfaceSelect::addElementDataToMap( QXmlStreamReader& xml,
                                                    QMap<QString, QString>& map ) const
{
    // We need a start element, like <foo>
    if ( xml.tokenType() != QXmlStreamReader::StartElement ) {
        return;
    }

    // Let's read the name...
    QString elementName = xml.name().toString();

    // ...go to the next.
    xml.readNext();

    //
    // This elements needs to contain Characters so we know it's
    // actually data, if it's not we'll leave.
    //
    if ( xml.tokenType() != QXmlStreamReader::Characters ) {
        return;
    }

    // Now we can add it to the map.
    map.insert( elementName, xml.text().toString() );
}


///////////////////////////////////////////////////////////////////////////////
/// \brief DialogInterfaceSelect::readVSCPInterfaceConfig
/// \return
///

bool DialogInterfaceSelect::writeVSCPInterfaceConfig( QList< QMap<QString,QString> > &config_vscpworks )
{
    QFile* file = new QFile("C:/Users/akhe/AppData/Roaming/vscpworks/vscpworks2.conf");

    // If we can't open it, let's show an error message.
    if ( !file->open( QIODevice::ReadWrite | QIODevice::Text ) ) {
        QMessageBox::critical( this,
                                  "QXSRExample::parseXML",
                                  "Couldn't open vscpworks.conf",
                                  QMessageBox::Ok);
        return false;
    }

    QXmlStreamWriter xml( file );
    xml.setAutoFormatting( true );
    xml.writeStartDocument();

    // * * * G E N E R A L * * *
    xml.writeStartElement("general");
    {
        QMutableListIterator< QMap< QString,QString> > cfg(config_vscpworks);
        while ( cfg.hasNext() ) {
            cfg.next();
            //if ( ( cfg.key == "interfacetype" ) &&
            //    ( cfg.value == "general" ) ) {

            //}
        }
    }
    xml.writeEndElement();

    // * * * V S C P C L I E N T * * *
    xml.writeStartElement("vscpclient");
    xml.writeEndElement();


    // * * * V S C P I N T E R F A C E * * *
    xml.writeStartElement("vscpinterface");


    // * * * C A N A L D R I V E R * * *
    xml.writeStartElement("canaldriver");
    xml.writeEndElement();

    // * * * V S C P D A E M O N * * *
    xml.writeStartElement("vscpdaemon");
    xml.writeEndElement();

    xml.writeEndElement();


    // write your old data.
    //xml.writeStartElement("element");
    //xml.writeTextElement("atrib", "New");
    //xml.writeTextElement("atrib", "New");
    //xml.writeEndElement();
    //...
    xml.writeEndDocument();

    return true;
}
