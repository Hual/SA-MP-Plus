using System;

namespace SAMP_Server_Browser_File_Parser
{
    class Server
    {
        private String m_strAddress, m_strHostname;
        private uint m_uiPort;

        public Server(String strAddress, uint uiPort, String strHostname)
        {
            m_strAddress = strAddress;
            m_uiPort = uiPort;
            m_strHostname = strHostname;
        }

        public void SetHostname(String strHostname)
        {
            m_strHostname = strHostname;
        }

        public void setAddress(String strAddress)
        {
            m_strAddress = strAddress;
        }

        public void setPort(uint uiPort)
        {
            m_uiPort = uiPort;
        }

        public String GetHostname()
        {
            return m_strHostname;
        }

        public String GetAddress()
        {
            return m_strAddress;
        }

        public uint GetPort()
        {
            return m_uiPort;
        }
    }
}
