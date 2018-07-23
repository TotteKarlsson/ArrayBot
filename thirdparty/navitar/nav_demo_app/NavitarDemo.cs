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
    public partial class NavitarDemo : Form
    {
        public NavitarDemo()
        {
            InitializeComponent();
            GetControllers();

            string[] args = Environment.GetCommandLineArgs();
            if (args.Length > 0 &&
                args.Where(c => c == "/e").Count() > 0)
            {
                this.navitarToolStripMenuItem.Visible = true;
            }
            else
            {
                this.navitarToolStripMenuItem.Visible = false;
            }
        }

        private void GetControllers()
        {
            ControllerHub.DiscoverControllers();
            ICollection<Controller> controllers = ControllerHub.GetAll();

            foreach (Controller controller in controllers)
            {
                if ((controller.ProductID == 0x4001 || controller.ProductID == 0x5001) &&
                    (controller.ProductSubclass == 2 || controller.ProductSubclass == 3 ||
                     controller.ProductSubclass == 1 || controller.ProductSubclass == (unchecked((int)0xffffffd9))))
                {
                    TabPage page = new TabPage(controller.Name);
                    page.Controls.Add(new TwoAxisControlPanel(controller));
                    this.tabControl1.TabPages.Add(page);
                }
                else if (controller.ProductID == 0x4000)
                {
                    TabPage page = new TabPage(controller.Name);
                    page.Controls.Add(new LEDControlPanel(controller));
                    this.tabControl1.TabPages.Add(page);
                }
            }

            if (tabControl1.TabPages.Count != 0)
            {
                tabControl1.SelectedIndex = 0;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.ToString();
            string copyright = ((System.Reflection.AssemblyCopyrightAttribute)Attribute.GetCustomAttribute(System.Reflection.Assembly.GetExecutingAssembly(), typeof(System.Reflection.AssemblyCopyrightAttribute), false)).Copyright;

            MessageBox.Show("Navitar Controller Demo Application \n" 
                + "Version " + version + "\n\n"
                + copyright, "About", MessageBoxButtons.OK);
        }

        private void enterBootloaderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (tabControl1.SelectedTab == null)
            {
                return;
            }

            NavitarControl control = tabControl1.SelectedTab.Controls[0] as NavitarControl;
            Controller controller = control.MyController;
            if (controller.Generation == 2)
            {
                ControllerGen2 secondGen = controller as ControllerGen2;

                // Get rid of tab
                TabPage page = tabControl1.SelectedTab;
                tabControl1.TabPages.Remove(page);
                page.Dispose();

                // Set wait cursor since operation takes a few seconds.
                Cursor.Current = Cursors.WaitCursor;

                // Enter bootloader
                secondGen.EnterBootloader();

                ControllerHub.RemoveController(secondGen);

                // Be patient while USB CDC device drops off bus.
                System.Threading.Thread.Sleep(2500);

                // Clear the wait cursor.
                Cursor.Current = Cursors.Default;
            }
            else
            {
                MessageBox.Show("Enter Bootloader command not supported for this controller.", "Feature Not Supported", MessageBoxButtons.OK);
            }
        }

        private String getDFUErrMsg(int errorcode)
        {
            switch (errorcode)
            {
                case 0:
                    return "";
                case 1:
                    return "Controller not found";
                case 10:
                    return "Unable to open file";
                case 20:
                    return "Unable to erase controller flash";
                case 40:
                    return "Device does not support TI DFU protocol";
                case 100:
                    return "Cannot switch controller into DFU mode";
                default:
                    return "error " + errorcode.ToString();
            }
        }

        private void upgradeFirmwareToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Browse for firmware binary image file
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "bin files (*.bin)|*.bin";
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                //dlg.FileName

                // Set wait cursor since operation takes a few seconds.
                Cursor.Current = Cursors.WaitCursor;

                // Be patient while DFU device appears on bus.
                System.Threading.Thread.Sleep(2500);

                // Now attempt to execute the DFU programming application to erase flash and program bin file.
                System.Diagnostics.Process eraseProcess = new System.Diagnostics.Process();
                eraseProcess.StartInfo.FileName = "dfuprog.exe";
                eraseProcess.StartInfo.Arguments = "-c -a 0x3e0000 -l 0x18000";
                eraseProcess.StartInfo.UseShellExecute = false;
                //eraseProcess.StartInfo.RedirectStandardError = true;
                //eraseProcess.StartInfo.RedirectStandardOutput = true;
                eraseProcess.Start();
                //string eError = eraseProcess.StandardOutput.ReadToEnd();
                eraseProcess.WaitForExit();

                if (eraseProcess.ExitCode != 0)
                {
                    String msg = getDFUErrMsg(eraseProcess.ExitCode);
                    MessageBox.Show(msg, "Firmware Upgrade Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    System.Diagnostics.Process flashProcess = new System.Diagnostics.Process();
                    flashProcess.StartInfo.FileName = "dfuprog.exe";
                    flashProcess.StartInfo.Arguments = "-f \"" + dlg.FileName + "\" -a 0x3e0000";
                    flashProcess.StartInfo.UseShellExecute = false;
                    //flashProcess.StartInfo.RedirectStandardError = true;
                    //flashProcess.StartInfo.RedirectStandardOutput = true;
                    flashProcess.Start();
                    //string pError = flashProcess.StandardOutput.ReadToEnd();
                    flashProcess.WaitForExit();

                    if (flashProcess.ExitCode != 0)
                    {
                        String msg = getDFUErrMsg(eraseProcess.ExitCode);
                        MessageBox.Show(msg,"Firmware Upgrade Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        MessageBox.Show("Please power-cycle the controller." +
                                        "Wait\n for controller to initialize," +
                                        "then choose\n\"File > Disover Controllers\" above.",
                            "Firmware Upgrade Completed", MessageBoxButtons.OK);

                    }
                }


                // Clear the wait cursor.
                Cursor.Current = Cursors.Default;

            }
        }

        private void discoverControllersToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (TabPage page in tabControl1.TabPages)
            {
                page.Dispose();
            }
            tabControl1.TabPages.Clear();

            GetControllers();
        }

        private void tabControl1_Selected(object sender, TabControlEventArgs e)
        {
            enterBootloaderToolStripMenuItem.Enabled = false;
            if (tabControl1.SelectedTab != null)
            {
                NavitarControl control = tabControl1.SelectedTab.Controls[0] as NavitarControl;
                Controller controller = control.MyController;
                if (controller.Generation == 2)
                {
                    enterBootloaderToolStripMenuItem.Enabled = true;
                }
            }
        }

        private void tabControl1_ControlAdded(object sender, ControlEventArgs e)
        {
            enterBootloaderToolStripMenuItem.Enabled = false;
            if (tabControl1.SelectedTab != null)
            {
                NavitarControl control = tabControl1.SelectedTab.Controls[0] as NavitarControl;
                Controller controller = control.MyController;
                if (controller.Generation == 2)
                {
                    enterBootloaderToolStripMenuItem.Enabled = true;
                }
            }
        }
    }
}
