using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Navitar.Demos
{
    public partial class MotionAxis : UserControl
    {
        private const int PRODUCT_GEN_2_CONTROLLER = 0x5001;

        private const uint STATUS_MOTOR_TYPE_BITS = 0x00006000;
        private const int STATUS_MOTOR_TYPE_SHIFT = 13;

        private const uint STATUS_BITS_INSUFFICIENT_VOLTAGE = 0x00001000;

        private const uint MOTOR_TYPE_1 = 0x00;
        private const uint MOTOR_TYPE_2 = 0x01;
        private const uint MOTOR_TYPE_3 = 0x02;
        private const uint MOTOR_TYPE_4 = 0x03;

        private const uint TWO_PHASE_UNKNOWN_MOTOR = MOTOR_TYPE_1;
        private const uint TWO_PHASE_AM0820_MOTOR = MOTOR_TYPE_2;
        private const uint TWO_PHASE_AM1524_MOTOR = MOTOR_TYPE_3;
        private const uint TWO_PHASE_UNKNOWN_OPEN_SHORT = MOTOR_TYPE_4;

        private const string UNKNOWN_MOTOR_STR = "Unknown";
        private const string AM0820_MOTOR_STR = "AM0820";
        private const string AM1524_MOTOR_STR = "AM1524";

        private const string ZOOM_STR = "Zoom";
        private const string FOCUS_STR = "Focus";

        private const string INSUFFICIENT_VOLTAGE_STR = "Insufficient Voltage";

        public MotionAxis()
            : this(null, 0)
        {
        }

        public MotionAxis(Controller controller, int axis)
        {
            MyController = controller;
            Axis = axis;
            RegOffset = Axis == 1 ? Controller.regOffsetMotor2 : 0;
            AutoStepping = false;
            Idle = false;

            InitializeComponent();

            groupBoxAxis.Text = Axis == 0 ? "Zoom" : "Focus";

            // Nasty hack to eliminate annoying animation of progressbar:
            SetWindowTheme(this.vProgressPosition.Handle, "", "");
            this.vProgressPosition.ForeColor = Color.Green;
            this.vProgressPosition.BackColor = Color.LightGray;

            NextStep = checkBoxAuto1;

            UpdateAxis();
        }

        [DllImport("uxtheme", ExactSpelling = true, CharSet = CharSet.Unicode)]
        public extern static Int32 SetWindowTheme(IntPtr hWnd, String textSubAppName, String textSubIdList);

        /// <summary>
        /// Poll for axis motor status and update appropriate motor position and
        /// status controls.  Must be called periodically to keep controls up to date.
        /// </summary>
        public void UpdateAxis()
        {
            int regVal;

            if (MyController.Connected)
            {
                try
                {
                    int status = MyController.Read(Controller.regStatus_1 + RegOffset);

                    if (MyController.ProductID == PRODUCT_GEN_2_CONTROLLER)
                    {
                        groupBoxAxis.Text = Axis == 0 ? ZOOM_STR : FOCUS_STR;

                        if (((uint)status & STATUS_BITS_INSUFFICIENT_VOLTAGE) != 0)
                        {
                            groupBoxAxis.Text += " (";
                            groupBoxAxis.Text += INSUFFICIENT_VOLTAGE_STR;
                            groupBoxAxis.Text += " )";
                        }
                        // If this is a Gen 2 two-phase controller, then the motor type should be identifible.
                        else if ((MyController.ProductSubclass == 2) ||
                                 (MyController.ProductSubclass == 3) ||
                                 (MyController.ProductSubclass == 1) ||
                                 (MyController.ProductSubclass == (unchecked((int)0xffffffd9))))
                        {
                            uint motorId = ((uint)status & STATUS_MOTOR_TYPE_BITS) >> STATUS_MOTOR_TYPE_SHIFT;

                            groupBoxAxis.Text += " (";

                            switch (motorId)
                            {
                                case TWO_PHASE_AM0820_MOTOR:
                                    groupBoxAxis.Text += AM0820_MOTOR_STR;
                                    break;

                                case TWO_PHASE_AM1524_MOTOR:
                                    groupBoxAxis.Text += AM1524_MOTOR_STR;
                                    break;

                                case TWO_PHASE_UNKNOWN_MOTOR:       // Intentional fall through
                                case TWO_PHASE_UNKNOWN_OPEN_SHORT:  // Intentional fall through
                                default:
                                    groupBoxAxis.Text += UNKNOWN_MOTOR_STR;
                                    break;
                            }

                            groupBoxAxis.Text += ")";
                        }
                    }

                    Idle = (((uint)status & 0x000000ff) == 0) ? true : false;
                    buttonAtHome.BackColor = (((uint)status & 0x00000100) != 0) ? Color.Red : Color.LightGray;
                    buttonAtLimit.BackColor = (((uint)status & 0x00000200) != 0) ? Color.Red : Color.LightGray;

                    // Fetch motor limit position value.
                    regVal = MyController.Read(Controller.regSetupLimit_1 + RegOffset);
                    if (regVal == 0)
                    {
                        this.Enabled = false;
                        return;
                    }
                    else
                    {
                        this.Enabled = true;
                    }

                    if (MotorLimit != regVal)
                    {
                        MotorLimit = regVal;
                        this.textBoxLimit.Text = MotorLimit.ToString();

                        this.numericUpDownStepMin.Minimum = 1;
                        this.numericUpDownStepMin.Maximum = MotorLimit / 10;
                        this.numericUpDownStepMin.Value = MotorLimit / 100;

                        this.numericUpDownStepMax.Minimum = 1;
                        this.numericUpDownStepMax.Maximum = MotorLimit / 4;
                        this.numericUpDownStepMax.Value = MotorLimit / 10;

                        this.numericUpDownTarget1.Minimum = 0;
                        this.numericUpDownTarget1.Maximum = MotorLimit;
                        this.numericUpDownTarget2.Minimum = 0;
                        this.numericUpDownTarget2.Maximum = MotorLimit;
                        this.numericUpDownTarget3.Minimum = 0;
                        this.numericUpDownTarget3.Maximum = MotorLimit;
                        this.numericUpDownTarget4.Minimum = 0;
                        this.numericUpDownTarget4.Maximum = MotorLimit;

                        this.vProgressPosition.Maximum = MotorLimit;
                        this.vProgressPosition.Minimum = 0;

                        //regVal = MyController.Read(Controller.regTarget_1 + RegOffset);
                        //SetTargetPostion(regVal);
                    }

                    MotorPosition = MyController.Read(Controller.regCurrent_1 + RegOffset);
                    vProgressPosition.Value = Math.Min(Math.Max(0, MotorPosition), vProgressPosition.Maximum);
                    textBoxPosition.Text = MotorPosition.ToString();

                    if (AutoStepping)
                    {
                        if (MotorTarget == MotorPosition || Idle)
                        {
                            if (numericUpDownDwellTime.Value == 0)
                            {
                                AutoStep();
                            }
                            else if (!timerDwell.Enabled)
                            {
                                timerDwell.Interval = (int)numericUpDownDwellTime.Value * 1000;
                                timerDwell.Start();
                            }
                        }
                    }

                    if (Idle)
                    {
                        if (HomeRequested)
                        {
                            HomeRequested = false;
                            MyController.Write(Controller.regLimit_1 + RegOffset, 0);
                        }
                        else if (LimitRequested)
                        {
                            LimitRequested = false;
                            MyController.Write(Controller.regLimit_1 + RegOffset, 1);
                        }
                        else if (MoveRequested)
                        {
                            MoveRequested = false;
                            MyController.Write(Controller.regTarget_1 + RegOffset, MotorTarget);
                        }
                        else if (!AutoStepping)
                        {
                            MotorTarget = MotorPosition;
                        }
                    }
                }
                catch (Exception)
                {
                }
            }
            else
            {
                Stop();
                this.Enabled = false;
            }
        }

        public void Stop()
        {
            checkBoxAuto1.Checked = false;
            checkBoxAuto2.Checked = false;
            checkBoxAuto3.Checked = false;
            checkBoxAuto4.Checked = false;
        }

        public bool Moving
        {
            get
            {
                return AutoStepping || !Idle;
            }
        }

        private void AutoStep()
        {
            if (NextStep == checkBoxAuto1)
            {
                if (checkBoxAuto2.Checked) { NextStep = checkBoxAuto2; }
                else if (checkBoxAuto3.Checked) { NextStep = checkBoxAuto3; }
                else if (checkBoxAuto4.Checked) { NextStep = checkBoxAuto4; }
            }
            else if (NextStep == checkBoxAuto2)
            {
                if (checkBoxAuto3.Checked) { NextStep = checkBoxAuto3; }
                else if (checkBoxAuto4.Checked) { NextStep = checkBoxAuto4; }
                else if (checkBoxAuto1.Checked) { NextStep = checkBoxAuto1; }
            }
            else if (NextStep == checkBoxAuto3)
            {
                if (checkBoxAuto4.Checked) { NextStep = checkBoxAuto4; }
                else if (checkBoxAuto1.Checked) { NextStep = checkBoxAuto1; }
                else if (checkBoxAuto2.Checked) { NextStep = checkBoxAuto2; }
            }
            else if (NextStep == checkBoxAuto4)
            {
                if (checkBoxAuto1.Checked) { NextStep = checkBoxAuto1; }
                else if (checkBoxAuto2.Checked) { NextStep = checkBoxAuto2; }
                else if (checkBoxAuto3.Checked) { NextStep = checkBoxAuto3; }
            }

            int nextPosition = -1;
            if (NextStep == checkBoxAuto1) { nextPosition = (int)numericUpDownTarget1.Value; }
            else if (NextStep == checkBoxAuto2) { nextPosition = (int)numericUpDownTarget2.Value; }
            else if (NextStep == checkBoxAuto3) { nextPosition = (int)numericUpDownTarget3.Value; }
            else if (NextStep == checkBoxAuto4) { nextPosition = (int)numericUpDownTarget4.Value; }

            if (nextPosition >= 0)
            {
                SetTargetPostion(nextPosition);
            }
        }

        // TODO:
        // Implement state machine:
        // 1) Auto - only 4 target numerics are active
        // 2) Manual - everything enabled, target changes are sent to controller immediately.
        // 3) SeekingHome - eveything disabled (accpet stop) until home reached, then target set to 0.
        // 4) SeekingLimit - everything disabled (accept stop) until limit reached, then target set to limit.

        private Controller MyController { get; set; }
        private int Axis { get; set; }
        private uint RegOffset { get; set; }
        private int MotorLimit { get; set; }
        private int MotorTarget { get; set; }
        private bool MoveRequested { get; set; }
        private bool HomeRequested { get; set; }
        private bool LimitRequested { get; set; }
        private int MotorPosition { get; set; }
        private bool AutoStepping { get; set; }
        private bool Idle { get; set; }
        private CheckBox NextStep { get; set; }

        private void SetTargetPostion(int target)
        {
            //if (target != MotorTarget)
            if (target != MotorPosition ||
                (AutoStepping && (target != MotorTarget)))
            {
                // clip to endpoints if necessary
                target = Math.Min(Math.Max(0, target), MotorLimit);
                MotorTarget = target;
                MoveRequested = true;
            }
        }

        private void buttonGoTarget1_Click(object sender, EventArgs e)
        {
            SetTargetPostion((int)this.numericUpDownTarget1.Value);
        }

        private void buttonGoToTarget2_Click(object sender, EventArgs e)
        {
            SetTargetPostion((int)this.numericUpDownTarget2.Value);
        }

        private void buttonGoToTarget3_Click(object sender, EventArgs e)
        {
            SetTargetPostion((int)this.numericUpDownTarget3.Value);
        }

        private void buttonGoToTarget4_Click(object sender, EventArgs e)
        {
            SetTargetPostion((int)this.numericUpDownTarget4.Value);
        }

        private void buttonToLimit_Click(object sender, EventArgs e)
        {
            LimitRequested = true;
//            SetTargetPostion(MotorLimit);
        }

        private void buttonToHome_Click(object sender, EventArgs e)
        {
            HomeRequested = true;
//            SetTargetPostion(0);
        }

        private void checkBoxAuto_CheckedChanged(object sender, EventArgs e)
        {
            bool alreadyStepping = AutoStepping;

            AutoStepping =
                checkBoxAuto1.Checked ||
                checkBoxAuto2.Checked ||
                checkBoxAuto3.Checked ||
                checkBoxAuto4.Checked;

            if (!AutoStepping)
            {
                timerDwell.Stop();
            }
            else if (!alreadyStepping)
            {
                AutoStep();
            }
        }

        private void numericUpDownDwellTime_ValueChanged(object sender, EventArgs e)
        {
            if (AutoStepping)
            {
                if (numericUpDownDwellTime.Value > 0)
                {
                    timerDwell.Interval = (int)numericUpDownDwellTime.Value * 1000;
                }
                else
                {
                    timerDwell.Stop();
                    AutoStep();
                }
            }
        }

        private void timerDwell_Tick(object sender, EventArgs e)
        {
            timerDwell.Stop();
            if (AutoStepping)
            {
                AutoStep();
            }
        }

        private void buttonUpFast_Click(object sender, EventArgs e)
        {
            int newTarget = MotorTarget + (int)numericUpDownStepMax.Value;
            SetTargetPostion(newTarget);
        }

        private void buttonUpSlow_Click(object sender, EventArgs e)
        {
            int newTarget = MotorTarget + (int)numericUpDownStepMin.Value;
            SetTargetPostion(newTarget);
        }

        private void buttonDownSlow_Click(object sender, EventArgs e)
        {
            int newTarget = MotorTarget - (int)numericUpDownStepMin.Value;
            SetTargetPostion(newTarget);
        }

        private void buttonDownFast_Click(object sender, EventArgs e)
        {
            int newTarget = MotorTarget - (int)numericUpDownStepMax.Value;
            SetTargetPostion(newTarget);
        }

    }
}
