using System;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;

using MetroFramework.Forms;
using MetroFramework.Drawing.Html;

namespace Browser
{
    public partial class MainForm : MetroForm
    {
        private MetroFramework.Controls.MetroTabControl metroTabControl1;
        private MetroFramework.Controls.MetroTabPage Favs;
        private MetroFramework.Controls.MetroTabPage ServerPage;
        private MetroFramework.Controls.MetroTabPage SAMPPlus;
        private MetroFramework.Components.MetroStyleManager metroStyleManager;
        private System.ComponentModel.IContainer components;
        private MetroFramework.Controls.MetroProgressSpinner metroProgressSpinner1;
        private MetroFramework.Controls.MetroScrollBar metroScrollBar1;
        private MetroFramework.Controls.MetroTabPage Hosted;

        public MainForm()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.metroTabControl1 = new MetroFramework.Controls.MetroTabControl();
            this.Favs = new MetroFramework.Controls.MetroTabPage();
            this.ServerPage = new MetroFramework.Controls.MetroTabPage();
            this.SAMPPlus = new MetroFramework.Controls.MetroTabPage();
            this.Hosted = new MetroFramework.Controls.MetroTabPage();
            this.metroStyleManager = new MetroFramework.Components.MetroStyleManager(this.components);
            this.metroProgressSpinner1 = new MetroFramework.Controls.MetroProgressSpinner();
            this.metroScrollBar1 = new MetroFramework.Controls.MetroScrollBar();
            this.metroTabControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.metroStyleManager)).BeginInit();
            this.SuspendLayout();
            // 
            // metroTabControl1
            // 
            this.metroTabControl1.Controls.Add(this.Favs);
            this.metroTabControl1.Controls.Add(this.ServerPage);
            this.metroTabControl1.Controls.Add(this.SAMPPlus);
            this.metroTabControl1.Controls.Add(this.Hosted);
            this.metroTabControl1.Location = new System.Drawing.Point(4, 32);
            this.metroTabControl1.Name = "metroTabControl1";
            this.metroTabControl1.SelectedIndex = 0;
            this.metroTabControl1.Size = new System.Drawing.Size(740, 36);
            this.metroTabControl1.Style = MetroFramework.MetroColorStyle.Lime;
            this.metroTabControl1.TabIndex = 0;
            this.metroTabControl1.UseSelectable = true;
            // 
            // Favs
            // 
            this.Favs.AutoScroll = true;
            this.Favs.HorizontalScrollbar = true;
            this.Favs.HorizontalScrollbarBarColor = true;
            this.Favs.HorizontalScrollbarHighlightOnWheel = false;
            this.Favs.HorizontalScrollbarSize = 10;
            this.Favs.Location = new System.Drawing.Point(4, 38);
            this.Favs.Name = "Favs";
            this.Favs.Padding = new System.Windows.Forms.Padding(25);
            this.Favs.Size = new System.Drawing.Size(732, 0);
            this.Favs.TabIndex = 0;
            this.Favs.Text = "Favourites";
            this.Favs.VerticalScrollbar = true;
            this.Favs.VerticalScrollbarBarColor = true;
            this.Favs.VerticalScrollbarHighlightOnWheel = false;
            this.Favs.VerticalScrollbarSize = 10;
            // 
            // ServerPage
            // 
            this.ServerPage.AutoScroll = true;
            this.ServerPage.HorizontalScrollbar = true;
            this.ServerPage.HorizontalScrollbarBarColor = true;
            this.ServerPage.HorizontalScrollbarHighlightOnWheel = false;
            this.ServerPage.HorizontalScrollbarSize = 10;
            this.ServerPage.Location = new System.Drawing.Point(4, 35);
            this.ServerPage.Name = "ServerPage";
            this.ServerPage.Padding = new System.Windows.Forms.Padding(25);
            this.ServerPage.Size = new System.Drawing.Size(732, -3);
            this.ServerPage.TabIndex = 0;
            this.ServerPage.Text = "Servers";
            this.ServerPage.VerticalScrollbar = true;
            this.ServerPage.VerticalScrollbarBarColor = true;
            this.ServerPage.VerticalScrollbarHighlightOnWheel = false;
            this.ServerPage.VerticalScrollbarSize = 10;
            // 
            // SAMPPlus
            // 
            this.SAMPPlus.AutoScroll = true;
            this.SAMPPlus.HorizontalScrollbar = true;
            this.SAMPPlus.HorizontalScrollbarBarColor = true;
            this.SAMPPlus.HorizontalScrollbarHighlightOnWheel = false;
            this.SAMPPlus.HorizontalScrollbarSize = 10;
            this.SAMPPlus.Location = new System.Drawing.Point(4, 35);
            this.SAMPPlus.Name = "SAMPPlus";
            this.SAMPPlus.Padding = new System.Windows.Forms.Padding(25);
            this.SAMPPlus.Size = new System.Drawing.Size(732, -3);
            this.SAMPPlus.TabIndex = 0;
            this.SAMPPlus.Text = "SAMP+ Servers";
            this.SAMPPlus.VerticalScrollbar = true;
            this.SAMPPlus.VerticalScrollbarBarColor = true;
            this.SAMPPlus.VerticalScrollbarHighlightOnWheel = false;
            this.SAMPPlus.VerticalScrollbarSize = 10;
            // 
            // Hosted
            // 
            this.Hosted.AutoScroll = true;
            this.Hosted.HorizontalScrollbar = true;
            this.Hosted.HorizontalScrollbarBarColor = true;
            this.Hosted.HorizontalScrollbarHighlightOnWheel = false;
            this.Hosted.HorizontalScrollbarSize = 10;
            this.Hosted.Location = new System.Drawing.Point(4, 35);
            this.Hosted.Name = "Hosted";
            this.Hosted.Padding = new System.Windows.Forms.Padding(25);
            this.Hosted.Size = new System.Drawing.Size(732, -3);
            this.Hosted.TabIndex = 0;
            this.Hosted.Text = "Hosted";
            this.Hosted.VerticalScrollbar = true;
            this.Hosted.VerticalScrollbarBarColor = true;
            this.Hosted.VerticalScrollbarHighlightOnWheel = false;
            this.Hosted.VerticalScrollbarSize = 10;
            // 
            // metroStyleManager
            // 
            this.metroStyleManager.Owner = null;
            // 
            // metroProgressSpinner1
            // 
            this.metroProgressSpinner1.Backwards = true;
            this.metroProgressSpinner1.Location = new System.Drawing.Point(4, 459);
            this.metroProgressSpinner1.Maximum = 100;
            this.metroProgressSpinner1.Minimum = 20;
            this.metroProgressSpinner1.Name = "metroProgressSpinner1";
            this.metroProgressSpinner1.Size = new System.Drawing.Size(16, 16);
            this.metroProgressSpinner1.Style = MetroFramework.MetroColorStyle.Lime;
            this.metroProgressSpinner1.TabIndex = 1;
            this.metroProgressSpinner1.UseSelectable = true;
            this.metroProgressSpinner1.UseStyleColors = true;
            this.metroProgressSpinner1.Value = 20;
            // 
            // metroScrollBar1
            // 
            this.metroScrollBar1.LargeChange = 10;
            this.metroScrollBar1.Location = new System.Drawing.Point(730, 76);
            this.metroScrollBar1.Maximum = 100;
            this.metroScrollBar1.Minimum = 0;
            this.metroScrollBar1.MouseWheelBarPartitions = 10;
            this.metroScrollBar1.Name = "metroScrollBar1";
            this.metroScrollBar1.Orientation = MetroFramework.Controls.MetroScrollOrientation.Vertical;
            this.metroScrollBar1.ScrollbarSize = 10;
            this.metroScrollBar1.Size = new System.Drawing.Size(10, 200);
            this.metroScrollBar1.TabIndex = 2;
            this.metroScrollBar1.UseSelectable = true;
            // 
            // MainForm
            // 
            this.ClientSize = new System.Drawing.Size(767, 483);
            this.Controls.Add(this.metroScrollBar1);
            this.Controls.Add(this.metroProgressSpinner1);
            this.Controls.Add(this.metroTabControl1);
            this.Name = "MainForm";
            this.Style = MetroFramework.MetroColorStyle.Lime;
            this.metroTabControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.metroStyleManager)).EndInit();
            this.ResumeLayout(false);

        }

        private void metroTile1_Click(object sender, EventArgs e)
        {

        }

        private void DrawTable(Graphics g, string html, int width)
        {
            PointF point = new PointF(500.0f, 500.0f);
            MetroFramework.Drawing.Html.HtmlRenderer.Render(g, html, point, width);
        }
    }
}