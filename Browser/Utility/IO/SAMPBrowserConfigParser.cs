using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace SAMP_Server_Browser_File_Parser.IO
{
    class SAMPBrowserConfigParser
    {
        private static readonly byte[] m_byteSAMP = { 0x53, 0x41, 0x4d, 0x50 };

        public static String GetDataFilePath()
        {
            return (System.Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) + @"\GTA San Andreas User Files\SAMP\USERDATA.DAT");
        }

        public static bool Load(String strFilePath, ref List<Server> lServers)
        {
            if(!File.Exists(strFilePath))
                return false;

            byte[] contents = File.ReadAllBytes(strFilePath);

            if(contents.Length < 12)
                return false;

            if (System.Text.Encoding.ASCII.GetString(contents, 0, 4) != "SAMP")
                return false;

            uint uiVersion, uiServers;

            if ((uiVersion = BitConverter.ToUInt32(contents, 4)) != 1)
                return false;

            if ((uiServers = BitConverter.ToUInt32(contents, 8)) == 0)
                return false;

            int iPos = 12;

            try
            {
                int iLen;
                uint uiPort;
                String strAddress, strHostname;

                for (uint i = 0; i < uiServers; ++i)
                {
                    iLen = BitConverter.ToInt32(contents, iPos);
                    strAddress = System.Text.Encoding.ASCII.GetString(contents, iPos + 4, iLen);
                    iPos += iLen + 4;

                    uiPort = BitConverter.ToUInt32(contents, iPos);
                    iLen = BitConverter.ToInt32(contents, iPos + 4);
                    strHostname = System.Text.Encoding.UTF8.GetString(contents, iPos + 8, iLen);
                    iPos += iLen + 16;

                    lServers.Add(new Server(strAddress, uiPort, strHostname));
                    //TODO: add to list
                }

                return true;
            }
            catch(Exception)
            {
                return false;
            }
        }

        public static void Save(String strFilePath, List<Server> lServers)
        {
            BinaryWriter binaryWriter = new BinaryWriter(File.Open(strFilePath, FileMode.Create, FileAccess.Write, FileShare.Write));

            binaryWriter.Write(m_byteSAMP);
            binaryWriter.Write((uint)1);
            binaryWriter.Write((uint)lServers.Count);
            
            foreach(Server server in lServers)
            {
                binaryWriter.Write((uint)server.GetAddress().Length);
                binaryWriter.Write(Encoding.ASCII.GetBytes(server.GetAddress()));
                binaryWriter.Write(server.GetPort());
                binaryWriter.Write((uint)server.GetHostname().Length);
                binaryWriter.Write(Encoding.UTF8.GetBytes(server.GetHostname()));
                binaryWriter.Write((ulong)0);
            }

            binaryWriter.Close();
        }
    }
}
