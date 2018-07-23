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
    public partial class TwoAxisControlPanel : NavitarControl
    {
        public TwoAxisControlPanel(Controller controller) : base(controller)
        {
            InitializeComponent();

            // Add the Axis controls manually because the designer apparently 
            // cannot handle non-default construction.
            this.motionAxis1 = new MotionAxis(MyController, 0);
            this.motionAxis1.Location = new System.Drawing.Point(4, 4);
            this.motionAxis1.Name = "motionAxis1";
            this.motionAxis1.Size = new System.Drawing.Size(322, 335);
            this.motionAxis1.TabIndex = 0;
            this.Controls.Add(this.motionAxis1);

            this.motionAxis2 = new MotionAxis(MyController, 1);
            this.motionAxis2.Location = new System.Drawing.Point(333, 4);
            this.motionAxis2.Name = "motionAxis2";
            this.motionAxis2.Size = new System.Drawing.Size(322, 335);
            this.motionAxis2.TabIndex = 1;
            this.Controls.Add(this.motionAxis2);

            timerPolling.Interval = 50;
            timerPolling.Start();
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            motionAxis1.Stop();
            motionAxis2.Stop();
            try
            {
                MyController.Stop();
            }
            catch (Exception)
            {
            }
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
                        int major = (int)(((uint)regValue & 0xff000000) >> 24);
                        int minor = (int)(((uint)regValue & 0xff0000) >> 16);
                        int rev = (int)(((uint)regValue & 0xff00) >> 8);
                        int bug = (int)((uint)regValue & 0xff);
                        this.labelHWVersion.Text = major.ToString() + "." + minor.ToString() + "." + rev.ToString() + "." + bug.ToString();
                        regValue = MyController.Read(Controller.regVersionSW);
                        major = (int)(((uint)regValue & 0xff000000) >> 24);
                        minor = (int)(((uint)regValue & 0xff0000) >> 16);
                        rev = (int)(((uint)regValue & 0xff00) >> 8);
                        bug = (int)((uint)regValue & 0xff);
                        this.labelFWVersion.Text = major.ToString() + "." + minor.ToString() + "." + rev.ToString() + "." + bug.ToString();
                        regValue = MyController.Read(Controller.regVersionDate);
                        major = (int)(((uint)regValue & 0xff000000) >> 24);
                        minor = (int)(((uint)regValue & 0xff0000) >> 16);
                        rev = (int)(((uint)regValue & 0xff00) >> 8);
                        bug = (int)((uint)regValue & 0xff);
                        DateTime date = new DateTime(rev + 2000, major, minor);
                        this.labelDateOfManufacture.Text = date.ToShortDateString();

                        regValue = MyController.Read(Controller.regSetupConfig_2);
                        if ((regValue & 0x04) != 0)
                        {
                            this.motionAxis2.Enabled = false;
                        }

                        if (MyController.Generation == 1)
                        {
                            label4.Hide();
                            labelSerialNumber.Hide();
                            label5.Hide();
                            label6.Hide();
                            textBoxLED1.Hide();
                            textBoxLED2.Hide();
                        }
                        else if (MyController.Generation == 2)
                        {
                            regValue = MyController.Read(Controller.regProductSerialNum);
                            labelSerialNumber.Text = regValue.ToString();
                        }
                    }

                    textBoxOnLine.Text = "On-Line";
                    textBoxOnLine.BackColor = Color.Green;
                    this.Enabled = true;

                    // TODO: Add polling for LED1 & LED2 status
                    int status = MyController.Read(Controller.regStatus_1);
                    textBoxLED1.BackColor = (((uint)status & 0x00000400) != 0) ? Color.Green : Color.LightGray;
                    textBoxLED2.BackColor = (((uint)status & 0x00000800) != 0) ? Color.Red : Color.LightGray;

                    motionAxis1.UpdateAxis();

                    // Check for disabled 2nd axis here
                    regValue = MyController.Read(Controller.regSetupConfig_2);
                    if ((regValue & 0x04) == 0)
                    {
                        motionAxis2.UpdateAxis();
                    }
                    else
                    {
                        this.motionAxis2.Enabled = false;
                    }
                }
                catch (Exception)
                {
                    MyController.Disconnect();
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

        private void buttonSettings_Click(object sender, EventArgs e)
        {
            if (motionAxis1.Moving || motionAxis2.Moving)
            {
                MessageBox.Show("Motion must be stopped before setup parameters may be modified.");
                return;
            }

            if (MyController.Connected)
            {
                SetupDialog setup = new SetupDialog(MyController);
                setup.ShowDialog();
            }
        }
    }
}
