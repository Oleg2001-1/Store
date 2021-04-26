#pragma once
#include <string>
#include <tchar.h>
#include <vector>

namespace GoodsSpace {
	const int GOODS_PARAMETERS = 4;
	const int PARAMETER_LENGTH = 30; //Max lenght of any parameter of any good
	enum GoodsTypes {
		Appliances, BuildingMaterials, Clothes, Devices, Food, Size
	};

	extern std::string GoodsTypesStr[GoodsTypes::Size]; //extern is needed to avoid compilation error
	extern std::vector<TCHAR*> GoodsTypesTCHAR; //GoodsTypes strings converted to TCHAR strings
	void init(); //function, that prepares GoodsTypesStr and GoodsTypesTCHAR
}
