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

import com.dao.SjlbDao;
import com.entity.Sjlb;

public class SjlbTable extends JFrame {

	// 顶部
	public JPanel jpz = new JPanel();
	private JPanel jpatop = new JPanel();
	private JLabel jla = new JLabel("名称：");
	private JTextField jtfa = new JTextField(12);
	private JButton jbf = new JButton("查询");
	private JButton jbc = new JButton("增加");
	private JButton jbd = new JButton("修改");
	private JButton jbe = new JButton("删除");

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
		List<Sjlb> myl = new SjlbDao().getAll(str);
		for (Sjlb fk : myl) {// 遍历集合
			// 将数据增加到表模式中
			Vector vec = new Vector();
			vec.add(fk.getBh());
			vec.add(fk.getMc());
			vec.add(fk.getBz());
			dtm.addRow(vec);
		}
	}

	public void del() {
		int rt = jtb.getSelectedRow();// 选中的行号
		if (rt >= 0) {// 如果选中了
			int t = JOptionPane.showConfirmDialog(null, "确定删除吗？");
			if (t == 0) {
				String id = dtm.getValueAt(rt, 0).toString();
				int n = new SjlbDao().delete(id);
				if (n > 0) {
					// 刷新数据
					JOptionPane.showMessageDialog(null, "删除成功！");
					myShow("");
				} else {
					JOptionPane.showMessageDialog(null, "删除失败！");
				}
			}
		} else {
			JOptionPane.showMessageDialog(null, "请选择你要删除的数据!");
		}

	}

	public SjlbTable() {
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
		jpatop.add(jbd);
		jpatop.add(jbe);

		// 表列名
		dtm.addColumn("编号");
		dtm.addColumn("名称");
		dtm.addColumn("备注");

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

		// 增加事件
		jbc.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				new AddSjlb(SjlbTable.this);
			}
		});

		// 删除事件
		jbe.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				del();
			}
		});

		// 修改事件
		jbd.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int rt = jtb.getSelectedRow();// 选中的行号
				if (rt >= 0) {// 如果选中了
					int t = JOptionPane.showConfirmDialog(null, "确定修改吗？");
					if (t == 0) {
						String tid = dtm.getValueAt(rt, 0).toString();
						Sjlb fk = new SjlbDao().getOne(tid);
						new UpdateSjlb(SjlbTable.this, fk);
					}
				} else {
					JOptionPane.showMessageDialog(null, "请选择你要修改的信息!");
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
