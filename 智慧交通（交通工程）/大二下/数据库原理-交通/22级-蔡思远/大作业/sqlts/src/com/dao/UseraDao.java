package com.dao;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JOptionPane;

import com.entity.Usera;
import com.util.DBhelper;

public class UseraDao {

	// 删除方法
	public int delete(String userah) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("delete from usera where ubh=" + userah);
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 增加方法
	public int add(Usera a) {
		int n = 0;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("insert into usera(ubh,xm,xb,dh,jtdz,upwd) "
					+ "values(?,?,?,?,?,?)");
			ps.setString(1, a.getUbh());
			ps.setString(2, a.getXm());
			ps.setString(3, a.getXb());
			ps.setString(4, a.getDh());
			ps.setString(5, a.getJtdz());
			ps.setString(6, a.getUpwd());
			n = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

	// 查询
	public List<Usera> getAll(String str) {
		List<Usera> ss = new ArrayList<Usera>();
		ResultSet rs = null;
		PreparedStatement ps = null;
		Connection con = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from usera where xm like '%"+str+"%'");
			rs = ps.executeQuery();
			while (rs.next()) {
				Usera s = new Usera();
				s.setUbh(rs.getString(1));
				s.setXm(rs.getString(2));
				s.setXb(rs.getString(3));
				s.setDh(rs.getString(4));
				s.setJtdz(rs.getString(5));
				ss.add(s);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}
		return ss;
	}
	
	// 登录方法
	public String login(String a,String b) {
		String n = null;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select ubh from usera where xm=? and upwd=?");
			ps.setString(1, a);
			ps.setString(2, b);
			rs = ps.executeQuery();
			if(rs.next()) {
				n=rs.getString(1);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}
	
}
