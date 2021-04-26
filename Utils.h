#pragma once
#include "GoodsTypes.h"
#include "Record.h"
#include <wchar.h>
#include <vector>
#include <tchar.h>

//Just declaring some useful functions
namespace Utils {
	int TCHARtoTYPE(TCHAR* type);
	TCHAR*** VECTORtoTCHAR(vector<Record> records);
}