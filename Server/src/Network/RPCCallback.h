#ifndef RPCCALLBACK_H
#define RPCCALLBACK_H

#include <Network/RPC.h>

class RPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK PlayerPauseMenuSwitch(RPC_ARGS);
	static RPC_CALLBACK PlayerPauseMenuBrowse(RPC_ARGS);

};

#endif
