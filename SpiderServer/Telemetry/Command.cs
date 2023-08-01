using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpiderServer.Telemetry
{
	internal struct Command
	{
		public string Type { get; set; }
		public int Count { get; set; }
		public int Speed { get; set; }
	}
}
