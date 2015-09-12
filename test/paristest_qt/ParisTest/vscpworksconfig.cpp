#include "vscpworksconfig.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief canalInterface::canalInterface
///

canalInterface::canalInterface()
{
    m_flags = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief tcpipInterface::tcpipInterface
///

tcpipInterface::tcpipInterface()
{
    m_strHost = "localhost";
    m_strUser = "admin";
    m_strPassword = "secret";
    m_port = VSCP_LEVEL2_TCP_PORT;
    m_bLevel2 = false;
    clearVSCPFilter( &m_vscpfilter );
}

///////////////////////////////////////////////////////////////////////////////
/// \brief vscpworksconfig::vscpworksconfig
///

vscpworksconfig::vscpworksconfig()
{

}
