#pragma once
#include "pch.h"
#include <iostream>
#include "����.h"
#include "��Χ����.h"
struct ��Ļ����ṹ
{
	float x����;
	float y����;
};


class ����
{
public:
	HWND Ŀ�괰�ھ��;  //�������ĸ������ϻ���
	RECT �ڴ���; //һ��ָ��ʾ��Ϸ���� 
	RECT �ⴰ��; //�������ڴ���������һ���ⴰ�ڣ�����˵�ɶ��
	unsigned int �ֱ���_��;
	unsigned int �ֱ���_��;
	int �ⴰ�ڿ�;
	int �ⴰ�ڸ�;
	float ����[16];
	DWORD �����ַ;
	HDC hdc;
	struct ��Ļ����ṹ Ŀ����Ļ����ṹ[32] = { 0 };
	��Χ���� Ŀ����Χ����;


public:
	����(HWND ���ھ��, DWORD �����ַ)
	{
		this->Ŀ�괰�ھ�� = ���ھ��;
		this->�����ַ = �����ַ;
		this->hdc = GetDC(this->Ŀ�괰�ھ��);
		��ȡ������Ϣ();
	}
	����(HWND ���ھ��)
	{
		Ŀ�괰�ھ�� = ���ھ��;
		this->hdc = GetDC(this->Ŀ�괰�ھ��);
		��ȡ������Ϣ();
	}




public:
	bool ��������תΪ��Ļ����_�Ǿ���(����ṹ Ŀ�����ṹ,  ��Ļ����ṹ& Ŀ����Ļ����ṹ);
	bool ��������תΪ��Ļ����_����(����ṹ Ŀ�����ṹ, ��Ļ����ṹ& Ŀ����Ļ����ṹ);
	void ����(int x, int y,DWORD ��Ӫ);
	void ���ƾ��ο�(RECT ����);
	void �����ַ���(int x, int y);
	void ����();


private:
	void ��ȡ������Ϣ();

};