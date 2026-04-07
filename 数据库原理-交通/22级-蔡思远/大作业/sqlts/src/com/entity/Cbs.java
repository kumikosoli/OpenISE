package com.entity;

import java.sql.Date;

public class Cbs {

	private String cbsbh;
	private String mz;
	private String fzr;
	private String lxdh;
	private String jtwz;

	

	public Cbs(String cbsbh, String mz, String fzr, String lxdh, String jtwz) {
		super();
		this.cbsbh = cbsbh;
		this.mz = mz;
		this.fzr = fzr;
		this.lxdh = lxdh;
		this.jtwz = jtwz;
	}



	public String getCbsbh() {
		return cbsbh;
	}



	public void setCbsbh(String cbsbh) {
		this.cbsbh = cbsbh;
	}



	public String getMz() {
		return mz;
	}



	public void setMz(String mz) {
		this.mz = mz;
	}



	public String getFzr() {
		return fzr;
	}



	public void setFzr(String fzr) {
		this.fzr = fzr;
	}



	public String getLxdh() {
		return lxdh;
	}



	public void setLxdh(String lxdh) {
		this.lxdh = lxdh;
	}



	public String getJtwz() {
		return jtwz;
	}



	public void setJtwz(String jtwz) {
		this.jtwz = jtwz;
	}



	public Cbs() {
	}
}
