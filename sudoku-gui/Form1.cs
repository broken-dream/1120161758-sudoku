using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace sudoku_gui
{
    public partial class Form1 : Form
    {
        private int[,] mp =new int [9,9];
        private int[] shift = { 0, 3, 6, 2, 5, 8, 1, 4, 7 };
        private int cnt = 0;
        private TextBox[,] allbox = new TextBox[9,9];
        private bool[,] visit_row = new bool[9, 10];
        private bool[,] visit_col = new bool[9, 10];
        private bool[,,] visit_sq = new bool[3, 3, 10];
        private int[,] cnt_sq = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            get();
            generate();
            show();
        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }
        private void TextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        public void generate()
        {   Random random = new Random();
            for(int i = 0; i < 9; i++)
            {
                mp[0,i] = i + 1;
            }
            for(int i = 0; i < 10; i++)
            {
              
                int idx1 = random.Next() % 9;
                int idx2 = random.Next() % 9;
                int cur = mp[0, idx1];
                mp[0, idx1] = mp[0, idx2];
                mp[0, idx2] = cur;
            }
            for(int row = 1; row < 9; row++)
            {
                for(int col = 0; col < 9; col++)
                {
                    mp[row, (col + shift[row]) % 9] = mp[0, col];
                }
            }
            for(int row=0;row<9; row++)
            {
                for(int col = 0; col < 6; col++)
                {
                    int idx = random.Next(0, 9);
                    if (mp[row, idx] != 0)
                    {
                        cnt_sq[row / 3, idx / 3]++;
                        cnt++;
                    }
                    mp[row, idx] = 0;
                }
            }
            addition();
        }
        public void show()
        {
            for(int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    if (mp[row, col] == 0) continue;
                    TextBox cur = allbox[row, col];
                    Color curcolor = cur.BackColor;
                    cur.Text = mp[row, col].ToString();
                    cur.ReadOnly = true;
                    cur.BackColor = curcolor;
                    cur.ForeColor = Color.Red;
                }
            }
        }
        public void get()
        {
            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    allbox[row,col] = (TextBox)tableLayoutPanel1.GetControlFromPosition(col, row);
                }
            }
        }
        public void check()
        {
            vis_reset();
            bool flag = false;
            for(int row = 0; row < 9; row++)
            {
                if (flag) break;
                for(int col = 0; col < 9; col++)
                {
                    if (allbox[row, col].Text == "")
                    {
                        flag = true;
                        break;
                    }
                    int cur = Convert.ToInt32(allbox[row, col].Text);
                    if (judge(row, col, cur))
                    {
                        flag = true;
                        break;
                    }
                    visit_row[row, cur] = true;
                    visit_col[col, cur] = true;
                    visit_sq[row / 3, col / 3, cur] = true;
                }
            }
            if (flag)
            {
                MessageBox.Show("回答有误");
            }
            else
            {
                MessageBox.Show("正确");
            }
        }
        public bool judge(int row,int col,int cur)
        {
            if (visit_row[row, cur] ||
                visit_col[col, cur] ||
                visit_sq[row / 3, col / 3, cur])
                return true;
            return false;
        }
        public void vis_reset()
        {
            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    visit_row[row, col+1] = false;
                    visit_col[row, col+1] = false;
                }
            }
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    for(int num = 1; num < 10; num++)
                    {
                        visit_sq[i, j, num] = false;
                    }
                }
            }
        }
        public void reset()
        {
            for(int row = 0; row < 9; row++)
            {
                for(int col = 0; col < 9; col++)
                {
                    allbox[row, col].ReadOnly = false;
                    allbox[row, col].ForeColor = SystemColors.WindowText;
                    allbox[row, col].Text = "";
                }
            }
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    cnt_sq[i, j] = 0;
                    cnt = 0;
                }
            }
        }
        public void addition()
        {
            if (cnt < 30)
            {
                for(int row = 0; row < 9; row++)
                {
                    if (cnt > 30) break;
                    for(int col=0;col<9; col++)
                    {
                        if (mp[row, col] != 0)
                        {
                            mp[row, col] = 0;
                            cnt++;
                        }
                        if (cnt > 30) break;
                    }
                }
            }

            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if (cnt_sq[i, j] < 2)
                    {
                        for(int row = i * 3; row < i * 3 + 3; row++)
                        {
                            if (cnt_sq[i, j] >= 2) break;
                            for (int col = j * 3; col < j * 3 + 3; col++)
                            {
                                if (mp[row, col] != 0)
                                {
                                    mp[row, col] = 0;
                                    cnt_sq[i, j]++;
                                }
                                if (cnt_sq[i, j] >= 2) break;
                            }
                        }
                    }
                }
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            check();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            reset();
            vis_reset();
            generate();
            show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9;j++)
                {
                    if (allbox[i, j].ReadOnly == true)
                    {
                        continue;
                    }
                    allbox[i, j].Text = "";
                }
                
            }
        }
    }
}
