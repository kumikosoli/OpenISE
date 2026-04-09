package com.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import com.entity.Sjlb;
import com.entity.Sjlb;
import com.util.DBhelper;

public class SjlbDao {

	// 修改方法
	public int update(Sjlb a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement(
					"update sjlb set mc=?,bz=? where bh=" + a.getBh());
			ps.setString(1, a.getMc());
			ps.setString(2, a.getBz());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 删除方法
	public int delete(String Sjlbh) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("delete from sjlb where bh=" + Sjlbh);
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 增加方法
	public int add(Sjlb a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("insert into sjlb(bh,mc,bz) "
					+ "values(?,?,?)");
			ps.setString(1, a.getBh());
			ps.setString(2, a.getMc());
			ps.setString(3, a.getBz());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 查询
	public List<Sjlb> getAll(String str) {
		List<Sjlb> ss = new ArrayList<Sjlb>();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from sjlb where mc like '%"+str+"%'");
			rs = ps.executeQuery();
			while (rs.next()) {
				Sjlb s = new Sjlb();
				s.setBh(rs.getString(1));
				s.setMc(rs.getString(2));
				s.setBz(rs.getString(3));
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
	public Sjlb getOne(String cph) {
		Sjlb s = new Sjlb();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from Sjlb where bh="+cph);
			rs = ps.executeQuery();
			while (rs.next()) {
				s.setBh(rs.getString(1));
				s.setMc(rs.getString(2));
				s.setBz(rs.getString(3));
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return s;
	}

}
