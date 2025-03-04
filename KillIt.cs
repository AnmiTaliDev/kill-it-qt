using Gtk;
using System.Diagnostics;
using System.Timers;

internal class KillIt : Window
{
    private Box _horizonBox;
    private Box _vertBox;

    private Label _name;
    private Label _timerLabel;
    private float _timeout;
    private static System.Timers.Timer _timer;
    
    private readonly Button _suspend;
	private readonly Button _hibernate;
    private readonly Button _reboot;
    private readonly Button _confirm;
    private readonly Button _cancel;

    public KillIt(Program.Settings settings) : base("Kill it")
    {
        SetDefaultSize(300, 100);
        SetPosition(WindowPosition.Center);
        BorderWidth = 10;
        _timeout = settings.Timer;
        _timer = new System.Timers.Timer(100);
        _timer.Elapsed += UpdateTimer;
        _timer.AutoReset = true;
        _timer.Enabled = true;

        _name = new Label("Want to Kill It? v1.3");
        _cancel = new Button("Cancel");
        _timerLabel = new Label($"Time to poweroff: {_timeout} ");
        
        _horizonBox = new Box(Orientation.Horizontal, 0);

        _cancel.Clicked += Cancel;
        _horizonBox.PackStart(_cancel, false, false, 10);

        if (settings.Modes != null && settings.Modes[0])
        {
            _hibernate = new Button("Hibernate");
            _hibernate.Clicked += Hibernate;
            _horizonBox.PackStart(_hibernate, false, false, 10);
        }

        if (settings.Modes != null &&settings.Modes[1])
        {
            _confirm = new Button("Power Off");
            _confirm.Clicked += Poweroff;
            _horizonBox.PackStart(_confirm, false, false, 10);
        }

        if (settings.Modes != null &&settings.Modes[2])
        {
            _suspend = new Button("Suspend");
            _suspend.Clicked += Suspend;
            _horizonBox.PackStart(_suspend, false, false, 10);
        }

        if (settings.Modes != null &&settings.Modes[3])
        {
            _reboot = new Button("Reboot");
            _reboot.Clicked += Reboot;
            _horizonBox.PackStart(_reboot, false, false, 10);
        }

        _vertBox = new Box(Orientation.Vertical, 0);
        _vertBox.PackStart(_name, false, false, 5);
        _vertBox.PackStart(_timerLabel, false, false, 10);
        _vertBox.PackStart(_horizonBox, false, false, 5);
        
        Add(_vertBox);
        ShowAll();
    }

    private void Hibernate(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "hibernate");
        System.Environment.Exit(0);
	}

    private void Poweroff(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "poweroff");
        System.Environment.Exit(0);
    }

    private void Suspend(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "suspend");
        System.Environment.Exit(0);
    }

    private void Reboot(object? sender, EventArgs e)
    {
        Process.Start("loginctl", "reboot");
        System.Environment.Exit(0);
    }
    
    private void Cancel(object? sender, EventArgs e)
    {
        System.Environment.Exit(0);
    }

    private void UpdateTimer(object? sender, ElapsedEventArgs e)
    {
        if (_timeout == 0)
            Poweroff(new object(), null);
        else if (_timeout > 0)
            _timeout -= 0.1f;
        _timerLabel.Text = "Time to poweroff: " + Math.Round(_timeout, 2);
    }
}

