#include "stdafx.h"
#include <Windows.h>
#include "NativeFunctionCalls.h"

void NativeFunctionCalls::ToggleDisplay()
{
	BOOL bResult = TRUE;
	DISPLAY_DEVICE DispDev;

	ZeroMemory(&DispDev, sizeof(DISPLAY_DEVICE));
	DispDev.cb = sizeof(DISPLAY_DEVICE);

	DISPLAY_DEVICE MainMonitor;
	LONG MainMonitorID{ -1 };
	ZeroMemory(&MainMonitor, sizeof(DISPLAY_DEVICE));
	MainMonitor.cb = sizeof(DISPLAY_DEVICE);

	DISPLAY_DEVICE SecondaryMonitor;
	LONG SecondaryMonitorID{ -1 };
	ZeroMemory(&SecondaryMonitor, sizeof(DISPLAY_DEVICE));
	SecondaryMonitor.cb = sizeof(DISPLAY_DEVICE);

	BOOL result{ FALSE };
	DWORD devNum{ 0 };

	do 
	{
		result = EnumDisplayDevices(NULL, devNum, &DispDev, 0);
		

		if (result)
		{
			if ((DispDev.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0)
			{
				MainMonitor = DispDev;
				MainMonitorID = devNum;
			}
			else if ((DispDev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0)
			{
				SecondaryMonitor = DispDev;
				SecondaryMonitorID = devNum;
			}
		}
		devNum++;
	} while (MainMonitorID == -1 || SecondaryMonitorID == -1);
	
	SetAsMainMonitor(&SecondaryMonitor, SecondaryMonitorID);
	SetAsMainMonitor(&MainMonitor, MainMonitorID);
}

void NativeFunctionCalls::SetAsMainMonitor(PDISPLAY_DEVICEW deviceToSet, DWORD devId)
{
	DEVMODE DeviceMode;
	ZeroMemory(&DeviceMode, sizeof(DEVMODE));

	if (EnumDisplaySettings(deviceToSet->DeviceName, -1, &DeviceMode))
	{
		LONG offsetX = DeviceMode.dmPosition.x;
		LONG offsetY = DeviceMode.dmPosition.y;
		DeviceMode.dmPosition.x = 0;
		DeviceMode.dmPosition.y = 0;

		ChangeDisplaySettingsEx(deviceToSet->DeviceName, &DeviceMode, NULL, (CDS_SET_PRIMARY | CDS_UPDATEREGISTRY | CDS_NORESET), NULL);

		ZeroMemory(deviceToSet, sizeof(DISPLAY_DEVICE));
		deviceToSet->cb = sizeof(DISPLAY_DEVICE);

		for (DWORD i = 0; EnumDisplayDevices(NULL, i, deviceToSet, 0); i++)
		{
			if (((deviceToSet->StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0) && i != devId)
			{
				DEVMODE otherDev;
				ZeroMemory(&otherDev, sizeof(DEVMODE));

				EnumDisplaySettings(deviceToSet->DeviceName, -1, &otherDev);

				otherDev.dmPosition.x -= offsetX;
				otherDev.dmPosition.y -= offsetY;

				ChangeDisplaySettingsEx(deviceToSet->DeviceName, &otherDev, NULL, (CDS_UPDATEREGISTRY | CDS_NORESET), NULL);
			}

			deviceToSet->cb = sizeof(DISPLAY_DEVICE);
		}

		ChangeDisplaySettingsEx(NULL, NULL, NULL, 0, NULL);
	}
	else
	{
		return;
	}
}