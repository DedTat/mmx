// Lab2.cpp: определяет точку входа для консольного приложения.
//проводятся операции суммирования векторов, взятия квадратного корня, сравнение элементов

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <cstdlib>

int main(void) {
	char qw1[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	char qw2[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
	int a = 1; int b = 2;
	float c[4] = {1.0, 2.0, 3.0, 4.0};
	float d[4] = { 5, 6, 7, 8 };
	double f[2] = { 4, 25 };
	char a128[16] = { 1, 18, 3, 19, 5, 21, 7, 23, 9, 25, 11,
		27, 13, 29, 15, 31 };
	char b128[16] = { 17, 2, 19, 4, 21, 6, 23, 8, 25, 10, 27,
		12, 29, 14, 31, 16 };
	int i = 0;
/*
	_asm { //mmx
		movq mm0, qw1                   //Переместить 64 бита
			movq mm1, qw2
			paddw mm0, mm1             // Непосредственное суммрование
			movq qw1, mm0
	}
	printf("%s\n", "Summing elements of vectors qw1 + qw2 :");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", qw1[i]);
	}
	printf("\n");
*/	
	_asm { //sse
		movups xmm0, c                 //SSE регистр xmm№ 128 бит,  AVX регистр ymm№  256 бит
			movups xmm1, d             // Пересылаем невыравненные упакованные числа из d в xmm1
			addps xmm0, xmm1
			movups c, xmm0
	}
	printf("%s\n", "Summing elements of vectors c + d :");
	for (int i = 0; i < 4; i++)
	{
		printf("%2.1f ", c[i]);
	}
	printf("\n");

	_asm { //sse2
		movups xmm1, f
			sqrtpd xmm0, xmm1
			movups f, xmm0
	}
	printf("\n%s %f %s %f\n", "Square of ", f[0], "is", f[1]);
	_asm {
		movups xmm0, a128
			movups xmm1, b128
			pminub xmm0, xmm1
			movups a128, xmm0
	}
	printf("\n%s\n", "Comparing elements :");
	for (int i = 0; i<16; i++)
	{
		printf("( %d , %d) ; ", a128[i], b128[i]);
	}
	printf("\n%s\n", "Minimum elements :");
	for (int i = 0; i<16; i++)
	{
		printf("%d ", a128[i]);
	}
	
	//_tsystem(0);
	
	system("pause");
	

}
