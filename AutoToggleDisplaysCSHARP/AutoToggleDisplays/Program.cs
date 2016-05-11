using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AutoToggleDisplays
{
    class Program
    {
        static void Main(string[] args)
        {
            ToggleDisplays d = new ToggleDisplays();
            d.ToggleMainMonitor();
        }
    }
}
