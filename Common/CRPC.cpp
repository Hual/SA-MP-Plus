#include <SAMP+/CRPC.h>

std::map<unsigned short, RPCFunct_t> CRPC::m_functions;

void CRPC::Add(unsigned short usRPCId, RPCFunct_t func)
{
	m_functions[usRPCId] = func;
}

void CRPC::Process(unsigned short usRPCId, RakNet::BitStream& bsData, int iExtra)
{
	std::map<unsigned short, RPCFunct_t>::iterator pValue = m_functions.find(usRPCId);

	if (pValue != m_functions.end())
		return pValue->second(bsData, iExtra);

}
