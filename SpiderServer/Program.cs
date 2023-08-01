using SpiderServer.Telemetry;

namespace SpiderServer
{
	internal static class Program
	{
		/// <summary>
		///  The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			ApplicationConfiguration.Initialize();

			Server server = new Server("0.0.0.0", 8070);

			Application.Run(new MainForm(server));
		}
	}
}