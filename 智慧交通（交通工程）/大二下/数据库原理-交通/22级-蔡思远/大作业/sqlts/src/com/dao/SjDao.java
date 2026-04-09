package com.dao;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JOptionPane;

import com.entity.Sj;
import com.entity.Sj;
import com.entity.Sj;
import com.util.DBhelper;

public class SjDao {

	// 修改方法
	public int update(Sj a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement(
					"update sj set sm=?,cbsbh=?,dj=?,zz=?,lbbh=?,gcsl=?kjsl=?,sfkj=? where sjbh=" + a.getSjbh());
			ps.setString(1, a.getSm());
			ps.setString(2, a.getCbsbh());
			ps.setFloat(3, a.getDj());
			ps.setString(4, a.getZz());
			ps.setString(5, a.getLbbh());
			ps.setInt(6, a.getGcsl());
			ps.setInt(7, a.getKjsl());
			ps.setString(8, a.getSfkj());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 删除方法
	public int delete(String Sjh) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("delete from sj where sjbh=" + Sjh);
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 增加方法
	public int add(Sj a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("insert into sj(sjbh,sm,cbsbh,dj,zz,lbbh) "
					+ "values(?,?,?,?,?,?,?,?,?)");
			ps.setString(1, a.getSjbh());
			ps.setString(2, a.getSm());
			ps.setString(3, a.getCbsbh());
			ps.setFloat(4, a.getDj());
			ps.setString(5, a.getZz());
			ps.setString(6, a.getLbbh());
			ps.setInt(7, a.getGcsl());
			ps.setInt(8, a.getKjsl());
			ps.setString(9, a.getSfkj());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 查询
	public List<Sj> getAlla(String str) {
		List<Sj> ss = new ArrayList<Sj>();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from sj where sm like '%"+str+"%' and kjsl>0");
			rs = ps.executeQuery();
			while (rs.next()) {
				Sj s = new Sj();
				s.setSjbh(rs.getString(1));
				s.setSm(rs.getString(2));
				s.setCbsbh(rs.getString(3));
				s.setDj(rs.getFloat(4));
				s.setZz(rs.getString(5));
				s.setLbbh(rs.getString(6));
				s.setGcsl(rs.getInt(7));
				s.setKjsl(rs.getInt(8));
				s.setSfkj(rs.getString(9));
				ss.add(s);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return ss;
	}
	
	public List<Sj> getAll(String str) {
		List<Sj> ss = new ArrayList<Sj>();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from sj where sm like '%"+str+"%'");
			rs = ps.executeQuery();
			while (rs.next()) {
				Sj s = new Sj();
				s.setSjbh(rs.getString(1));
				s.setSm(rs.getString(2));
				s.setCbsbh(rs.getString(3));
				s.setDj(rs.getFloat(4));
				s.setZz(rs.getString(5));
				s.setLbbh(rs.getString(6));
				s.setGcsl(rs.getInt(7));
				s.setKjsl(rs.getInt(8));
				s.setSfkj(rs.getString(9));
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
	public Sj getOne(String cph) {
		Sj s = new Sj();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from sj where sjbh="+cph);
			rs = ps.executeQuery();
			while (rs.next()) {
				s.setSjbh(rs.getString(1));
				s.setSm(rs.getString(2));
				s.setCbsbh(rs.getString(3));
				s.setDj(rs.getFloat(4));
				s.setZz(rs.getString(5));
				s.setLbbh(rs.getString(6));
				s.setGcsl(rs.getInt(7));
				s.setKjsl(rs.getInt(8));
				s.setSfkj(rs.getString(9));
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return s;
	}
	
}
