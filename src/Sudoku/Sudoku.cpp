#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<stdio.h>
#pragma warning(disable:4996)
#include"stdafx.h"
using namespace std;
int board[10][10] = { 0 };//数独二维数组//
int num, x;//定义阶数和盘面数//
int canshu(int argc)//判断命令行参数是否有误
{
	if (argc != 9)
	{
		cout << "参数个数出错！";
		return 1;
	}
	if (x < 3 || x>9 || num < 0)
	{
		cout << "数字出错！";
		return 1;
	}
	return 0;
}
bool Check(int check_number, int check_now_row, int check_now_column,
	int check_block_row, int check_block_column)//合法性检测
{
	for (int i = 0;i <= x;i++)//检查与待检查的坐标同行或同列的位置 
	{
		if (board[check_now_row][i] == check_number || board[i][check_now_column] == check_number)
			return false;
	}
	if (x == 9)
	{
		check_block_row = (check_now_row / 3) * 3;
		check_block_column = (check_now_column / 3) * 3;
		for (int i = 0;i <= 2;i++)//检查与待检查的坐标同3*3方格的位置 
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
		for (int i = 0;i <= 1;i++)//检查与待检查的坐标同2*2方格的位置 
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
		for (int i = 0;i <= 3;i++)//检查与待检查的坐标同4*2方格的位置 
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
		for (int i = 0;i <= 1;i++)//检查与待检查的坐标同2*3方格的位置 
		{
			for (int j = 0;j <= 2;j++)
			{
				if (board[check_block_row + i][check_block_column + j] == check_number)
					return false;
			}
		}
	}
	return true;//通过所有检查，返回true 
}

bool Work(int now_row, int now_column)
{
	if (now_row == x)
	{
		return true;//如果将数独解完，返回true 
	}
	else
	{
		int next_row, next_column;
		int block_row = 0, block_column = 0;
		next_column = now_column + 1;
		next_row = (next_column >= x ? now_row + 1 : now_row);//如果最后一列,换行 
		next_column = (next_column >= x ? 0 : next_column);//如果最后一行,列置为0 
		if (board[now_row][now_column] != 0)//如果当前坐标有数字，则对下一个坐标进行工作 
		{
			if (Work(next_row, next_column)) return true;//如果数独最终有解，则不断向前返回true 
		}
		else
		{
			for (int i = 1;i <= x;i++)
			{
				if (Check(i, now_row, now_column, block_row, block_column))
				{
					board[now_row][now_column] = i;//如果i值合法，则对下一个坐标进行工作
					if (Work(next_row, next_column)) return true;
				}
			}
			board[now_row][now_column] = 0;//回溯操作 
			return false;//如果i的值为1-x均不合法，则返回上一层继续循环 
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
	fp1 = fopen("input.txt", "r");//只读打开文件 
	if (fp1 == NULL)//打开文件出错 
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
		if (fp2 == NULL)//打开文件出错 
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
		fclose(fp2);//关闭文件，防止数据丢失
		board[10][10] = { 0 };
	}
	fclose(fp1);
	return 0;
}