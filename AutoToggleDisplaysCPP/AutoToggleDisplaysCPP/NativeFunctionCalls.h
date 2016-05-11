#include <Windows.h>
#ifndef NATIVE_FUNCTION_CALLS_INCLUDED
	#define NATIVE_FUNCTION_CALLS_INCLUDED
	
class NativeFunctionCalls
{
public:
	void ToggleDisplay();
	void SetAsMainMonitor(PDISPLAY_DEVICEW deviceToSet, DWORD devId);
};
#endif // !
