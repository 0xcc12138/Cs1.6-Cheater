#include "����.h"
#include <cmath>    // ���� tan ����
void ����::��ȡ������Ϣ()
{
	if (!GetClientRect(this->Ŀ�괰�ھ��, &this->�ڴ���))//��ȡ�����ڲ����ڵ���Ϣ,�������Ի�ȡ���ϣ����µ����꣬�ֱ��ʾ��ǿ�͸�ռ������
	{
		DWORD Error = GetLastError();
		MessageBox(0, L"����", L"��ȡ�ڴ�������ʧ��", 0);
	}
	this->�ֱ���_�� = this->�ڴ���.right - this->�ڴ���.left;
	this->�ֱ���_�� = this->�ڴ���.bottom - this->�ڴ���.top;//ע��������bottom��ȥtop

	if (!GetWindowRect(this->Ŀ�괰�ھ��, &this->�ⴰ��))
	{
		MessageBox(0, L"����", L"��ȡ�ⴰ������ʧ��", 0);
	}

	this->�ⴰ�ڿ� = this->�ⴰ��.right - this->�ⴰ��.left;
	this->�ⴰ�ڸ� = this->�ⴰ��.bottom - this->�ⴰ��.top;//ע��������bottom��ȥtop
}


void ����::���ƾ��ο�(RECT ����)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(this->Ŀ�괰�ھ��, &ps);

	 // ����һ����ɫ�Ļ���
	HPEN hPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
	HGDIOBJ oldPen = SelectObject(hdc, hPen);

	// ����һ���հ׵Ļ�ˢ
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HGDIOBJ oldBrush = SelectObject(hdc, hBrush);

	// ���ƾ��α߿�
	Rectangle(hdc, ����.left, ����.top, ����.right, ����.bottom);

	// �ָ�ԭ���Ļ��ʺͻ�ˢ
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);

	// ����
	DeleteObject(hPen);
	EndPaint(this->Ŀ�괰�ھ��, &ps);
}



void ����::����(int x,int y,DWORD ��Ӫ) //Ĭ�ϴӿͻ������������м俪ʼ����
{
	��ȡ������Ϣ();
	HPEN hPen;
	// ����һ����ɫ�Ļ��� ����
	if (��Ӫ == 0)
	{
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		
	}
	else//����
	{
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	}
	HGDIOBJ oldPen = SelectObject(hdc, hPen);
	//����
	MoveToEx(hdc, this->�ֱ���_�� / 2, this->�ֱ���_��*3/4, NULL);
	// ����ʼλ�û��Ƶ� (200, 200)
	LineTo(hdc, x, y);

}


void ����::�����ַ���(int x,int y)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(this->Ŀ�괰�ھ��, &ps);

	// Ҫ���Ƶ��ַ���
	TCHAR* text = (TCHAR*)L"Hello, Win32 API!";

	// �� (50, 50) λ�û����ַ���
	TextOut(hdc, x, y, text, lstrlen(text));

	EndPaint(this->Ŀ�괰�ھ��, &ps);
}



bool ����::��������תΪ��Ļ����_�Ǿ���(����ṹ Ŀ�����ṹ, ��Ļ����ṹ& Ŀ����Ļ����ṹ)
{
	
    FLOAT �ߵͿ��ӽǶ� = (FLOAT)(atan2(�ֱ���_��, �ֱ���_��) * 180 / ��);
    
    
    
    if (fabs(Ŀ�����ṹ.�������ĵĽǶȲ�.ˮƽ����) > 45 || fabs(Ŀ�����ṹ.�������ĵĽǶȲ�.��ֱ����) > �ߵͿ��ӽǶ�)
    {
		Ŀ����Ļ����ṹ.x���� = (float)(this->�ֱ���_�� / 2);
		Ŀ����Ļ����ṹ.y���� = (float)(this->�ֱ���_�� * 3 / 4);
    	return false;//������Ļ��Χ��
    }
    int ˮƽ�� = (int)(tan(Ŀ�����ṹ.�������ĵĽǶȲ�.ˮƽ���� * �� / 180) * (�ֱ���_�� / 2));
    Ŀ����Ļ����ṹ.x���� = (float)(�ֱ���_�� / 2 + ˮƽ��);
    
    int �߶Ȳ� = (int)(tan(Ŀ�����ṹ.�������ĵĽǶȲ�.��ֱ���� * �� / 180) * (�ֱ���_��) / 2);
    Ŀ����Ļ����ṹ.y���� = (float)(�ֱ���_�� / 2 + �߶Ȳ�);
	return true;
	
}

bool ����::��������תΪ��Ļ����_����(����ṹ Ŀ�����ṹ, ��Ļ����ṹ& Ŀ����Ļ����ṹ)
{
	for (int i = 0; i < 16; i++)
	{
		����[i] = *(float*)(�����ַ + 4 * i);
	}
	DWORD w = 1;
	float ��������x = this->����[0] * Ŀ�����ṹ.�������ĵ�x���� + this->����[4] * Ŀ�����ṹ.�������ĵ�y���� + this->����[8] * Ŀ�����ṹ.�������ĵ�z���� + this->����[12] * w;
	float ��������y = this->����[1] * Ŀ�����ṹ.�������ĵ�x���� + this->����[5] * Ŀ�����ṹ.�������ĵ�y���� + this->����[9] * Ŀ�����ṹ.�������ĵ�z���� + this->����[13] * w;
	float ��������z = this->����[2] * Ŀ�����ṹ.�������ĵ�x���� + this->����[6] * Ŀ�����ṹ.�������ĵ�y���� + this->����[10] * Ŀ�����ṹ.�������ĵ�z���� + this->����[14] * w;
	float ��������w = this->����[3] * Ŀ�����ṹ.�������ĵ�x���� + this->����[7] * Ŀ�����ṹ.�������ĵ�y���� + this->����[11] * Ŀ�����ṹ.�������ĵ�z���� + this->����[15] * w;

	if (��������w < 0.0f)
	{
		Ŀ����Ļ����ṹ.x���� = �ֱ���_�� / 2;
		Ŀ����Ļ����ṹ.y���� = �ֱ���_�� * 3 / 4;
		return false;
	}


	float NDC_x = ��������x / ��������w;
	float NDC_y = ��������y / ��������w;

	Ŀ����Ļ����ṹ.x���� = (�ֱ���_�� / 2) * NDC_x + �ֱ���_�� / 2;
	Ŀ����Ļ����ṹ.y���� =  0-(�ֱ���_�� / 2) * NDC_y + �ֱ���_�� / 2;
	return true;
}



void ����::����()
{
	if (GetKeyState(VK_F4))
	{
		//�����ĸ��������Լ����
		int �����������±� = -1;
		float ������� = 0xFFFFFFFF;
		for (int i = 0; i < this->Ŀ����Χ����.��������-1; i++)
		{
			float ���� = sqrt(pow((this->Ŀ����Χ����.��������ͳ���.��ҵ�x���� - this->Ŀ����Χ����.�����б�[i]->�������ĵ�x����), 2) + pow((this->Ŀ����Χ����.��������ͳ���.��ҵ�y���� - this->Ŀ����Χ����.�����б�[i]->�������ĵ�y����), 2) + pow((this->Ŀ����Χ����.��������ͳ���.��ҵ�z���� - this->Ŀ����Χ����.�����б�[i]->�������ĵ�z����), 2));
			if (���� < �������&& this->Ŀ����Χ����.�����б�[i]->������־==0 && this->Ŀ����Χ����.�����б�[i]->��Ӫ��־!=0)
			{
				�����������±� = i;
			}
		}

//		��ֱ����cstrike.exe + 0x19E10C4   ˮƽ����:cstrike.exe + 0x19E10C8
		if (�����������±� != 1)
		{
			*(float*)(this->Ŀ����Χ����.cstrike����ַ + 0x19E10C4) = this->Ŀ����Χ����.�����б�[�����������±�]->��������ĳ���.��ֱ����;
			*(float*)(this->Ŀ����Χ����.cstrike����ַ + 0x19E10C8) = this->Ŀ����Χ����.�����б�[�����������±�]->��������ĳ���.ˮƽ����;
		}
	}
	else
		return;
}