package com.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import com.entity.Cbs;
import com.util.DBhelper;

public class AdminDao {
	
	// µÇÂ¼·½·¨
	public boolean login(String a,String b) {
		boolean n = false;
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DBhelper.getCon();
			ps = con.prepareStatement("select * from admin where adminname=? and password=?");
			ps.setString(1, a);
			ps.setString(2, b);
			rs = ps.executeQuery();
			if(rs.next()) {
				n=true;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			DBhelper.myClose(con, ps, rs);
		}

		return n;
	}

}
