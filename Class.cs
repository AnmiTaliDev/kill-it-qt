using Gtk;
using System;
using System.Diagnostics;

internal class KillIt : Window
{
    private Button _confirm;
    private Button _cancel;

    private Box _horizonBox;
    private Box _vertBox;

    private Label _name;

    public KillIt() : base("Kill it")
    {
        SetDefaultSize(300, 100);
        SetPosition(WindowPosition.Center);
      
        _name = new Label("Want to Kill It?");

        _confirm = new Button("Yes");
        _cancel = new Button("No");

        _confirm.Clicked += Confirm;
        _cancel.Clicked += Cancel;

        _horizonBox = new Box(Orientation.Horizontal, 0);
        _horizonBox.PackStart(_confirm, false, false, 50);
        _horizonBox.PackStart(_cancel, false, false, 50);
        
        _vertBox = new Box(Orientation.Vertical, 0);
        _vertBox.PackStart(_name, false, false, 5);
        _vertBox.PackStart(_horizonBox, false, false, 5);
        
        Add(_vertBox);
        ShowAll();
    }

    private void Confirm(object? sender, EventArgs e)
    {
        Process.Start("sudo", "poweroff");
    }
    
    private void Cancel(object? sender, EventArgs e)
    {
        System.Environment.Exit(0);
    }
}

