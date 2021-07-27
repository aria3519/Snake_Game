#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
#include<conio.h>
#include<iomanip>
#include<list>
#include<time.h>
using namespace std;
#define MAXWALL 20
#define FOODTIME 5000
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define STOP 0
#define NULL 0
#define MAX_X 88
#define MAX_Y 24
#define READY 1
#define MAXFOOD 10

struct Point
{
	int x;
	int y;
};

enum STATE
{
	STATE_DEATH,
	STATE_KEEP,
	STATE_EATFOOD
};