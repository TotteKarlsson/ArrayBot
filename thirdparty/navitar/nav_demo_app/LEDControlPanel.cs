using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Navitar.Demos
{
    public partial class LEDControlPanel : NavitarControl
    {
        public LEDControlPanel(Controller controller) : base(controller)
        {
            InitializeComponent();

            buttonSettings.Hide();

            numericUpDownSetpoint.Minimum = 0;
            numericUpDownSetpoint.Maximum = 100;
            numericUpDownSetpoint.Increment = 0.1M;
            numericUpDownSetpoint.DecimalPlaces = 1;

            this.vScrollBarSetpoint.Maximum = 1000;
            this.vScrollBarSetpoint.Minimum = 0;
            this.vScrollBarSetpoint.LargeChange = 10;
            this.vScrollBarSetpoint.SmallChange = 1;
            // This next line is a royal hack needed so scroll can actually reach its maximum:
//            this.vScrollBarSetpoint.Maximum += this.vScrollBarSetpoint.LargeChange - 1;

            timerPolling.Interval = 50;
            timerPolling.Start();
        }

        private void timerPolling_Tick(object sender, EventArgs e)
        {
            if (MyController.Connected)
            {
                try
                {
                    int regValue;
                    if (timerPolling.Interval != 250)
                    {
                        timerPolling.Interval = 250;

                        // Initialize info from controller
                        regValue = MyController.Read(Controller.regVersionHW);
                        this.labelHWVersion.Text = regValue.ToString("X");
                        regValue = MyController.Read(Controller.regVersionSW);
                        this.labelFWVersion.Text = regValue.ToString("X");
                        regValue = MyController.Read(Controller.regVersionDate);
                        this.labelDateOfManufacture.Text = regValue.ToString("X");

                        regValue = MyController.Read(Controller.regSetupPwmDefault);

                        if (MyController.Generation == 1)
                        {
                            label5.Hide();
                            label6.Hide();
                            textBoxLED1.Hide();
                            textBoxLED2.Hide();
                        }
                    }

                    textBoxOnLine.Text = "On-Line";
                    textBoxOnLine.BackColor = Color.Green;
                    this.Enabled = true;

                    if (MyController.Generation == 2)
                    {
                        // poll for LED1 & LED2 status
                        int status = MyController.Read(Controller.regStatus_1);
                        textBoxLED1.BackColor = (((uint)status & 0x00000400) != 0) ? Color.Green : Color.LightGray;
                        textBoxLED2.BackColor = (((uint)status & 0x00000800) != 0) ? Color.Red : Color.LightGray;
                    }

                    int pwmVal = MyController.Read(Controller.regPwmAbsolute);
                    setPwmSetpoint(pwmVal);
                }
                catch (Exception)
                {
                }
            }
            else
            {
                textBoxOnLine.Text = "Off-Line";
                textBoxOnLine.BackColor = Color.Gray;
                this.Enabled = false;
                if (timerPolling.Interval != 5000)
                {
                    // Poll much more slowly if we are not connected
                    timerPolling.Interval = 5000;
                }

                // Attempt to reconnect
                try
                {
                    MyController.Connect();
                }
                catch (Exception)
                {
                }
            }
        }

        private void vScrollBarSetpoint_Scroll(object sender, ScrollEventArgs e)
        {
            setPwmSetpoint(vScrollBarSetpoint.Maximum - e.NewValue);
        }

        private void numericUpDownSetpoint_ValueChanged(object sender, EventArgs e)
        {
            setPwmSetpoint(Convert.ToInt32(numericUpDownSetpoint.Value * 10));
        }

//        private int PwmSetpoint { get; set; }

        private void setPwmSetpoint(int setpoint)
        {
            this.vScrollBarSetpoint.Scroll -= new System.Windows.Forms.ScrollEventHandler(this.vScrollBarSetpoint_Scroll);
            this.numericUpDownSetpoint.ValueChanged -= new System.EventHandler(this.numericUpDownSetpoint_ValueChanged);

            setpoint = Math.Min(setpoint, 1000);
            setpoint = Math.Max(0, setpoint);
            MyController.Write(Controller.regPwmAbsolute, setpoint);
            vScrollBarSetpoint.Value = vScrollBarSetpoint.Maximum - setpoint;
            numericUpDownSetpoint.Value = Convert.ToDecimal(setpoint) / 10;

            this.vScrollBarSetpoint.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBarSetpoint_Scroll);
            this.numericUpDownSetpoint.ValueChanged += new System.EventHandler(this.numericUpDownSetpoint_ValueChanged);
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            setPwmSetpoint(0);
        }

    }
}
