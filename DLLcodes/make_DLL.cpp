// dlltry3.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Windows.h"
#include "extcode.h"
#include "dlltr3.h"

DLLIMPORT int32_t add(double in1, double in2, double *out)
{

	*out = in1 + in2;
	return 0;
}
