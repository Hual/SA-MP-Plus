using System;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;

using MetroFramework.Forms;

namespace MetroFramework.Browser
{
    public partial class MainForm : MetroForm
    {
        public MainForm()
        {
            InitializeComponent();

        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // MainForm
            // 
            this.ClientSize = new System.Drawing.Size(584, 388);
            this.Name = "MainForm";
            this.ResumeLayout(false);

        }
    }
}