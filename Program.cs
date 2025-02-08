using System;
using Gtk;

class Program
{
    public static void Main()
    {
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
