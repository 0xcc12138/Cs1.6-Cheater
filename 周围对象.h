#pragma once
#define Π 3.1415927
#include <windows.h>
struct 朝向结构
{
	float 水平朝向;
	float 垂直朝向;
};


struct 对象结构
{
	float 对象重心的x坐标;
	float 对象重心的y坐标;
	float 对象重心的z坐标;


	float 对象脚的x坐标;
	float 对象脚的y坐标;
	float 对象脚的z坐标;

	float 对象头的x坐标;
	float 对象头的y坐标;
	float 对象头的z坐标;

	int 血量;

	unsigned int 死亡标志;
	unsigned int 阵营标志;


	朝向结构 对象的重心朝向;
	朝向结构 对象脚的朝向;
	朝向结构 对象头的朝向;

	朝向结构 对象重心的角度差;
	朝向结构 对象脚的角度差;
	朝向结构 对象头的角度差;
};


struct 玩家自身坐标和朝向
{
	float 玩家的x坐标;
	float 玩家的y坐标;
	float 玩家的z坐标;
	朝向结构 玩家的朝向结构;
};


class 周围对象
{
public:
	玩家自身坐标和朝向 自身坐标和朝向;
	对象结构* 对象列表[32];
	unsigned int 对象数量;
	unsigned int mp_dll基地址;
	unsigned int cstrike基地址;
public:
	void 刷新周围数据();
	周围对象()
	{
		for (int i = 0; i < 32; i++)
		{
			对象列表[i] = new 对象结构;
		}
		mp_dll基地址 = (unsigned int)GetModuleHandleA("mp.dll");
		cstrike基地址 = (unsigned int)GetModuleHandleA("cstrike.exe");
	}

private:
	void 计算朝向(对象结构& 对象);

	void 获取自身坐标和朝向();
};