#include "stdafx.h"
#include <Windows.h>

//typedef struct _DISPLAY_DEVICE {
//	DWORD cb;
//	TCHAR DeviceName[32];
//	TCHAR DeviceString[128];
//	DWORD StateFlags;
//	TCHAR DeviceID[128];
//	TCHAR DeviceKey[128];
//} DISPLAY_DEVICE, *PDISPLAY_DEVICE;
//
//typedef struct _devicemode {
//	TCHAR dmDeviceName[CCHDEVICENAME];
//	WORD  dmSpecVersion;
//	WORD  dmDriverVersion;
//	WORD  dmSize;
//	WORD  dmDriverExtra;
//	DWORD dmFields;
//	union {
//		struct {
//			short dmOrientation;
//			short dmPaperSize;
//			short dmPaperLength;
//			short dmPaperWidth;
//			short dmScale;
//			short dmCopies;
//			short dmDefaultSource;
//			short dmPrintQuality;
//		};
//		struct {
//			POINTL dmPosition;
//			DWORD  dmDisplayOrientation;
//			DWORD  dmDisplayFixedOutput;
//		};
//	};
//	short dmColor;
//	short dmDuplex;
//	short dmYResolution;
//	short dmTTOption;
//	short dmCollate;
//	TCHAR dmFormName[CCHFORMNAME];
//	WORD  dmLogPixels;
//	DWORD dmBitsPerPel;
//	DWORD dmPelsWidth;
//	DWORD dmPelsHeight;
//	union {
//		DWORD dmDisplayFlags;
//		DWORD dmNup;
//	};
//	DWORD dmDisplayFrequency;
//#if (WINVER >= 0x0400)
//	DWORD dmICMMethod;
//	DWORD dmICMIntent;
//	DWORD dmMediaType;
//	DWORD dmDitherType;
//	DWORD dmReserved1;
//	DWORD dmReserved2;
//#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
//	DWORD dmPanningWidth;
//	DWORD dmPanningHeight;
//#endif 
//#endif 
//} DEVMODE, *PDEVMODE, *LPDEVMODE;
//
//typedef struct POINTL
//{
//	int x;
//	int y;
//};
//
//typedef enum DM : int
//{
//	Orientation = 0x1,
//	PaperSize = 0x2,
//	PaperLength = 0x4,
//	PaperWidth = 0x8,
//	Scale = 0x10,
//	Position = 0x20,
//	NUP = 0x40,
//	DisplayOrientation = 0x80,
//	Copies = 0x100,
//	DefaultSource = 0x200,
//	PrintQuality = 0x400,
//	Color = 0x800,
//	Duplex = 0x1000,
//	YResolution = 0x2000,
//	TTOption = 0x4000,
//	Collate = 0x8000,
//	FormName = 0x10000,
//	LogPixels = 0x20000,
//	BitsPerPixel = 0x40000,
//	PelsWidth = 0x80000,
//	PelsHeight = 0x100000,
//	DisplayFlags = 0x200000,
//	DisplayFrequency = 0x400000,
//	ICMMethod = 0x800000,
//	ICMIntent = 0x1000000,
//	MediaType = 0x2000000,
//	DitherType = 0x4000000,
//	PanningWidth = 0x8000000,
//	PanningHeight = 0x10000000,
//	DisplayFixedOutput = 0x20000000
//};
//
//typedef enum DISPLAY_DEVICE_STATE_FLAGS : int
//{
//	AttachedToDesktop = 0x1,
//	MultiDriver = 0x2,
//	PrimaryDevice = 0x4,
//	MirroringDriver = 0x8,
//	VGACompatible = 0x10,
//	Removable = 0x20,
//	Disconnect = 0x2000000,
//	Remote = 0x4000000,
//	ModesPruned = 0x8000000
//};
//
//typedef enum CHANGE_DISPLAY_SETTINGS_FLAGS : int
//{
//	CdsNone = 0x00000000,
//	CdsUpdateEegistry = 0x00000001,
//	CdsTest = 0x00000002,
//	CdsFullscreen = 0x00000004,
//	CdsGlobal = 0x00000008,
//	CdsSetPrimary = 0x00000010,
//	CdsVideoParameters = 0x00000020,
//	CdsEnableUnsafeModes = 0x00000100,
//	CdsDisableUnsafeModes = 0x00000200,
//	CdsReset = 0x40000000,
//	CdsResetEx = 0x20000000,
//	CdsNoReset = 0x10000000
//};
//
//typedef enum DISP_CHANGE_ENUM : int
//{
//	Succesful = 0,
//	Restart = 1,
//	Failed = -1,
//	BadMode = -2,
//	NotUpdated = -3,
//	BadFlags = -4,
//	BadParam = -5,
//	BadDualView = -6
//};