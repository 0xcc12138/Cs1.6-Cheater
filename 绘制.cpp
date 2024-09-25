#include "绘制.h"
#include <cmath>    // 包含 tan 函数
void 绘制::获取窗口信息()
{
	if (!GetClientRect(this->目标窗口句柄, &this->内窗口))//获取的是内部窗口的信息,这样可以获取左上，右下的坐标，分辨率就是宽和高占的像素
	{
		DWORD Error = GetLastError();
		MessageBox(0, L"错误", L"获取内窗口属性失败", 0);
	}
	this->分辨率_宽 = this->内窗口.right - this->内窗口.left;
	this->分辨率_高 = this->内窗口.bottom - this->内窗口.top;//注意这里是bottom减去top

	if (!GetWindowRect(this->目标窗口句柄, &this->外窗口))
	{
		MessageBox(0, L"错误", L"获取外窗口属性失败", 0);
	}

	this->外窗口宽 = this->外窗口.right - this->外窗口.left;
	this->外窗口高 = this->外窗口.bottom - this->外窗口.top;//注意这里是bottom减去top
}


void 绘制::绘制矩形框(RECT 矩形)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(this->目标窗口句柄, &ps);

	 // 创建一个绿色的画笔
	HPEN hPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
	HGDIOBJ oldPen = SelectObject(hdc, hPen);

	// 创建一个空白的画刷
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HGDIOBJ oldBrush = SelectObject(hdc, hBrush);

	// 绘制矩形边框
	Rectangle(hdc, 矩形.left, 矩形.top, 矩形.right, 矩形.bottom);

	// 恢复原来的画笔和画刷
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);

	// 清理
	DeleteObject(hPen);
	EndPaint(this->目标窗口句柄, &ps);
}



void 绘制::画线(int x,int y,DWORD 阵营) //默认从客户区的最下面中间开始连线
{
	获取窗口信息();
	HPEN hPen;
	// 创建一个绿色的画笔 队友
	if (阵营 == 0)
	{
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		
	}
	else//敌人
	{
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	}
	HGDIOBJ oldPen = SelectObject(hdc, hPen);
	//连线
	MoveToEx(hdc, this->分辨率_宽 / 2, this->分辨率_高*3/4, NULL);
	// 从起始位置绘制到 (200, 200)
	LineTo(hdc, x, y);

}


void 绘制::绘制字符串(int x,int y)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(this->目标窗口句柄, &ps);

	// 要绘制的字符串
	TCHAR* text = (TCHAR*)L"Hello, Win32 API!";

	// 在 (50, 50) 位置绘制字符串
	TextOut(hdc, x, y, text, lstrlen(text));

	EndPaint(this->目标窗口句柄, &ps);
}



bool 绘制::世界坐标转为屏幕坐标_非矩阵(对象结构 目标对象结构, 屏幕坐标结构& 目标屏幕坐标结构)
{
	
    FLOAT 高低可视角度 = (FLOAT)(atan2(分辨率_高, 分辨率_宽) * 180 / Π);
    
    
    
    if (fabs(目标对象结构.对象重心的角度差.水平朝向) > 45 || fabs(目标对象结构.对象重心的角度差.垂直朝向) > 高低可视角度)
    {
		目标屏幕坐标结构.x坐标 = (float)(this->分辨率_宽 / 2);
		目标屏幕坐标结构.y坐标 = (float)(this->分辨率_高 * 3 / 4);
    	return false;//不在屏幕范围内
    }
    int 水平差 = (int)(tan(目标对象结构.对象重心的角度差.水平朝向 * Π / 180) * (分辨率_宽 / 2));
    目标屏幕坐标结构.x坐标 = (float)(分辨率_宽 / 2 + 水平差);
    
    int 高度差 = (int)(tan(目标对象结构.对象重心的角度差.垂直朝向 * Π / 180) * (分辨率_宽) / 2);
    目标屏幕坐标结构.y坐标 = (float)(分辨率_高 / 2 + 高度差);
	return true;
	
}

bool 绘制::世界坐标转为屏幕坐标_矩阵(对象结构 目标对象结构, 屏幕坐标结构& 目标屏幕坐标结构)
{
	for (int i = 0; i < 16; i++)
	{
		矩阵[i] = *(float*)(矩阵地址 + 4 * i);
	}
	DWORD w = 1;
	float 剪辑坐标x = this->矩阵[0] * 目标对象结构.对象重心的x坐标 + this->矩阵[4] * 目标对象结构.对象重心的y坐标 + this->矩阵[8] * 目标对象结构.对象重心的z坐标 + this->矩阵[12] * w;
	float 剪辑坐标y = this->矩阵[1] * 目标对象结构.对象重心的x坐标 + this->矩阵[5] * 目标对象结构.对象重心的y坐标 + this->矩阵[9] * 目标对象结构.对象重心的z坐标 + this->矩阵[13] * w;
	float 剪辑坐标z = this->矩阵[2] * 目标对象结构.对象重心的x坐标 + this->矩阵[6] * 目标对象结构.对象重心的y坐标 + this->矩阵[10] * 目标对象结构.对象重心的z坐标 + this->矩阵[14] * w;
	float 剪辑坐标w = this->矩阵[3] * 目标对象结构.对象重心的x坐标 + this->矩阵[7] * 目标对象结构.对象重心的y坐标 + this->矩阵[11] * 目标对象结构.对象重心的z坐标 + this->矩阵[15] * w;

	if (剪辑坐标w < 0.0f)
	{
		目标屏幕坐标结构.x坐标 = 分辨率_宽 / 2;
		目标屏幕坐标结构.y坐标 = 分辨率_高 * 3 / 4;
		return false;
	}


	float NDC_x = 剪辑坐标x / 剪辑坐标w;
	float NDC_y = 剪辑坐标y / 剪辑坐标w;

	目标屏幕坐标结构.x坐标 = (分辨率_宽 / 2) * NDC_x + 分辨率_宽 / 2;
	目标屏幕坐标结构.y坐标 =  0-(分辨率_高 / 2) * NDC_y + 分辨率_高 / 2;
	return true;
}



void 绘制::自瞄()
{
	if (GetKeyState(VK_F4))
	{
		//计算哪个对象离自己最近
		int 最近距离对象下标 = -1;
		float 最近距离 = 0xFFFFFFFF;
		for (int i = 0; i < this->目标周围对象.对象数量-1; i++)
		{
			float 距离 = sqrt(pow((this->目标周围对象.自身坐标和朝向.玩家的x坐标 - this->目标周围对象.对象列表[i]->对象重心的x坐标), 2) + pow((this->目标周围对象.自身坐标和朝向.玩家的y坐标 - this->目标周围对象.对象列表[i]->对象重心的y坐标), 2) + pow((this->目标周围对象.自身坐标和朝向.玩家的z坐标 - this->目标周围对象.对象列表[i]->对象重心的z坐标), 2));
			if (距离 < 最近距离&& this->目标周围对象.对象列表[i]->死亡标志==0 && this->目标周围对象.对象列表[i]->阵营标志!=0)
			{
				最近距离对象下标 = i;
			}
		}

//		垂直朝向cstrike.exe + 0x19E10C4   水平朝向:cstrike.exe + 0x19E10C8
		if (最近距离对象下标 != 1)
		{
			*(float*)(this->目标周围对象.cstrike基地址 + 0x19E10C4) = this->目标周围对象.对象列表[最近距离对象下标]->对象的重心朝向.垂直朝向;
			*(float*)(this->目标周围对象.cstrike基地址 + 0x19E10C8) = this->目标周围对象.对象列表[最近距离对象下标]->对象的重心朝向.水平朝向;
		}
	}
	else
		return;
}