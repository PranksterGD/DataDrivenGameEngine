#include "pch.h"
using namespace FieaGameEngine;
using namespace std;

uint32_t IncrementFunctor::operator()(uint32_t Size, uint32_t Capacity)
{
	UNREFERENCED_PARAMETER(Size);
	return Capacity + 1;
}