#include "Utils.h"

int Utils::TCHARtoTYPE(TCHAR* type) {
    for (int i = 0; i < GoodsSpace::GoodsTypes::Size; i++) {
        if (!wcscmp(type, GoodsSpace::GoodsTypesTCHAR[i])) {
            return GoodsSpace::GoodsTypes(i);
        }
    }
    return 0;
}

TCHAR*** Utils::VECTORtoTCHAR(vector<Record> records) {
    int size = records.size();
    TCHAR*** result = new TCHAR**[size];
    for (int i = 0; i < size; i++) {
        result[i] = new TCHAR * [4];

        TCHAR* indexTCHAR = new TCHAR[10];
        _itow_s(records[i].index, indexTCHAR, 10, 10);
        int len = std::wcslen(indexTCHAR) + 1;
        result[i][0] = new TCHAR[len];
        wcscpy_s(result[i][0], len, indexTCHAR);
        result[i][1] = new TCHAR[records[i].name.size()];
        const char* orig = records[i].name.c_str();
        size_t converted_chars = 0;
        size_t new_size = strlen(orig) + 1;
        mbstowcs_s(&converted_chars, result[i][1], new_size, orig, _TRUNCATE);

        const TCHAR* typeTCHAR = new TCHAR[20];
        typeTCHAR = GoodsSpace::GoodsTypesTCHAR[records[i].type];
        len = std::wcslen(typeTCHAR) + 1;
        result[i][2] = new TCHAR[len];
        wcscpy_s(result[i][2], len + 1, typeTCHAR);

        TCHAR* countTCHAR = new TCHAR[10];
        _itow_s(records[i].count, countTCHAR, 10, 10);
        len = std::wcslen(countTCHAR) + 1;
        result[i][3] = new TCHAR[len];
        wcscpy_s(result[i][3], len, countTCHAR);
    }
    return result;
}