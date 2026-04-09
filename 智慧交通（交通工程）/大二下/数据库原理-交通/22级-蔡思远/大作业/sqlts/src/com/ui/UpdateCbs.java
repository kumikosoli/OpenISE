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
import java.util.Date;
import java.util.List;

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

import com.dao.CbsDao;
import com.entity.Cbs;

public class UpdateCbs extends JFrame {

	// 放标题的容器
	private JPanel jpn = new JPanel();
	private JPanel jpa = new JPanel();

	private JLabel jla = new JLabel("出版社编号：");
	private JLabel jcba = new JLabel();
	private JLabel jlb = new JLabel("出版社名字：");
	private JTextField jcbb = new JTextField(12);
	private JLabel jlc = new JLabel("负责人：");
	private JTextField jcbc = new JTextField(12);
	private JLabel jld = new JLabel("联系电话：");
	private JTextField jcbd = new JTextField(12);
	private JLabel jle = new JLabel("具体位置：");
	private JTextField jcbe = new JTextField(12);
	
	private JButton jba = new JButton("修改");
	
	// 总容器
	private JPanel jpz = new JPanel();

	public UpdateCbs(CbsTable t,Cbs Cbs) {
		// 加入背景图
		MyJpanel jpz = new MyJpanel("img/back.jpg", 350, 450);

		// 将容器设置为透明，便于显示图片
		jpn.setOpaque(false);
		jpa.setOpaque(false);
				
		this.setTitle("修改界面");
		this.setSize(350, 450);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(2);
		this.setResizable(false);// 设置窗体无法改变大小
		GridBagLayout gbl = new GridBagLayout();
		GridBagConstraints gbc = new GridBagConstraints();
		jpa.setLayout(gbl);
		
		// 编号以及其文本框的位置
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbl.setConstraints(jla, gbc);// 让约束对象来约束jla(坐标)
		jpa.add(jla);// 将jla修改到容器中

		gbc.gridx = 1;
		gbc.gridy = 0;
		gbl.setConstraints(jcba, gbc);
		jpa.add(jcba);

		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.insets = new Insets(20, 0, 0, 0);
		gbl.setConstraints(jlb, gbc);
		jpa.add(jlb);

		gbc.gridx = 1;
		gbc.gridy = 1;
		gbl.setConstraints(jcbb, gbc);
		jpa.add(jcbb);

		gbc.gridx = 0;
		gbc.gridy = 2;
		gbl.setConstraints(jlc, gbc);
		jpa.add(jlc);
		
		gbc.gridx = 1;
		gbc.gridy = 2;
		gbl.setConstraints(jcbc, gbc);
		jpa.add(jcbc);
		
		gbc.gridx = 0;
		gbc.gridy = 3;
		gbl.setConstraints(jld, gbc);
		jpa.add(jld);
		
		gbc.gridx = 1;
		gbc.gridy = 3;
		gbl.setConstraints(jcbd, gbc);
		jpa.add(jcbd);
		
		gbc.gridx = 0;
		gbc.gridy = 4;
		gbl.setConstraints(jle, gbc);
		jpa.add(jle);
		
		gbc.gridx = 1;
		gbc.gridy = 4;
		gbl.setConstraints(jcbe, gbc);
		jpa.add(jcbe);
		
		// 按钮位置
		gbc.gridx = 1;
		gbc.gridy = 5;
		gbl.setConstraints(jba, gbc);
		jpa.add(jba);
		
		jcba.setText(Cbs.getCbsbh());
		jcbb.setText(Cbs.getMz());
		jcbc.setText(Cbs.getFzr());
		jcbd.setText(Cbs.getLxdh());
		jcbe.setText(Cbs.getJtwz());
		
		// 修改方法
		jba.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// 获取对应文本框的值
				String a = jcba.getText();
				String b = jcbb.getText();
				String c = jcbc.getText();
				String d = jcbd.getText();
				String ea = jcbe.getText();
				Cbs fkxx=new Cbs(a, b, c, d,ea);
				int ia = new CbsDao().update(fkxx);
				if (ia > 0) {
					JOptionPane.showMessageDialog(null, "修改成功！");
					t.myShow("");
				} else {
					JOptionPane.showMessageDialog(null, "修改失败！");
				}
			}
		});

		// 将小容器加入总容器中
		jpz.add(jpn, "North");
		jpz.add(jpa, "Center");
		this.getContentPane().add(jpz);
		this.setVisible(true);
	}

}
