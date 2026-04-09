package com.ui;

import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

/**
 * 自定义画板
 * @author Miss.Yan
 *
 */
public class MyJpanel extends JPanel{
	
	private String imgPath; //图片路径
	private int width;
	private int height;
	
	public MyJpanel(String imgPath, int width, int height) {
		this.imgPath = imgPath;
		this.width = width;
		this.height = height;
	}

	@Override
	protected void paintComponent(Graphics g) {
		// TODO Auto-generated method stub
		g.drawImage(new ImageIcon(imgPath).getImage(), 0, 0, width, height, null);
	}

}
