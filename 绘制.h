#pragma once
#include "pch.h"
#include <iostream>
#include "绘制.h"
#include "周围对象.h"
struct 屏幕坐标结构
{
	float x坐标;
	float y坐标;
};


class 绘制
{
public:
	HWND 目标窗口句柄;  //锁定在哪个窗口上画框
	RECT 内窗口; //一般指显示游戏界面 
	RECT 外窗口; //可能在内窗口外面有一个外窗口，例如菜单啥的
	unsigned int 分辨率_宽;
	unsigned int 分辨率_高;
	int 外窗口宽;
	int 外窗口高;
	float 矩阵[16];
	DWORD 矩阵地址;
	HDC hdc;
	struct 屏幕坐标结构 目标屏幕坐标结构[32] = { 0 };
	周围对象 目标周围对象;


public:
	绘制(HWND 窗口句柄, DWORD 矩阵地址)
	{
		this->目标窗口句柄 = 窗口句柄;
		this->矩阵地址 = 矩阵地址;
		this->hdc = GetDC(this->目标窗口句柄);
		获取窗口信息();
	}
	绘制(HWND 窗口句柄)
	{
		目标窗口句柄 = 窗口句柄;
		this->hdc = GetDC(this->目标窗口句柄);
		获取窗口信息();
	}




public:
	bool 世界坐标转为屏幕坐标_非矩阵(对象结构 目标对象结构,  屏幕坐标结构& 目标屏幕坐标结构);
	bool 世界坐标转为屏幕坐标_矩阵(对象结构 目标对象结构, 屏幕坐标结构& 目标屏幕坐标结构);
	void 画线(int x, int y,DWORD 阵营);
	void 绘制矩形框(RECT 矩形);
	void 绘制字符串(int x, int y);
	void 自瞄();


private:
	void 获取窗口信息();

};