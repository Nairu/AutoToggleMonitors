using System;
using System.Runtime.InteropServices;

namespace AutoToggleDisplays
{
    public class ToggleDisplays
    {
        public void ToggleMainMonitor()
        {
            DISPLAY_DEVICE d = new DISPLAY_DEVICE(0);

            int mainMonitor = -1;
            int secondaryMonitor = -1;

            int devNum = 0;
            bool result;
            do
            {
                result = NativeMethods.EnumDisplayDevices(IntPtr.Zero, devNum, ref d, 0);

                if (result)
                {
                    if ((d.StateFlags & DisplayDeviceStateFlags.PrimaryDevice) != 0)
                    {
                        mainMonitor = devNum;
                    }

                    else if ((d.StateFlags & DisplayDeviceStateFlags.AttachedToDesktop) != 0)
                    {
                        secondaryMonitor = devNum;
                    }                    
                }

                devNum++;
            } while (mainMonitor == -1 || secondaryMonitor == -1);

            SetAsPrimaryMonitor(secondaryMonitor);            
            SetAsPrimaryMonitor(mainMonitor);
        }

        public static void SetAsPrimaryMonitor(int id)
        {
            var device = new DISPLAY_DEVICE();
            var deviceMode = new DEVMODE();
            device.cb = Marshal.SizeOf(device);

            NativeMethods.EnumDisplayDevices(IntPtr.Zero, id, ref device, 0);
            NativeMethods.EnumDisplaySettings(device.DeviceName, -1, ref deviceMode);
            var offsetx = deviceMode.dmPosition.x;
            var offsety = deviceMode.dmPosition.y;
            deviceMode.dmPosition.x = 0;
            deviceMode.dmPosition.y = 0;

            NativeMethods.ChangeDisplaySettingsEx(
                device.DeviceName,
                ref deviceMode,
                (IntPtr)null,
                (ChangeDisplaySettingsFlags.CDS_SET_PRIMARY | ChangeDisplaySettingsFlags.CDS_UPDATEREGISTRY | ChangeDisplaySettingsFlags.CDS_NORESET),
                IntPtr.Zero);

            device = new DISPLAY_DEVICE();
            device.cb = Marshal.SizeOf(device);

            // Update remaining devices
            for (int otherid = 0; NativeMethods.EnumDisplayDevices(IntPtr.Zero, otherid, ref device, 0); otherid++)
            {
                if (device.StateFlags.HasFlag(DisplayDeviceStateFlags.AttachedToDesktop) && otherid != id)
                {
                    device.cb = Marshal.SizeOf(device);
                    var otherDeviceMode = new DEVMODE();

                    NativeMethods.EnumDisplaySettings(device.DeviceName, -1, ref otherDeviceMode);

                    otherDeviceMode.dmPosition.x -= offsetx;
                    otherDeviceMode.dmPosition.y -= offsety;

                    NativeMethods.ChangeDisplaySettingsEx(
                        device.DeviceName,
                        ref otherDeviceMode,
                        (IntPtr)null,
                        (ChangeDisplaySettingsFlags.CDS_UPDATEREGISTRY | ChangeDisplaySettingsFlags.CDS_NORESET),
                        IntPtr.Zero);

                }

                device.cb = Marshal.SizeOf(device);
            }

            // Apply settings
            NativeMethods.ChangeDisplaySettingsEx(null, IntPtr.Zero, (IntPtr)null, ChangeDisplaySettingsFlags.CDS_NONE, (IntPtr)null);
        }

        private string GetDeviceName(int devNum)
        {
            DISPLAY_DEVICE d = new DISPLAY_DEVICE(0);
            bool result = NativeMethods.EnumDisplayDevices(IntPtr.Zero,
                devNum, ref d, 0);
            return (result ? d.DeviceName.Trim() : "#error#");
        }
    }

    public class NativeMethods
    {
        [DllImport("User32.dll")]
        public static extern bool EnumDisplayDevices(
            IntPtr lpDevice, int iDevNum,
            ref DISPLAY_DEVICE lpDisplayDevice, int dwFlags);

        [DllImport("User32.dll")]
        public static extern bool EnumDisplaySettings(
            string devName, int modeNum, ref DEVMODE devMode);

        [DllImport("user32.dll")]
        public static extern DISP_CHANGE ChangeDisplaySettingsEx(string lpszDeviceName, ref DEVMODE lpDevMode, IntPtr hwnd, ChangeDisplaySettingsFlags dwflags, IntPtr lParam);

        [DllImport("user32.dll")]
        public static extern DISP_CHANGE ChangeDisplaySettingsEx(string lpszDeviceName, IntPtr lpDevMode, IntPtr hwnd, ChangeDisplaySettingsFlags dwflags, IntPtr lParam);
    }
}
