#pragma once
#define �� 3.1415927
#include <windows.h>
struct ����ṹ
{
	float ˮƽ����;
	float ��ֱ����;
};


struct ����ṹ
{
	float �������ĵ�x����;
	float �������ĵ�y����;
	float �������ĵ�z����;


	float ����ŵ�x����;
	float ����ŵ�y����;
	float ����ŵ�z����;

	float ����ͷ��x����;
	float ����ͷ��y����;
	float ����ͷ��z����;

	int Ѫ��;

	unsigned int ������־;
	unsigned int ��Ӫ��־;


	����ṹ ��������ĳ���;
	����ṹ ����ŵĳ���;
	����ṹ ����ͷ�ĳ���;

	����ṹ �������ĵĽǶȲ�;
	����ṹ ����ŵĽǶȲ�;
	����ṹ ����ͷ�ĽǶȲ�;
};


struct �����������ͳ���
{
	float ��ҵ�x����;
	float ��ҵ�y����;
	float ��ҵ�z����;
	����ṹ ��ҵĳ���ṹ;
};


class ��Χ����
{
public:
	�����������ͳ��� ��������ͳ���;
	����ṹ* �����б�[32];
	unsigned int ��������;
	unsigned int mp_dll����ַ;
	unsigned int cstrike����ַ;
public:
	void ˢ����Χ����();
	��Χ����()
	{
		for (int i = 0; i < 32; i++)
		{
			�����б�[i] = new ����ṹ;
		}
		mp_dll����ַ = (unsigned int)GetModuleHandleA("mp.dll");
		cstrike����ַ = (unsigned int)GetModuleHandleA("cstrike.exe");
	}

private:
	void ���㳯��(����ṹ& ����);

	void ��ȡ��������ͳ���();
};