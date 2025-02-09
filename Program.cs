using System;
using Gtk;
using System.Diagnostics;

class Program
{
    public static void Main()
    {
        Process.Start("sudo", "ls");
        Application.Init();
        var App = new KillIt();
        App.Resizable = true;
        App.DeleteEvent += delegate
        {
            Console.WriteLine("App Closed");
            Application.Quit();
        };        
        Application.Run();
    }
}
