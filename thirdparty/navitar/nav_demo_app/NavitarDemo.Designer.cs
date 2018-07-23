namespace Navitar.Demos
{
    partial class NavitarDemo
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NavitarDemo));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.discoverControllersToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.navitarToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.upgradeFirmwareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.enterBootloaderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControl1.Location = new System.Drawing.Point(13, 27);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(682, 449);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.Selected += new System.Windows.Forms.TabControlEventHandler(this.tabControl1_Selected);
            this.tabControl1.ControlAdded += new System.Windows.Forms.ControlEventHandler(this.tabControl1_ControlAdded);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem,
            this.navitarToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(707, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.discoverControllersToolStripMenuItem,
            this.connectionToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // discoverControllersToolStripMenuItem
            // 
            this.discoverControllersToolStripMenuItem.Name = "discoverControllersToolStripMenuItem";
            this.discoverControllersToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.discoverControllersToolStripMenuItem.Text = "Discover Controllers";
            this.discoverControllersToolStripMenuItem.Click += new System.EventHandler(this.discoverControllersToolStripMenuItem_Click);
            // 
            // connectionToolStripMenuItem
            // 
            this.connectionToolStripMenuItem.Name = "connectionToolStripMenuItem";
            this.connectionToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.connectionToolStripMenuItem.Text = "Exit";
            this.connectionToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // navitarToolStripMenuItem
            // 
            this.navitarToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.enterBootloaderToolStripMenuItem,
            this.upgradeFirmwareToolStripMenuItem});
            this.navitarToolStripMenuItem.Name = "navitarToolStripMenuItem";
            this.navitarToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.navitarToolStripMenuItem.Text = "Navitar";
            // 
            // upgradeFirmwareToolStripMenuItem
            // 
            this.upgradeFirmwareToolStripMenuItem.Name = "upgradeFirmwareToolStripMenuItem";
            this.upgradeFirmwareToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.upgradeFirmwareToolStripMenuItem.Text = "Upgrade Firmware";
            this.upgradeFirmwareToolStripMenuItem.Click += new System.EventHandler(this.upgradeFirmwareToolStripMenuItem_Click);
            // 
            // enterBootloaderToolStripMenuItem
            // 
            this.enterBootloaderToolStripMenuItem.Name = "enterBootloaderToolStripMenuItem";
            this.enterBootloaderToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.enterBootloaderToolStripMenuItem.Text = "Enter Bootloader";
            this.enterBootloaderToolStripMenuItem.Click += new System.EventHandler(this.enterBootloaderToolStripMenuItem_Click);
            // 
            // NavitarDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(707, 488);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "NavitarDemo";
            this.Text = "Navitar Controller Demo";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem connectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem navitarToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem upgradeFirmwareToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem discoverControllersToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem enterBootloaderToolStripMenuItem;
    }
}

