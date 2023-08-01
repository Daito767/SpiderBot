using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.IO;

namespace SpiderServer.Telemetry
{
	public class Server
	{
		private TcpListener Listener;
		private Thread ServerThread;
		private TcpClient? Client;
		private bool run = false;

		public Server(string ip, int port)
		{
			IPAddress localAddr = IPAddress.Parse(ip);
			Listener = new TcpListener(localAddr, port);
		}

		public void Start()
		{
			run = true;
			ServerThread = new Thread(RunServer);
			ServerThread.Start();
		}

		public void Stop()
		{
			run = false;
			Listener.Stop();
			if (ServerThread != null)
			{
				ServerThread.Interrupt();
			}

			Listener = null;
			ServerThread = null;
		}

		private void RunServer()
		{
			try
			{
				Listener.Start();

				while (true)
				{
					if (Client is not null && Client.Connected)
					{
						if (Client.Available > 0)
						{
							string message = Receive(Client);
						}
					}
					else
					{
						Client = Listener.AcceptTcpClient();
					}
				}

			}
			catch (SocketException e)
			{
				Console.WriteLine("SocketException: {0}", e);
			}
			finally
			{
				Listener.Stop();
			}
		}

		//private void RunServer()
		//{
		//	try
		//	{
		//		Listener.Start();
		//		TcpClient client = WaitClient();

		//		while (run)
		//		{
		//			string data = Receive(client);
		//		}

		//		client.Close();
		//	}
		//	catch (SocketException e)
		//	{
		//		Console.WriteLine("SocketException: {0}", e);
		//	}
		//	finally
		//	{
		//		Listener.Stop();
		//	}
		//}

		private string Receive(TcpClient client)
		{
			// Process the data sent by the client.
			byte[] bytes = new Byte[512];
			StringBuilder data = new StringBuilder();
			int i;

			Stream stream = client.GetStream();

			while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
			{
				// Translate data bytes to a string.
				string partialData = Encoding.ASCII.GetString(bytes, 0, i);
				data.Append(partialData);

				// If the end of the message has been reached
				if (partialData.ToString().EndsWith("\r"))
				{
					break;
				}
			}

			return data.ToString();
		}

		public bool Send(string message)
		{
			if (Client is null)
			{
				return false;
			}

			Stream stream = Client.GetStream();

			byte[] msg = Encoding.ASCII.GetBytes(message);
			stream.Write(msg, 0, msg.Length);

			return true;
		}
	}
}
