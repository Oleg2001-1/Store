#include "GoodsTypes.h"

std::string GoodsSpace::GoodsTypesStr[] = { "Appliances", "BuildingMaterials", "Clothes", "Devices", "Food" };
std::vector<TCHAR*> GoodsSpace::GoodsTypesTCHAR;

void GoodsSpace::init() {
    //Converting GoodsTypesStr strings to TCHAR strings and storing in GoodsTypesTCHAR
    GoodsSpace::GoodsTypesTCHAR.resize(GoodsSpace::GoodsTypes::Size);
    for (int i = 0; i < GoodsSpace::GoodsTypes::Size; i++) {
        int len = GoodsSpace::GoodsTypesStr[i].size();
        GoodsSpace::GoodsTypesTCHAR[i] = new TCHAR[len];

        const char* orig = GoodsSpace::GoodsTypesStr[i].c_str();
        size_t converted_chars = 0;
        size_t new_size = strlen(orig) + 1;
        mbstowcs_s(&converted_chars, GoodsSpace::GoodsTypesTCHAR[i], new_size, orig, _TRUNCATE);
    }
}