using System;
using Gtk;
using System.Diagnostics;

class Program
{
    public static void Main()
    {
        Application.Init();

        var App = new KillIt();
        App.Resizable = false;
        App.DeleteEvent += delegate
        {
            Console.WriteLine("App Closed");
            Application.Quit();
        };        
        Application.Run();
    }
}
