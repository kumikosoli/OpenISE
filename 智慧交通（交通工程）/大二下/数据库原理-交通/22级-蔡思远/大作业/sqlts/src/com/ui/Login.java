package com.ui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.UIManager;

import com.dao.AdminDao;
import com.dao.UseraDao;
import com.entity.Admin;
import com.entity.Usera;

public class Login extends JFrame {

	public static void main(String[] args) {
		// 新建一个Login类
		new Login();
	}

	// 放标题的容器
	private JPanel jpn = new JPanel();
	// 放用户名，密码，登陆，取消按钮的容器
	private JPanel jpa = new JPanel();

	private JLabel jla = new JLabel("用户名:");
	private JTextField jtf = new JTextField(16);
	private JLabel jlb = new JLabel("密  码:");
	private JPasswordField jpf = new JPasswordField(16);
	private JLabel jlc = new JLabel("身  份:");
	public JRadioButton s1 = new JRadioButton("游客", true);
	public JRadioButton s2 = new JRadioButton("读者");
	public JRadioButton s3 = new JRadioButton("管理员");
	private JButton jba = new JButton("登陆");
	private JButton jbb = new JButton("读者注册");

	// new一个dao类
	UseraDao ud = new UseraDao();
	
	// 单选按钮的组，放入同一个组就能够实现单选的效果
	public ButtonGroup g = new ButtonGroup();

	// 总容器
	private JPanel jpz = new JPanel();

	public Login() {
		// 加入背景图
		MyJpanel jpz = new MyJpanel("img/back.jpg", 450, 250);
		// 将容器设置为透明，便于显示图片
		jpn.setOpaque(false);
		jpa.setOpaque(false);
		
		// 将单选按钮加入同一个组中
		g.add(s1);
		g.add(s2);
		g.add(s3);

		this.setTitle("登录界面");
		this.setSize(450, 250);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(3);
		this.setResizable(false);// 设置窗体无法改变大小
		GridBagLayout gbl = new GridBagLayout();
		GridBagConstraints gbc = new GridBagConstraints();
		jpa.setLayout(gbl);

		// 用户名以及其文本框的位置
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbl.setConstraints(jla, gbc);// 让约束对象来约束jla(坐标)
		jpa.add(jla);// 将jla增加到容器中

		gbc.gridx = 1;
		gbc.gridy = 0;
		gbl.setConstraints(jtf, gbc);
		jpa.add(jtf);

		// 密码以及其文本框的位置
		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.insets = new Insets(20, 0, 0, 0);
		gbl.setConstraints(jlb, gbc);
		jpa.add(jlb);

		gbc.gridx = 1;
		gbc.gridy = 1;
		gbl.setConstraints(jpf, gbc);
		jpa.add(jpf);

		// 身份的位置
		gbc.gridx = 0;
		gbc.gridy = 2;
		gbl.setConstraints(jlc, gbc);
		jpa.add(jlc);

		gbc.gridx = 1;
		gbc.gridy = 2;
		gbl.setConstraints(s1, gbc);
		jpa.add(s1);
		
		gbc.gridx = 2;
		gbc.gridy = 2;
		gbl.setConstraints(s2, gbc);
		jpa.add(s2);
		
		gbc.gridx = 3;
		gbc.gridy = 2;
		gbl.setConstraints(s3, gbc);
		jpa.add(s3);

		// 按钮位置
		gbc.gridx = 1;
		gbc.gridy = 3;
		gbl.setConstraints(jba, gbc);
		jpa.add(jba);

		gbc.gridx = 2;
		gbc.gridy = 3;
		gbl.setConstraints(jbb, gbc);
		jpa.add(jbb);

		// 标题
		JLabel jlc = new JLabel("图书管理系统登录界面");
		jlc.setFont(new Font("宋体", Font.BOLD, 15));
		jpn.add(jlc);

		// 登陆方法
		jba.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// 获取对应文本框的值
				String uname = jtf.getText();
				String upwd = jpf.getText();
				String urole = "";
				if (s1.isSelected()) {
					urole = "游客";
				}
				if (s2.isSelected()) {
					urole = "读者";
				}
				if (s3.isSelected()) {
					urole = "管理员";
				}
				if (urole.equals("管理员")) {
					boolean f = new AdminDao().login(uname,upwd);
					// 判断方法是否执行成功
					if (f) {
						JOptionPane.showMessageDialog(null, "管理员登陆成功！");
						new Meau();
						Login.this.dispose();
					} else {
						JOptionPane.showMessageDialog(null, "管理员登陆失败！");
					}
				} else if (urole.equals("游客")) {
					JOptionPane.showMessageDialog(null, "游客进入成功！");
					new YkSjTable();
					Login.this.dispose();
				} else {
					String ubh=new UseraDao().login(uname, upwd);
					if (ubh != null) {
						JOptionPane.showMessageDialog(null, "读者登陆成功！");
						new UserMeau(ubh);
						Login.this.dispose();
					}else {
						JOptionPane.showMessageDialog(null, "读者登陆失败！");
					}
				}
			}
		});

		// 注册
		jbb.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				new AddUser();
			}
		});

		// 将小容器加入总容器中
		jpz.add(jpn, "North");
		jpz.add(jpa, "Center");
		this.getContentPane().add(jpz);
		this.setVisible(true);
	}

}
