package com.dao;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JOptionPane;

import com.entity.Cbs;
import com.entity.Cbs;
import com.util.DBhelper;

public class CbsDao {

	// 修改方法
	public int update(Cbs a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement(
					"update cbs set mz=?,fzr=?,lxdh=?,jtwz=? where cbsbh=" + a.getCbsbh());
			ps.setString(1, a.getMz());
			ps.setString(2, a.getFzr());
			ps.setString(3, a.getLxdh());
			ps.setString(4, a.getJtwz());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 删除方法
	public int delete(String Cbsh) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("delete from cbs where cbsbh=" + Cbsh);
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 增加方法
	public int add(Cbs a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("insert into cbs(cbsbh,mz,fzr,lxdh,jtwz) "
					+ "values(?,?,?,?,?)");
			ps.setString(1, a.getCbsbh());
			ps.setString(2, a.getMz());
			ps.setString(3, a.getFzr());
			ps.setString(4, a.getLxdh());
			ps.setString(5, a.getJtwz());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 查询
	public List<Cbs> getAll(String mz) {
		List<Cbs> ss = new ArrayList<Cbs>();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from cbs where mz like '%"+mz+"%'");
			rs = ps.executeQuery();
			while (rs.next()) {
				Cbs s = new Cbs();
				s.setCbsbh(rs.getString(1));
				s.setMz(rs.getString(2));
				s.setFzr(rs.getString(3));
				s.setLxdh(rs.getString(4));
				s.setJtwz(rs.getString(5));
				ss.add(s);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return ss;
	}
	
	// 查询
	public Cbs getOne(String cph) {
		Cbs s = new Cbs();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from cbs where cbsbh="+cph);
			rs = ps.executeQuery();
			while (rs.next()) {
				s.setCbsbh(rs.getString(1));
				s.setMz(rs.getString(2));
				s.setFzr(rs.getString(3));
				s.setLxdh(rs.getString(4));
				s.setJtwz(rs.getString(5));
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return s;
	}

}
