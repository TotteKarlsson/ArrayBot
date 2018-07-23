namespace Navitar.Demos
{
    partial class TwoAxisControlPanel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TwoAxisControlPanel));
            this.pictureBoxLogo = new System.Windows.Forms.PictureBox();
            this.buttonStop = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.labelHWVersion = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.labelFWVersion = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.labelDateOfManufacture = new System.Windows.Forms.Label();
            this.buttonSettings = new System.Windows.Forms.Button();
            this.textBoxOnLine = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxLED2 = new System.Windows.Forms.TextBox();
            this.textBoxLED1 = new System.Windows.Forms.TextBox();
            this.timerPolling = new System.Windows.Forms.Timer(this.components);
            this.label4 = new System.Windows.Forms.Label();
            this.labelSerialNumber = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBoxLogo
            // 
            this.pictureBoxLogo.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxLogo.Image")));
            this.pictureBoxLogo.Location = new System.Drawing.Point(380, 349);
            this.pictureBoxLogo.Name = "pictureBoxLogo";
            this.pictureBoxLogo.Size = new System.Drawing.Size(280, 62);
            this.pictureBoxLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxLogo.TabIndex = 3;
            this.pictureBoxLogo.TabStop = false;
            // 
            // buttonStop
            // 
            this.buttonStop.Location = new System.Drawing.Point(274, 349);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(100, 62);
            this.buttonStop.TabIndex = 4;
            this.buttonStop.Text = "Stop All";
            this.buttonStop.UseVisualStyleBackColor = true;
            this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 346);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "HW:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // labelHWVersion
            // 
            this.labelHWVersion.AutoSize = true;
            this.labelHWVersion.Location = new System.Drawing.Point(44, 346);
            this.labelHWVersion.Name = "labelHWVersion";
            this.labelHWVersion.Size = new System.Drawing.Size(69, 13);
            this.labelHWVersion.TabIndex = 6;
            this.labelHWVersion.Text = "<<HW Ver>>";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 366);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(27, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "FW:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // labelFWVersion
            // 
            this.labelFWVersion.AutoSize = true;
            this.labelFWVersion.Location = new System.Drawing.Point(44, 366);
            this.labelFWVersion.Name = "labelFWVersion";
            this.labelFWVersion.Size = new System.Drawing.Size(67, 13);
            this.labelFWVersion.TabIndex = 8;
            this.labelFWVersion.Text = "<<FW Ver>>";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(105, 346);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(33, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "DoM:";
            // 
            // labelDateOfManufacture
            // 
            this.labelDateOfManufacture.AutoSize = true;
            this.labelDateOfManufacture.Location = new System.Drawing.Point(135, 346);
            this.labelDateOfManufacture.Name = "labelDateOfManufacture";
            this.labelDateOfManufacture.Size = new System.Drawing.Size(63, 13);
            this.labelDateOfManufacture.TabIndex = 10;
            this.labelDateOfManufacture.Text = "<<D of M>>";
            // 
            // buttonSettings
            // 
            this.buttonSettings.Location = new System.Drawing.Point(37, 390);
            this.buttonSettings.Name = "buttonSettings";
            this.buttonSettings.Size = new System.Drawing.Size(75, 23);
            this.buttonSettings.TabIndex = 11;
            this.buttonSettings.Text = "Settings";
            this.buttonSettings.UseVisualStyleBackColor = true;
            this.buttonSettings.Click += new System.EventHandler(this.buttonSettings_Click);
            // 
            // textBoxOnLine
            // 
            this.textBoxOnLine.Location = new System.Drawing.Point(206, 338);
            this.textBoxOnLine.Name = "textBoxOnLine";
            this.textBoxOnLine.Size = new System.Drawing.Size(52, 20);
            this.textBoxOnLine.TabIndex = 13;
            this.textBoxOnLine.Text = "On-Line";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(203, 390);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(40, 13);
            this.label6.TabIndex = 23;
            this.label6.Text = "LED 2:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(203, 365);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 22;
            this.label5.Text = "LED 1:";
            // 
            // textBoxLED2
            // 
            this.textBoxLED2.Location = new System.Drawing.Point(242, 387);
            this.textBoxLED2.Name = "textBoxLED2";
            this.textBoxLED2.Size = new System.Drawing.Size(16, 20);
            this.textBoxLED2.TabIndex = 21;
            // 
            // textBoxLED1
            // 
            this.textBoxLED1.Location = new System.Drawing.Point(242, 362);
            this.textBoxLED1.Name = "textBoxLED1";
            this.textBoxLED1.Size = new System.Drawing.Size(16, 20);
            this.textBoxLED1.TabIndex = 20;
            // 
            // timerPolling
            // 
            this.timerPolling.Tick += new System.EventHandler(this.timerPolling_Tick);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(108, 366);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(30, 13);
            this.label4.TabIndex = 24;
            this.label4.Text = "S/N:";
            // 
            // labelSerialNumber
            // 
            this.labelSerialNumber.AutoSize = true;
            this.labelSerialNumber.Location = new System.Drawing.Point(135, 366);
            this.labelSerialNumber.Name = "labelSerialNumber";
            this.labelSerialNumber.Size = new System.Drawing.Size(57, 13);
            this.labelSerialNumber.TabIndex = 25;
            this.labelSerialNumber.Text = "<< S/N >>";
            // 
            // TwoAxisControlPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.labelSerialNumber);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxLED2);
            this.Controls.Add(this.textBoxLED1);
            this.Controls.Add(this.textBoxOnLine);
            this.Controls.Add(this.buttonSettings);
            this.Controls.Add(this.labelDateOfManufacture);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.labelFWVersion);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.labelHWVersion);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonStop);
            this.Controls.Add(this.pictureBoxLogo);
            this.Name = "TwoAxisControlPanel";
            this.Size = new System.Drawing.Size(660, 420);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLogo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MotionAxis motionAxis1;
        private MotionAxis motionAxis2;
        private System.Windows.Forms.PictureBox pictureBoxLogo;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelHWVersion;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelFWVersion;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label labelDateOfManufacture;
        private System.Windows.Forms.Button buttonSettings;
        private System.Windows.Forms.TextBox textBoxOnLine;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxLED2;
        private System.Windows.Forms.TextBox textBoxLED1;
        private System.Windows.Forms.Timer timerPolling;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label labelSerialNumber;
    }
}
