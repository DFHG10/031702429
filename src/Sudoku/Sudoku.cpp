#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<stdio.h>
#pragma warning(disable:4996)
#include"stdafx.h"
using namespace std;
int board[10][10] = { 0 };//������ά����//
int num, x;//���������������//
int canshu(int argc)//�ж������в����Ƿ�����
{
	if (argc != 9)
	{
		cout << "������������";
		return 1;
	}
	if (x < 3 || x>9 || num < 0)
	{
		cout << "���ֳ���";
		return 1;
	}
	return 0;
}
bool Check(int check_number, int check_now_row, int check_now_column,
	int check_block_row, int check_block_column)//�Ϸ��Լ��
{
	for (int i = 0;i <= x;i++)//��������������ͬ�л�ͬ�е�λ�� 
	{
		if (board[check_now_row][i] == check_number || board[i][check_now_column] == check_number)
			return false;
	}
	if (x == 9)
	{
		check_block_row = (check_now_row / 3) * 3;
		check_block_column = (check_now_column / 3) * 3;
		for (int i = 0;i <= 2;i++)//��������������ͬ3*3�����λ�� 
		{
			for (int j = 0;j <= 2;j++)
			{
				if (board[check_block_row + i][check_block_column + j] == check_number)
					return false;
			}
		}
	}
	if (x == 4)
	{
		check_block_row = (check_now_row / 2) * 2;
		check_block_column = (check_now_column / 2) * 2;
		for (int i = 0;i <= 1;i++)//��������������ͬ2*2�����λ�� 
		{
			for (int j = 0;j <= 1;j++)
			{
				if (board[check_block_row + i][check_block_column + j] == check_number)
					return false;
			}
		}
	}
	if (x == 8)
	{
		check_block_row = (check_now_row / 4) * 4;
		check_block_column = (check_now_column / 2) * 2;
		for (int i = 0;i <= 3;i++)//��������������ͬ4*2�����λ�� 
		{
			for (int j = 0;j <= 1;j++)
			{
				if (board[check_block_row + i][check_block_column + j] == check_number)
					return false;
			}
		}
	}
	if (x == 6)
	{
		check_block_row = (check_now_row / 2) * 2;
		check_block_column = (check_now_column / 3) * 3;
		for (int i = 0;i <= 1;i++)//��������������ͬ2*3�����λ�� 
		{
			for (int j = 0;j <= 2;j++)
			{
				if (board[check_block_row + i][check_block_column + j] == check_number)
					return false;
			}
		}
	}
	return true;//ͨ�����м�飬����true 
}

bool Work(int now_row, int now_column)
{
	if (now_row == x)
	{
		return true;//������������꣬����true 
	}
	else
	{
		int next_row, next_column;
		int block_row = 0, block_column = 0;
		next_column = now_column + 1;
		next_row = (next_column >= x ? now_row + 1 : now_row);//������һ��,���� 
		next_column = (next_column >= x ? 0 : next_column);//������һ��,����Ϊ0 
		if (board[now_row][now_column] != 0)//�����ǰ���������֣������һ��������й��� 
		{
			if (Work(next_row, next_column)) return true;//������������н⣬�򲻶���ǰ����true 
		}
		else
		{
			for (int i = 1;i <= x;i++)
			{
				if (Check(i, now_row, now_column, block_row, block_column))
				{
					board[now_row][now_column] = i;//���iֵ�Ϸ��������һ��������й���
					if (Work(next_row, next_column)) return true;
				}
			}
			board[now_row][now_column] = 0;//���ݲ��� 
			return false;//���i��ֵΪ1-x�����Ϸ����򷵻���һ�����ѭ�� 
		}
		return  0;
	}
}
int main(int argc, char* argv[])
{
	FILE* fp1;
	FILE* fp2;
	x = atoi(argv[2]);
	num = atoi(argv[4]);
	canshu(argc);
	int i, j, k;
	fp1 = fopen("input.txt", "r");//ֻ�����ļ� 
	if (fp1 == NULL)//���ļ����� 
	{
		exit(0);
	}
	while (num > 0)
	{
		for (j = 0;j <= x - 1;j++)
		{
			for (k = 0;k <= x - 1;k++)
			{
				fscanf(fp1, "%d", &board[j][k]);
			}
		}
		Work(0, 0);
		fp2 = fopen("output.txt", "a");// 
		if (fp2 == NULL)//���ļ����� 
		{
			exit(0);
		}
		for (i = 0;i < x;i++)
		{
			for (j = 0;j < x;j++)
			{
				fprintf(fp2, "%d", board[i][j]);
				if (j != x - 1)
					fprintf(fp2, " ");
			}
			fprintf(fp2, "\n");
		}
		fprintf(fp2, "\n");
		num--;
		fclose(fp2);//�ر��ļ�����ֹ���ݶ�ʧ
		board[10][10] = { 0 };
	}
	fclose(fp1);
	return 0;
}