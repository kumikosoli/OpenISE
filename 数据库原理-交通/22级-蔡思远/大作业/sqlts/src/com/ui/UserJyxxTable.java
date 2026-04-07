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

import com.dao.JyxxDao;
import com.entity.Jyxx;

public class UserJyxxTable extends JFrame {

	// 顶部
	public JPanel jpz = new JPanel();
	private JPanel jpatop = new JPanel();
	private JButton jbf = new JButton("归还");

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
		List<Jyxx> myl = new JyxxDao().getAll(str);
		for (Jyxx fk : myl) {// 遍历集合
			// 将数据增加到表模式中
			Vector vec = new Vector();
			vec.add(fk.getJybh());
			vec.add(fk.getSjbh());
			vec.add(fk.getUbh());
			vec.add(fk.getJysj());
			vec.add(fk.getJyts());
			vec.add(fk.getGhsj());
			dtm.addRow(vec);
		}
	}

	public UserJyxxTable(String ubh) {
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
		jpatop.add(jbf);

		// 表列名
		dtm.addColumn("借阅编号");
		dtm.addColumn("书籍编号");
		dtm.addColumn("用户编号");
		dtm.addColumn("借阅时间");
		dtm.addColumn("借阅天数");
		dtm.addColumn("归还时间");

		jtb.setModel(dtm);
		
		// 绑定数据
		myShow(ubh);

		// 归还
		jbf.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int rt = jtb.getSelectedRow();// 选中的行号
				if (rt >= 0) {// 如果选中了
					int t = JOptionPane.showConfirmDialog(null, "确定归还吗？");
					if (t == 0) {
						String sjbh = dtm.getValueAt(rt, 0).toString();
						int n = new JyxxDao().update(sjbh);
						if (n > 0) {
							JOptionPane.showMessageDialog(null, "归还成功！");
							myShow(ubh);
						} else {
							JOptionPane.showMessageDialog(null, "归还失败！");
						}
					}
				} else {
					JOptionPane.showMessageDialog(null, "请选择你要归还的图书!");
				}
			}
		});

		jpz.add(jpatop, "North");
		jpz.add(jpfoot, "South");
		jpz.add(jsp, "Center");

		this.getContentPane().add(jpz);
		this.setVisible(true);

	}

}
