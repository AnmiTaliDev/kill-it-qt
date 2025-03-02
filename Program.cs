using System;
using Gtk;
using System.Diagnostics;
using System.IO;

class Program
{
	private bool[] _modes;
	private float _timer = 30f;

	public struct Settings
	{
		public bool[] Modes { get; init; } = {true, true, true, true};
		public float Timer { get; init; }

		public Settings(bool[] modes, float timer)
		{
			for (byte i = 0; i <= Modes.Length; i++)
			{
				try
				{
					Modes[i] = modes[i];
				}
				catch
				{
					Console.WriteLine("modes end");
				}
			}

			Timer = timer;
		}
	}

    public static void Main()
    {
        Application.Init();
        
		Settings settings = ReadFile("/etc/killit/killit.conf");
		
        var app = new KillIt(settings);
        app.Resizable = false;
        app.DeleteEvent += delegate
        {
            Console.WriteLine("App Closed");
            Application.Quit();
        };        
        Application.Run();
    }

	private static Settings ReadFile(string path)
	{
		Settings result = new Settings();
		
		try
		{
			using StreamReader reader = new( path );

		    string text = reader.ReadToEnd();
			result = SettingsSet(text);
		}
		catch (IOException e)
		{
			Console.WriteLine("The file could not be read:");
			Console.WriteLine(e.Message);
		}

		return result;
	}

	private static Settings SettingsSet(string raw)
	{
		bool[] modes = new bool[] {true, true, true, true, true};
		float timer = 30f;
		string[] lines = raw.Split('\n');
		string name = "";
		string value = "";
		bool flag = false;
		
		foreach (string line in lines)
		{
			foreach (char item in line)
			{
				
				if (item == '=')
				{
					flag = true;
					continue;
				}
				
				if (flag)
					value += item;
				else
					name += item;
			}
			flag = false;

			try
			{
				switch (name)
				{
					case null:
						break;
					
					default:
						Console.WriteLine($"Error parsing config: {name} is not defined");
						break;

					case "hibernate":
						if (Convert.ToBoolean(value))
							modes[0] = true;
						else
							modes[0] = false;
						break;

					case "poweroff":
						if (Convert.ToBoolean(value))
							modes[2] = true;
						else
							modes[2] = false;
						break;

					case "suspend":
						if (Convert.ToBoolean(value))
							modes[1] = true;
						else
							modes[1] = false;
						break;

					case "reboot":
						if (Convert.ToBoolean(value)) 
							modes[3] = true;
						else
							modes[3] = false;
						break;

					case "timer":
						if (Convert.ToSingle(value) > 0f)
							timer = Convert.ToSingle(value);
						else
							Console.WriteLine("Error parsing config: timer is below 0");
						break;
				}
			}
			catch (Exception e)
			{
				Console.WriteLine("Error parsing config: " + e.Message);
			}

			name = "";
			value = "";
		}
		
		Settings result = new Settings(modes, timer);
		Console.WriteLine(result.Modes[0]);
		return result;
	}
}
