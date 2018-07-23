using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Navitar.Demos
{
    public partial class SetupDialog : Form
    {
        public SetupDialog()
            : this(null)
        {
        }

        private void InitializeControls()
        {
            int row = 0;
            int col = 1;
            tableLayoutPanel1.Controls.Add(MakeLabel("Zoom"), col++, row);
            tableLayoutPanel1.Controls.Add(MakeLabel("Focus"), col++, row);

            row++;
            col = 0;
            if ((MyController.ProductID == 0x4001) && (MyController.ProductSubclass == 3))
            {
                tableLayoutPanel1.Controls.Add(MakeLabel("Deceleration"), col++, row);
            }
            else
            {
                tableLayoutPanel1.Controls.Add(MakeLabel("Acceleration"), col++, row);
            }
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupAcceleration_1), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupAcceleration_2), col++, row);

            row++;
            col = 0;
            if ((MyController.ProductID == 0x4001) && (MyController.ProductSubclass == 3))
            {
                tableLayoutPanel1.Controls.Add(MakeLabel("Gain"), col++, row);
            }
            else
            {
                tableLayoutPanel1.Controls.Add(MakeLabel("Initial Velocity"), col++, row);
            }
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupInitialVelocity_1), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupInitialVelocity_2), col++, row);

            row++;
            col = 0;
            if ((MyController.ProductID == 0x4001) && (MyController.ProductSubclass == 3))
            {
                tableLayoutPanel1.Controls.Add(MakeLabel("Max Torque %"), col++, row);
            }
            else
            {
                tableLayoutPanel1.Controls.Add(MakeLabel("Maximum Velocity"), col++, row);
            }
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupMaxVelocity_1), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupMaxVelocity_2), col++, row);

            row++;
            col = 0;
            tableLayoutPanel1.Controls.Add(MakeLabel("Reverse Backlash"), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupReverseBacklash_1), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupReverseBacklash_2), col++, row);

            row++;
            col = 0;
            tableLayoutPanel1.Controls.Add(MakeLabel("Forward Backlash"), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupForwardBacklash_1), col++, row);
            tableLayoutPanel1.Controls.Add(MakeNumeric(Controller.regSetupForwardBacklash_2), col++, row);

            row++;
            col = 0;
            tableLayoutPanel1.Controls.Add(MakeLabel("Down Through Home"), col++, row);
            checkBoxThruHome1 = new CheckBox();
            int config1 = MyController.Read(Controller.regSetupConfig_1);
            checkBoxThruHome1.Checked = ((config1 & 0x02) != 0);
            checkBoxThruHome1.CheckedChanged += new EventHandler(this.setting_Changed);
            checkBoxThruHome1.Anchor = AnchorStyles.Left | AnchorStyles.Bottom;
            tableLayoutPanel1.Controls.Add(checkBoxThruHome1, col++, row);
            checkBoxThruHome2 = new CheckBox();
            int config2 = MyController.Read(Controller.regSetupConfig_2);
            checkBoxThruHome2.Checked = ((config2 & 0x02) != 0);
            checkBoxThruHome2.CheckedChanged += new EventHandler(this.setting_Changed);
            checkBoxThruHome2.Anchor = AnchorStyles.Left | AnchorStyles.Bottom;
            tableLayoutPanel1.Controls.Add(checkBoxThruHome2, col++, row);

            row++;
            col = 0;
            tableLayoutPanel1.Controls.Add(MakeLabel("Zero Position is"), col++, row);
            comboBoxZeroPosition1 = new ComboBox();
            comboBoxZeroPosition1.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxZeroPosition1.Items.Add("Near");
            comboBoxZeroPosition1.Items.Add("Far");
            comboBoxZeroPosition1.SelectedIndex = (config1 & 0x01) == 0 ? 0 : 1;
            comboBoxZeroPosition1.SelectedIndexChanged += new EventHandler(this.setting_Changed);
            tableLayoutPanel1.Controls.Add(comboBoxZeroPosition1, col++, row);
            comboBoxZeroPosition2 = new ComboBox();
            comboBoxZeroPosition2.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxZeroPosition2.Items.Add("Near");
            comboBoxZeroPosition2.Items.Add("Far");
            comboBoxZeroPosition2.SelectedIndex = (config2 & 0x01) == 0 ? 0 : 1;
            comboBoxZeroPosition2.SelectedIndexChanged += new EventHandler(this.setting_Changed);
            tableLayoutPanel1.Controls.Add(comboBoxZeroPosition2, col++, row);

            row++;
            col = 0;
            tableLayoutPanel1.Controls.Add(MakeLabel("Disable Axis"), col++, row);
            if (MyController.Generation == 2)
            {
                checkBoxDisableAxis1 = new CheckBox();
                checkBoxDisableAxis1.Checked = ((config1 & 0x04) != 0);
                checkBoxDisableAxis1.CheckedChanged += new EventHandler(this.setting_Changed);
                checkBoxDisableAxis1.Anchor = AnchorStyles.Left | AnchorStyles.Bottom;
                tableLayoutPanel1.Controls.Add(checkBoxDisableAxis1, col++, row);
            }
            else
            {
                col++;
            }
            checkBoxDisableAxis2 = new CheckBox();
            checkBoxDisableAxis2.Checked = ((config2 & 0x04) != 0);
            checkBoxDisableAxis2.CheckedChanged += new EventHandler(this.setting_Changed);
            checkBoxDisableAxis2.Anchor = AnchorStyles.Left | AnchorStyles.Bottom;
            tableLayoutPanel1.Controls.Add(checkBoxDisableAxis2, col++, row);
        }

        public SetupDialog(Controller controller)
        {
            MyController = controller;
            MapRegToNumeric = new Dictionary<uint, NumericUpDown>();
            MapNumericToReg = new Dictionary<NumericUpDown, uint>();
            InitializeComponent();

            InitializeControls();
        }

        private Label MakeLabel(string lableString)
        {
            Label label = new Label();
            label.Text = lableString;
            label.TextAlign = ContentAlignment.MiddleRight;
            label.Anchor = AnchorStyles.Right;
            label.AutoSize = true;
            return label;
        }

        private NumericUpDown MakeNumeric(uint register)
        {
            NumericUpDown upDown = new NumericUpDown();
            upDown.Maximum = 100000;
            upDown.Minimum = 0;
            upDown.Value = MyController.Read(register);
            upDown.Validating += new CancelEventHandler(this.upDown_Validating);
            upDown.Anchor = AnchorStyles.Left | AnchorStyles.Bottom;
            MapRegToNumeric.Add(register, upDown);
            MapNumericToReg.Add(upDown, register);
            return upDown;
        }

        private Controller MyController { get; set; }
        private Dictionary<uint, NumericUpDown> MapRegToNumeric { get; set; }
        private Dictionary<NumericUpDown, uint> MapNumericToReg { get; set; }

        private CheckBox checkBoxThruHome1;
        private ComboBox comboBoxZeroPosition1;
        private CheckBox checkBoxDisableAxis1;
        private CheckBox checkBoxThruHome2;
        private ComboBox comboBoxZeroPosition2;
        private CheckBox checkBoxDisableAxis2;

        private void buttonSave_Click(object sender, EventArgs e)
        {
            try
            {
                // Set wait cursor since save to flash takes a few seconds.
                Cursor.Current = Cursors.WaitCursor;

                // Save to flash
                MyController.SaveSetup();

                // Clear the wait cursor.
                Cursor.Current = Cursors.Default;
            }
            catch (Exception)
            {
                // Problem saving new parameter values, display generic error.
                MessageBox.Show("An error occurred attempting to save the settings.  Ensure motion is stopped before saving.");
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonDefault_Click(object sender, EventArgs e)
        {
            try
            {
                MyController.LoadDefaultSetup();

                MapRegToNumeric.Clear();
                MapNumericToReg.Clear();
                tableLayoutPanel1.Controls.Clear();
                InitializeControls();
            }
            catch (Exception)
            {
                MessageBox.Show("An error occurred attempting to restore default settings.");
            }
        }

        private void upDown_Validating(object sender, CancelEventArgs e)
        {
            if (MyController.Generation == 1)
            {
                int status1 = MyController.Read(Controller.regStatus_1);
                int status2 = MyController.Read(Controller.regStatus_2);
                if (((status1 | status2) & 0x0ff) != 0)
                {
                    MessageBox.Show("Motion must be stopped before setup parameters may be modified.");
                    Close();
                    e.Cancel = true;
                    return;
                }
            }

            NumericUpDown upDown = (NumericUpDown)sender;
            uint register = MapNumericToReg[upDown];
            try
            {
                MyController.Write(register, (int)upDown.Value);
            }
            catch (Exception)
            {
                MessageBox.Show("Setting is out of range.");
                e.Cancel = true;
                return;
            }
        }

        private void setting_Changed(object sender, EventArgs e)
        {
            try
            {
                if (MyController.Generation == 1)
                {
                    int status1 = MyController.Read(Controller.regStatus_1);
                    int status2 = MyController.Read(Controller.regStatus_2);
                    if (((status1 | status2) & 0x0ff) != 0)
                    {
                        MessageBox.Show("Motion must be stopped before setup parameters may be modified.");
                        Close();
                        return;
                    }
                }

                int regVal = MyController.Read(Controller.regSetupConfig_1);
                if (comboBoxZeroPosition1.SelectedIndex == 1)
                {
                    regVal |= 0x01;
                }
                else
                {
                    regVal &= ~((int)0x01);
                }
                if (checkBoxThruHome1.Checked)
                {
                    regVal |= 0x02;
                }
                else
                {
                    regVal &= ~((int)0x02);
                }
                if (MyController.Generation == 2 && checkBoxDisableAxis1.Checked)
                {
                    regVal |= 0x04;
                }
                else
                {
                    regVal &= ~((int)0x04);
                }
                MyController.Write(Controller.regSetupConfig_1, regVal);

                regVal = MyController.Read(Controller.regSetupConfig_2); ;
                if (comboBoxZeroPosition2.SelectedIndex == 1)
                {
                    regVal |= 0x01;
                }
                else
                {
                    regVal &= ~((int)0x01);
                }
                if (checkBoxThruHome2.Checked)
                {
                    regVal |= 0x02;
                }
                else
                {
                    regVal &= ~((int)0x02);
                }
                if (checkBoxDisableAxis2.Checked)
                {
                    regVal |= 0x04;
                }
                else
                {
                    regVal &= ~((int)0x04);
                }
                MyController.Write(Controller.regSetupConfig_2, regVal);
            }
            catch (Exception)
            {
                // Problem writing new parameter values, probably a limit check, display generic error.
                MessageBox.Show("Error writing register.");
                return;
            }
        }
    }
}
