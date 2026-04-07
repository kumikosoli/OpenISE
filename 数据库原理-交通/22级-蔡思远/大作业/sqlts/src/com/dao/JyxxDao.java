package com.dao;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JOptionPane;

import com.entity.Jyxx;
import com.util.DBhelper;

public class JyxxDao {

	// 修改方法
	public int update(String jybh) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement(
					"update jyxx set ghsj=getdate() where jybh=" + jybh);
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 删除方法
	public int delete(String jyxxh) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("delete from jyxx where jybh=" + jyxxh);
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 增加方法
	public int add(Jyxx a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("insert into jyxx(jybh,sjbh,ubh,jysj,jyts) "
					+ "values(?,?,?,getdate(),?)");
			ps.setString(1, a.getJybh());
			ps.setString(2, a.getSjbh());
			ps.setString(3, a.getUbh());
			ps.setInt(4, a.getJyts());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 查询
	public List<Jyxx> getAll(String str) {
		List<Jyxx> ss = new ArrayList<Jyxx>();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from jyxx where ubh like '%"+str+"%'");
			rs = ps.executeQuery();
			while (rs.next()) {
				Jyxx s = new Jyxx();
				s.setJybh(rs.getString(1));
				s.setSjbh(rs.getString(2));
				s.setUbh(rs.getString(3));
				s.setJysj(rs.getDate(4));
				s.setJyts(rs.getInt(5));
				s.setGhsj(rs.getDate(6));
				ss.add(s);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return ss;
	}
	
	public boolean getF(String str) {
		boolean f=false;
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from jyxx where ubh like '%"+str+"%' and ghsj is null and DATEADD(day, jyts,jysj)<getdate()");
			rs = ps.executeQuery();
			while (rs.next()) {
				f=true;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return f;
	}
	
}
