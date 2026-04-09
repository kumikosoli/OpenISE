package com.ui;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Date;
import java.util.List;
import java.util.Vector;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.UIManager;
import javax.swing.plaf.nimbus.State;
import javax.swing.table.DefaultTableModel;

import com.dao.SjDao;
import com.entity.Sj;

public class YkSjTable extends JFrame {

	// 顶部
	public JPanel jpz = new JPanel();
	private JPanel jpatop = new JPanel();
	private JLabel jla = new JLabel("名称：");
	private JTextField jtfa = new JTextField(12);
	private JButton jbf = new JButton("查询");
	private JButton jbc = new JButton("申请读者");

	// 底部
	private JPanel jpfoot = new JPanel();

	// 表
	private JTable jtb = new JTable();
	private DefaultTableModel dtm = new DefaultTableModel();
	private JScrollPane jsp = new JScrollPane(jtb);

	public void myShow(String str) {
		// 清空以前的数据
		// 取到表中以前有多少行数据
		int rows = dtm.getRowCount();
		for (int i = 0; i < rows; i++) {
			dtm.removeRow(0);// 根据下标移除
		}
		List<Sj> myl = new SjDao().getAlla(str);
		for (Sj fk : myl) {// 遍历集合
			// 将数据增加到表模式中
			Vector vec = new Vector();
			vec.add(fk.getSjbh());
			vec.add(fk.getSm());
			vec.add(fk.getCbsbh());
			vec.add(fk.getDj());
			vec.add(fk.getZz());
			vec.add(fk.getLbbh());
			dtm.addRow(vec);
		}
	}

	public YkSjTable() {
		// 加入背景图
		MyJpanel jpz = new MyJpanel("img/back.jpg", 750, 550);

		// 将容器设置为透明，便于显示图片
		jpfoot.setOpaque(false);
		jpatop.setOpaque(false);
		
		this.setTitle("数据查看界面");
		this.setSize(750, 550);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(2);

		// 容器加物件
		jpatop.add(jla);
		jpatop.add(jtfa);
		jpatop.add(jbf);
		jpatop.add(jbc);

		// 表列名
		dtm.addColumn("书籍编号");
		dtm.addColumn("书名");
		dtm.addColumn("出版社编号");
		dtm.addColumn("单价");
		dtm.addColumn("作者");
		dtm.addColumn("类别编号");

		jtb.setModel(dtm);
		
		// 绑定数据
		myShow("");

		// 查询
		jbf.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				String cj = jtfa.getText();
				myShow(cj);
			}
		});

		// 读者事件
		jbc.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				new AddUser();
			}
		});

		jpz.add(jpatop, "North");
		jpz.add(jpfoot, "South");
		jpz.add(jsp, "Center");

		this.getContentPane().add(jpz);
		this.setVisible(true);

	}

}
