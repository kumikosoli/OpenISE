package com.entity;

import java.util.Date;

public class Jyxx {

	private String jybh;
	private String sjbh;
	private String ubh;
	private Date jysj;
	private int jyts;
	private Date ghsj;

	


	


	public Jyxx(String jybh, String sjbh, String ubh, Date jysj, int jyts, Date ghsj) {
		super();
		this.jybh = jybh;
		this.sjbh = sjbh;
		this.ubh = ubh;
		this.jysj = jysj;
		this.jyts = jyts;
		this.ghsj = ghsj;
	}







	public String getJybh() {
		return jybh;
	}







	public void setJybh(String jybh) {
		this.jybh = jybh;
	}







	public String getSjbh() {
		return sjbh;
	}







	public void setSjbh(String sjbh) {
		this.sjbh = sjbh;
	}







	public String getUbh() {
		return ubh;
	}







	public void setUbh(String ubh) {
		this.ubh = ubh;
	}







	public Date getJysj() {
		return jysj;
	}







	public void setJysj(Date jysj) {
		this.jysj = jysj;
	}







	public int getJyts() {
		return jyts;
	}







	public void setJyts(int jyts) {
		this.jyts = jyts;
	}







	public Date getGhsj() {
		return ghsj;
	}







	public void setGhsj(Date ghsj) {
		this.ghsj = ghsj;
	}







	public Jyxx() {
	}

}
