package com.entity;

public class Admin {

	/**
	 * 管理员类
	 */

	// 管理员登录名
	private String adminname;
	// 管理员密码
	private String password;
	// 管理员身份证
	private String asfz;
	// 管理员手机号
	private String atel;
	// 管理员职位
	private String azw;

	public Admin(String adminname, String password, String asfz, String atel, String azw) {
		super();
		this.adminname = adminname;
		this.password = password;
		this.asfz = asfz;
		this.atel = atel;
		this.azw = azw;
	}

	public String getAdminname() {
		return adminname;
	}

	public void setAdminname(String adminname) {
		this.adminname = adminname;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getAsfz() {
		return asfz;
	}

	public void setAsfz(String asfz) {
		this.asfz = asfz;
	}

	public String getAtel() {
		return atel;
	}

	public void setAtel(String atel) {
		this.atel = atel;
	}

	public String getAzw() {
		return azw;
	}

	public void setAzw(String azw) {
		this.azw = azw;
	}

	public Admin() {
	}

}
