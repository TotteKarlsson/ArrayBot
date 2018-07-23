namespace Navitar.Demos
{
    partial class MotionAxis
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MotionAxis));
            this.buttonAtLimit = new System.Windows.Forms.Button();
            this.buttonAtHome = new System.Windows.Forms.Button();
            this.buttonToLimit = new System.Windows.Forms.Button();
            this.buttonToHome = new System.Windows.Forms.Button();
            this.textBoxLimit = new System.Windows.Forms.TextBox();
            this.textBoxPosition = new System.Windows.Forms.TextBox();
            this.numericUpDownTarget1 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTarget2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTarget3 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTarget4 = new System.Windows.Forms.NumericUpDown();
            this.buttonGoToTarget1 = new System.Windows.Forms.Button();
            this.buttonGoToTarget2 = new System.Windows.Forms.Button();
            this.buttonGoToTarget4 = new System.Windows.Forms.Button();
            this.buttonGoToTarget3 = new System.Windows.Forms.Button();
            this.checkBoxAuto1 = new System.Windows.Forms.CheckBox();
            this.checkBoxAuto2 = new System.Windows.Forms.CheckBox();
            this.checkBoxAuto3 = new System.Windows.Forms.CheckBox();
            this.checkBoxAuto4 = new System.Windows.Forms.CheckBox();
            this.labelLimitPos = new System.Windows.Forms.Label();
            this.labelPosition = new System.Windows.Forms.Label();
            this.numericUpDownDwellTime = new System.Windows.Forms.NumericUpDown();
            this.labelDwellTime = new System.Windows.Forms.Label();
            this.groupBoxAxis = new System.Windows.Forms.GroupBox();
            this.buttonDownFast = new System.Windows.Forms.Button();
            this.buttonDownSlow = new System.Windows.Forms.Button();
            this.buttonUpSlow = new System.Windows.Forms.Button();
            this.buttonUpFast = new System.Windows.Forms.Button();
            this.labelStepMax = new System.Windows.Forms.Label();
            this.labelStepMin = new System.Windows.Forms.Label();
            this.numericUpDownStepMax = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownStepMin = new System.Windows.Forms.NumericUpDown();
            this.labelHome = new System.Windows.Forms.Label();
            this.labelLimit = new System.Windows.Forms.Label();
            this.timerDwell = new System.Windows.Forms.Timer(this.components);
            this.vProgressPosition = new Navitar.Demos.VProgress();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDwellTime)).BeginInit();
            this.groupBoxAxis.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStepMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStepMin)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonAtLimit
            // 
            this.buttonAtLimit.Enabled = false;
            this.buttonAtLimit.Location = new System.Drawing.Point(6, 19);
            this.buttonAtLimit.Name = "buttonAtLimit";
            this.buttonAtLimit.Size = new System.Drawing.Size(23, 23);
            this.buttonAtLimit.TabIndex = 4;
            this.buttonAtLimit.UseVisualStyleBackColor = true;
            // 
            // buttonAtHome
            // 
            this.buttonAtHome.Enabled = false;
            this.buttonAtHome.Location = new System.Drawing.Point(6, 294);
            this.buttonAtHome.Name = "buttonAtHome";
            this.buttonAtHome.Size = new System.Drawing.Size(23, 23);
            this.buttonAtHome.TabIndex = 5;
            this.buttonAtHome.UseVisualStyleBackColor = true;
            // 
            // buttonToLimit
            // 
            this.buttonToLimit.Location = new System.Drawing.Point(35, 19);
            this.buttonToLimit.Name = "buttonToLimit";
            this.buttonToLimit.Size = new System.Drawing.Size(30, 23);
            this.buttonToLimit.TabIndex = 6;
            this.buttonToLimit.Text = "To";
            this.buttonToLimit.UseVisualStyleBackColor = true;
            this.buttonToLimit.Click += new System.EventHandler(this.buttonToLimit_Click);
            // 
            // buttonToHome
            // 
            this.buttonToHome.Location = new System.Drawing.Point(35, 294);
            this.buttonToHome.Name = "buttonToHome";
            this.buttonToHome.Size = new System.Drawing.Size(30, 23);
            this.buttonToHome.TabIndex = 7;
            this.buttonToHome.Text = "To";
            this.buttonToHome.UseVisualStyleBackColor = true;
            this.buttonToHome.Click += new System.EventHandler(this.buttonToHome_Click);
            // 
            // textBoxLimit
            // 
            this.textBoxLimit.Location = new System.Drawing.Point(97, 21);
            this.textBoxLimit.Name = "textBoxLimit";
            this.textBoxLimit.ReadOnly = true;
            this.textBoxLimit.Size = new System.Drawing.Size(80, 20);
            this.textBoxLimit.TabIndex = 8;
            // 
            // textBoxPosition
            // 
            this.textBoxPosition.Location = new System.Drawing.Point(95, 61);
            this.textBoxPosition.Name = "textBoxPosition";
            this.textBoxPosition.ReadOnly = true;
            this.textBoxPosition.Size = new System.Drawing.Size(82, 20);
            this.textBoxPosition.TabIndex = 9;
            // 
            // numericUpDownTarget1
            // 
            this.numericUpDownTarget1.Location = new System.Drawing.Point(95, 87);
            this.numericUpDownTarget1.Name = "numericUpDownTarget1";
            this.numericUpDownTarget1.Size = new System.Drawing.Size(100, 20);
            this.numericUpDownTarget1.TabIndex = 10;
            // 
            // numericUpDownTarget2
            // 
            this.numericUpDownTarget2.Location = new System.Drawing.Point(95, 114);
            this.numericUpDownTarget2.Name = "numericUpDownTarget2";
            this.numericUpDownTarget2.Size = new System.Drawing.Size(100, 20);
            this.numericUpDownTarget2.TabIndex = 11;
            // 
            // numericUpDownTarget3
            // 
            this.numericUpDownTarget3.Location = new System.Drawing.Point(95, 141);
            this.numericUpDownTarget3.Name = "numericUpDownTarget3";
            this.numericUpDownTarget3.Size = new System.Drawing.Size(100, 20);
            this.numericUpDownTarget3.TabIndex = 12;
            // 
            // numericUpDownTarget4
            // 
            this.numericUpDownTarget4.Location = new System.Drawing.Point(95, 168);
            this.numericUpDownTarget4.Name = "numericUpDownTarget4";
            this.numericUpDownTarget4.Size = new System.Drawing.Size(100, 20);
            this.numericUpDownTarget4.TabIndex = 13;
            // 
            // buttonGoToTarget1
            // 
            this.buttonGoToTarget1.Location = new System.Drawing.Point(201, 84);
            this.buttonGoToTarget1.Name = "buttonGoToTarget1";
            this.buttonGoToTarget1.Size = new System.Drawing.Size(33, 23);
            this.buttonGoToTarget1.TabIndex = 14;
            this.buttonGoToTarget1.Text = "Go";
            this.buttonGoToTarget1.UseVisualStyleBackColor = true;
            this.buttonGoToTarget1.Click += new System.EventHandler(this.buttonGoTarget1_Click);
            // 
            // buttonGoToTarget2
            // 
            this.buttonGoToTarget2.Location = new System.Drawing.Point(201, 111);
            this.buttonGoToTarget2.Name = "buttonGoToTarget2";
            this.buttonGoToTarget2.Size = new System.Drawing.Size(33, 23);
            this.buttonGoToTarget2.TabIndex = 15;
            this.buttonGoToTarget2.Text = "Go";
            this.buttonGoToTarget2.UseVisualStyleBackColor = true;
            this.buttonGoToTarget2.Click += new System.EventHandler(this.buttonGoToTarget2_Click);
            // 
            // buttonGoToTarget4
            // 
            this.buttonGoToTarget4.Location = new System.Drawing.Point(201, 165);
            this.buttonGoToTarget4.Name = "buttonGoToTarget4";
            this.buttonGoToTarget4.Size = new System.Drawing.Size(33, 23);
            this.buttonGoToTarget4.TabIndex = 16;
            this.buttonGoToTarget4.Text = "Go";
            this.buttonGoToTarget4.UseVisualStyleBackColor = true;
            this.buttonGoToTarget4.Click += new System.EventHandler(this.buttonGoToTarget4_Click);
            // 
            // buttonGoToTarget3
            // 
            this.buttonGoToTarget3.Location = new System.Drawing.Point(201, 138);
            this.buttonGoToTarget3.Name = "buttonGoToTarget3";
            this.buttonGoToTarget3.Size = new System.Drawing.Size(33, 23);
            this.buttonGoToTarget3.TabIndex = 17;
            this.buttonGoToTarget3.Text = "Go";
            this.buttonGoToTarget3.UseVisualStyleBackColor = true;
            this.buttonGoToTarget3.Click += new System.EventHandler(this.buttonGoToTarget3_Click);
            // 
            // checkBoxAuto1
            // 
            this.checkBoxAuto1.AutoSize = true;
            this.checkBoxAuto1.Location = new System.Drawing.Point(241, 89);
            this.checkBoxAuto1.Name = "checkBoxAuto1";
            this.checkBoxAuto1.Size = new System.Drawing.Size(48, 17);
            this.checkBoxAuto1.TabIndex = 18;
            this.checkBoxAuto1.Text = "Auto";
            this.checkBoxAuto1.UseVisualStyleBackColor = true;
            this.checkBoxAuto1.CheckedChanged += new System.EventHandler(this.checkBoxAuto_CheckedChanged);
            // 
            // checkBoxAuto2
            // 
            this.checkBoxAuto2.AutoSize = true;
            this.checkBoxAuto2.Location = new System.Drawing.Point(241, 115);
            this.checkBoxAuto2.Name = "checkBoxAuto2";
            this.checkBoxAuto2.Size = new System.Drawing.Size(48, 17);
            this.checkBoxAuto2.TabIndex = 19;
            this.checkBoxAuto2.Text = "Auto";
            this.checkBoxAuto2.UseVisualStyleBackColor = true;
            this.checkBoxAuto2.CheckedChanged += new System.EventHandler(this.checkBoxAuto_CheckedChanged);
            // 
            // checkBoxAuto3
            // 
            this.checkBoxAuto3.AutoSize = true;
            this.checkBoxAuto3.Location = new System.Drawing.Point(241, 142);
            this.checkBoxAuto3.Name = "checkBoxAuto3";
            this.checkBoxAuto3.Size = new System.Drawing.Size(48, 17);
            this.checkBoxAuto3.TabIndex = 20;
            this.checkBoxAuto3.Text = "Auto";
            this.checkBoxAuto3.UseVisualStyleBackColor = true;
            this.checkBoxAuto3.CheckedChanged += new System.EventHandler(this.checkBoxAuto_CheckedChanged);
            // 
            // checkBoxAuto4
            // 
            this.checkBoxAuto4.AutoSize = true;
            this.checkBoxAuto4.Location = new System.Drawing.Point(241, 169);
            this.checkBoxAuto4.Name = "checkBoxAuto4";
            this.checkBoxAuto4.Size = new System.Drawing.Size(48, 17);
            this.checkBoxAuto4.TabIndex = 21;
            this.checkBoxAuto4.Text = "Auto";
            this.checkBoxAuto4.UseVisualStyleBackColor = true;
            this.checkBoxAuto4.CheckedChanged += new System.EventHandler(this.checkBoxAuto_CheckedChanged);
            // 
            // labelLimitPos
            // 
            this.labelLimitPos.AutoSize = true;
            this.labelLimitPos.Location = new System.Drawing.Point(179, 24);
            this.labelLimitPos.Name = "labelLimitPos";
            this.labelLimitPos.Size = new System.Drawing.Size(44, 13);
            this.labelLimitPos.TabIndex = 22;
            this.labelLimitPos.Text = "Position";
            // 
            // labelPosition
            // 
            this.labelPosition.AutoSize = true;
            this.labelPosition.Location = new System.Drawing.Point(179, 64);
            this.labelPosition.Name = "labelPosition";
            this.labelPosition.Size = new System.Drawing.Size(81, 13);
            this.labelPosition.TabIndex = 23;
            this.labelPosition.Text = "Current Position";
            // 
            // numericUpDownDwellTime
            // 
            this.numericUpDownDwellTime.Location = new System.Drawing.Point(109, 194);
            this.numericUpDownDwellTime.Name = "numericUpDownDwellTime";
            this.numericUpDownDwellTime.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownDwellTime.TabIndex = 24;
            this.numericUpDownDwellTime.ValueChanged += new System.EventHandler(this.numericUpDownDwellTime_ValueChanged);
            // 
            // labelDwellTime
            // 
            this.labelDwellTime.AutoSize = true;
            this.labelDwellTime.Location = new System.Drawing.Point(197, 197);
            this.labelDwellTime.Name = "labelDwellTime";
            this.labelDwellTime.Size = new System.Drawing.Size(59, 13);
            this.labelDwellTime.TabIndex = 25;
            this.labelDwellTime.Text = "Dwell Time";
            // 
            // groupBoxAxis
            // 
            this.groupBoxAxis.Controls.Add(this.buttonDownFast);
            this.groupBoxAxis.Controls.Add(this.buttonDownSlow);
            this.groupBoxAxis.Controls.Add(this.buttonUpSlow);
            this.groupBoxAxis.Controls.Add(this.buttonUpFast);
            this.groupBoxAxis.Controls.Add(this.labelStepMax);
            this.groupBoxAxis.Controls.Add(this.labelStepMin);
            this.groupBoxAxis.Controls.Add(this.numericUpDownStepMax);
            this.groupBoxAxis.Controls.Add(this.numericUpDownStepMin);
            this.groupBoxAxis.Controls.Add(this.labelHome);
            this.groupBoxAxis.Controls.Add(this.labelLimit);
            this.groupBoxAxis.Controls.Add(this.buttonToLimit);
            this.groupBoxAxis.Controls.Add(this.buttonToHome);
            this.groupBoxAxis.Controls.Add(this.buttonGoToTarget1);
            this.groupBoxAxis.Controls.Add(this.labelDwellTime);
            this.groupBoxAxis.Controls.Add(this.numericUpDownDwellTime);
            this.groupBoxAxis.Controls.Add(this.vProgressPosition);
            this.groupBoxAxis.Controls.Add(this.labelPosition);
            this.groupBoxAxis.Controls.Add(this.buttonAtLimit);
            this.groupBoxAxis.Controls.Add(this.labelLimitPos);
            this.groupBoxAxis.Controls.Add(this.buttonAtHome);
            this.groupBoxAxis.Controls.Add(this.checkBoxAuto4);
            this.groupBoxAxis.Controls.Add(this.checkBoxAuto3);
            this.groupBoxAxis.Controls.Add(this.checkBoxAuto2);
            this.groupBoxAxis.Controls.Add(this.textBoxLimit);
            this.groupBoxAxis.Controls.Add(this.checkBoxAuto1);
            this.groupBoxAxis.Controls.Add(this.textBoxPosition);
            this.groupBoxAxis.Controls.Add(this.buttonGoToTarget3);
            this.groupBoxAxis.Controls.Add(this.numericUpDownTarget1);
            this.groupBoxAxis.Controls.Add(this.buttonGoToTarget4);
            this.groupBoxAxis.Controls.Add(this.numericUpDownTarget2);
            this.groupBoxAxis.Controls.Add(this.buttonGoToTarget2);
            this.groupBoxAxis.Controls.Add(this.numericUpDownTarget3);
            this.groupBoxAxis.Controls.Add(this.numericUpDownTarget4);
            this.groupBoxAxis.Location = new System.Drawing.Point(3, 3);
            this.groupBoxAxis.Name = "groupBoxAxis";
            this.groupBoxAxis.Size = new System.Drawing.Size(311, 327);
            this.groupBoxAxis.TabIndex = 26;
            this.groupBoxAxis.TabStop = false;
            this.groupBoxAxis.Text = "Axis N";
            // 
            // buttonDownFast
            // 
            this.buttonDownFast.Image = ((System.Drawing.Image)(resources.GetObject("buttonDownFast.Image")));
            this.buttonDownFast.Location = new System.Drawing.Point(35, 228);
            this.buttonDownFast.Name = "buttonDownFast";
            this.buttonDownFast.Size = new System.Drawing.Size(30, 45);
            this.buttonDownFast.TabIndex = 36;
            this.buttonDownFast.UseVisualStyleBackColor = true;
            this.buttonDownFast.Click += new System.EventHandler(this.buttonDownFast_Click);
            // 
            // buttonDownSlow
            // 
            this.buttonDownSlow.Image = ((System.Drawing.Image)(resources.GetObject("buttonDownSlow.Image")));
            this.buttonDownSlow.Location = new System.Drawing.Point(35, 173);
            this.buttonDownSlow.Name = "buttonDownSlow";
            this.buttonDownSlow.Size = new System.Drawing.Size(30, 45);
            this.buttonDownSlow.TabIndex = 35;
            this.buttonDownSlow.UseVisualStyleBackColor = true;
            this.buttonDownSlow.Click += new System.EventHandler(this.buttonDownSlow_Click);
            // 
            // buttonUpSlow
            // 
            this.buttonUpSlow.Image = ((System.Drawing.Image)(resources.GetObject("buttonUpSlow.Image")));
            this.buttonUpSlow.Location = new System.Drawing.Point(35, 118);
            this.buttonUpSlow.Name = "buttonUpSlow";
            this.buttonUpSlow.Size = new System.Drawing.Size(30, 45);
            this.buttonUpSlow.TabIndex = 34;
            this.buttonUpSlow.UseVisualStyleBackColor = true;
            this.buttonUpSlow.Click += new System.EventHandler(this.buttonUpSlow_Click);
            // 
            // buttonUpFast
            // 
            this.buttonUpFast.Image = ((System.Drawing.Image)(resources.GetObject("buttonUpFast.Image")));
            this.buttonUpFast.Location = new System.Drawing.Point(35, 63);
            this.buttonUpFast.Name = "buttonUpFast";
            this.buttonUpFast.Size = new System.Drawing.Size(30, 45);
            this.buttonUpFast.TabIndex = 33;
            this.buttonUpFast.UseVisualStyleBackColor = true;
            this.buttonUpFast.Click += new System.EventHandler(this.buttonUpFast_Click);
            // 
            // labelStepMax
            // 
            this.labelStepMax.AutoSize = true;
            this.labelStepMax.Location = new System.Drawing.Point(197, 270);
            this.labelStepMax.Name = "labelStepMax";
            this.labelStepMax.Size = new System.Drawing.Size(71, 13);
            this.labelStepMax.TabIndex = 32;
            this.labelStepMax.Text = "Jog Maximum";
            // 
            // labelStepMin
            // 
            this.labelStepMin.AutoSize = true;
            this.labelStepMin.Location = new System.Drawing.Point(197, 244);
            this.labelStepMin.Name = "labelStepMin";
            this.labelStepMin.Size = new System.Drawing.Size(68, 13);
            this.labelStepMin.TabIndex = 31;
            this.labelStepMin.Text = "Jog Minimum";
            // 
            // numericUpDownStepMax
            // 
            this.numericUpDownStepMax.Location = new System.Drawing.Point(109, 268);
            this.numericUpDownStepMax.Name = "numericUpDownStepMax";
            this.numericUpDownStepMax.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownStepMax.TabIndex = 30;
            // 
            // numericUpDownStepMin
            // 
            this.numericUpDownStepMin.Location = new System.Drawing.Point(109, 242);
            this.numericUpDownStepMin.Name = "numericUpDownStepMin";
            this.numericUpDownStepMin.Size = new System.Drawing.Size(86, 20);
            this.numericUpDownStepMin.TabIndex = 29;
            // 
            // labelHome
            // 
            this.labelHome.AutoSize = true;
            this.labelHome.Location = new System.Drawing.Point(66, 300);
            this.labelHome.Name = "labelHome";
            this.labelHome.Size = new System.Drawing.Size(35, 13);
            this.labelHome.TabIndex = 28;
            this.labelHome.Text = "Home";
            // 
            // labelLimit
            // 
            this.labelLimit.AutoSize = true;
            this.labelLimit.Location = new System.Drawing.Point(66, 24);
            this.labelLimit.Name = "labelLimit";
            this.labelLimit.Size = new System.Drawing.Size(28, 13);
            this.labelLimit.TabIndex = 27;
            this.labelLimit.Text = "Limit";
            // 
            // timerDwell
            // 
            this.timerDwell.Tick += new System.EventHandler(this.timerDwell_Tick);
            // 
            // vProgressPosition
            // 
            this.vProgressPosition.Location = new System.Drawing.Point(6, 63);
            this.vProgressPosition.Name = "vProgressPosition";
            this.vProgressPosition.Size = new System.Drawing.Size(23, 210);
            this.vProgressPosition.TabIndex = 3;
            // 
            // MotionAxis
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxAxis);
            this.Name = "MotionAxis";
            this.Size = new System.Drawing.Size(322, 335);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTarget4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDwellTime)).EndInit();
            this.groupBoxAxis.ResumeLayout(false);
            this.groupBoxAxis.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStepMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStepMin)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private VProgress vProgressPosition;
        private System.Windows.Forms.Button buttonAtLimit;
        private System.Windows.Forms.Button buttonAtHome;
        private System.Windows.Forms.Button buttonToLimit;
        private System.Windows.Forms.Button buttonToHome;
        private System.Windows.Forms.TextBox textBoxLimit;
        private System.Windows.Forms.TextBox textBoxPosition;
        private System.Windows.Forms.NumericUpDown numericUpDownTarget1;
        private System.Windows.Forms.NumericUpDown numericUpDownTarget2;
        private System.Windows.Forms.NumericUpDown numericUpDownTarget3;
        private System.Windows.Forms.NumericUpDown numericUpDownTarget4;
        private System.Windows.Forms.Button buttonGoToTarget1;
        private System.Windows.Forms.Button buttonGoToTarget2;
        private System.Windows.Forms.Button buttonGoToTarget4;
        private System.Windows.Forms.Button buttonGoToTarget3;
        private System.Windows.Forms.CheckBox checkBoxAuto1;
        private System.Windows.Forms.CheckBox checkBoxAuto2;
        private System.Windows.Forms.CheckBox checkBoxAuto3;
        private System.Windows.Forms.CheckBox checkBoxAuto4;
        private System.Windows.Forms.Label labelLimitPos;
        private System.Windows.Forms.Label labelPosition;
        private System.Windows.Forms.NumericUpDown numericUpDownDwellTime;
        private System.Windows.Forms.Label labelDwellTime;
        private System.Windows.Forms.GroupBox groupBoxAxis;
        private System.Windows.Forms.Label labelLimit;
        private System.Windows.Forms.Label labelHome;
        private System.Windows.Forms.Label labelStepMax;
        private System.Windows.Forms.Label labelStepMin;
        private System.Windows.Forms.NumericUpDown numericUpDownStepMax;
        private System.Windows.Forms.NumericUpDown numericUpDownStepMin;
        private System.Windows.Forms.Timer timerDwell;
        private System.Windows.Forms.Button buttonDownFast;
        private System.Windows.Forms.Button buttonDownSlow;
        private System.Windows.Forms.Button buttonUpSlow;
        private System.Windows.Forms.Button buttonUpFast;
    }
}
