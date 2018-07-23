using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Navitar.Demos
{
    public partial class VProgress : ProgressBar 
    {
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.Style |= 0x04;
                return cp;
            }
        }

        protected override System.Drawing.Size DefaultSize 
        {
            get 
            {
                return new System.Drawing.Size(23, 100);
            }
        }
    }
}
