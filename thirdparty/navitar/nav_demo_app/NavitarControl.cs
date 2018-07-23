using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Navitar.Demos
{
    public partial class NavitarControl : UserControl
    {
        public NavitarControl()
        {
            InitializeComponent();
        }

        public NavitarControl(Controller controller)
        {
            InitializeComponent();

            MyController = controller;
        }

        public Controller MyController { get; protected set; }
    }
}
