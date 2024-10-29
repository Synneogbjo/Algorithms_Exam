// Fill out your copyright notice in the Description page of Project Settings.


#include "F2DVectorInt.h"

F2DVectorInt::F2DVectorInt()
{
	X = 0;
	Y = 0;
}

F2DVectorInt::F2DVectorInt(const int SetX, const int SetY)
{
	X = SetX;
	Y = SetY;
}

F2DVectorInt::~F2DVectorInt()
{

}

F2DVectorInt F2DVectorInt::operator+(const F2DVectorInt& Other) const
{
	return F2DVectorInt(X + Other.X, Y + Other.Y);
}

bool F2DVectorInt::operator==(const F2DVectorInt& Other) const
{
	return (X == Other.X && Y == Other.Y);
}
