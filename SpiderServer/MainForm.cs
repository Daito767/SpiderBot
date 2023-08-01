using SpiderServer.Telemetry;

namespace SpiderServer
{
	public partial class MainForm : Form
	{
		private Server server { get; set; }

		public MainForm(Server server)
		{
			InitializeComponent();

			this.server = server;
			server.Start();
		}

		private void BtnFront_Click(object sender, EventArgs e)
		{
			server.Send("{\r\n  \"commands\": [\r\n    {\r\n      \"type\": \"step_front\",\r\n      \"count\": 1,\r\n      \"speed\": 50\r\n    }\r\n  ]\r\n}");
		}

		private void BtnBack_Click(object sender, EventArgs e)
		{
			server.Send("{\r\n  \"commands\": [\r\n    {\r\n      \"type\": \"step_back\",\r\n      \"count\": 1,\r\n      \"speed\": 50\r\n    }\r\n  ]\r\n}");
		}

		private void BtnRight_Click(object sender, EventArgs e)
		{
			server.Send("{\r\n  \"commands\": [\r\n    {\r\n      \"type\": \"turn_right\",\r\n      \"count\": 1,\r\n      \"speed\": 50\r\n    }\r\n  ]\r\n}");
		}

		private void BntLeft_Click(object sender, EventArgs e)
		{
			server.Send("{\r\n  \"commands\": [\r\n    {\r\n      \"type\": \"turn_left\",\r\n      \"count\": 1,\r\n      \"speed\": 50\r\n    }\r\n  ]\r\n}");
		}
	}
}