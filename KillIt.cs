using Gtk;
using System;
using System.Diagnostics;
using System.Runtime.Loader;

internal class KillIt : Window
{
    private Box _horizonBox;
    private Box _vertBox;

    private Label _name;

    private readonly Button _suspend;
    private readonly Button _reboot;
    private readonly Button _confirm;
    private readonly Button _cancel;

    public KillIt() : base("Kill it")
    {
        SetDefaultSize(300, 100);
        SetPosition(WindowPosition.Center);
        BorderWidth = 10;

        _name = new Label("Want to Kill It? v1.2");

        _confirm = new Button("Power Off");
        _cancel = new Button("Cancel");
        _reboot = new Button("Reboot");
        _suspend = new Button("Suspend");

        _confirm.Clicked += Confirm;
        _cancel.Clicked += Cancel;
        _suspend.Clicked += Suspend;
        _reboot.Clicked += Reboot;

        _horizonBox = new Box(Orientation.Horizontal, 0);

        _horizonBox.PackStart(_cancel, false, false, 10);
        _horizonBox.PackStart(_confirm, false, false, 10);
        _horizonBox.PackStart(_reboot, false, false, 10);
        _horizonBox.PackStart(_suspend, false, false, 10);
        
        _vertBox = new Box(Orientation.Vertical, 0);
        _vertBox.PackStart(_name, false, false, 5);
        _vertBox.PackStart(_horizonBox, false, false, 5);
        
        Add(_vertBox);
        ShowAll();
    }

    private void Confirm(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "poweroff");
    }

    private void Suspend(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "suspend");
    }

    private void Reboot(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "reboot");
    }
    
    private void Cancel(object? sender, EventArgs e)
    {
        System.Environment.Exit(0);
    }
}

