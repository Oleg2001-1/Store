//Project.cpp : Defines application entry point
//

#include "framework.h"
#include "Project.h"

#define MAX_LOADSTRING 100

// Global variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];
Warehouse warehouse;                            // creation of warehouse object

 
//Window handlers declaration
INT_PTR CALLBACK    MainDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    WarehouseDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DeleteDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    OrderDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    OrderStateDlg(HWND, UINT, WPARAM, LPARAM);

void                UpdateListBox(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //Initial Actions
    {
        GoodsSpace::init();
        OrdersSpace::init();

        //Primary warehouse filling
        {
            const char* orig = "Meet";

            //normal char to TCHAR string
            TCHAR* name1 = new TCHAR[strlen(orig)];
            size_t converted_chars = 0;
            size_t new_size1 = strlen(orig) + 1;
            mbstowcs_s(&converted_chars, name1, new_size1, orig, _TRUNCATE);
            warehouse.addRecord(Record(5505, name1, GoodsSpace::GoodsTypes::Food, 50));

            const char* orig2 = "Wood";

            TCHAR* name2 = new TCHAR[strlen(orig2)];
            size_t new_size2 = strlen(orig2) + 1;
            mbstowcs_s(&converted_chars, name2, new_size2, orig2, _TRUNCATE);
            warehouse.addRecord(Record(5502, name2, GoodsSpace::GoodsTypes::BuildingMaterials, 100));

            const char* orig3 = "Fridge";

            TCHAR* name3 = new TCHAR[strlen(orig3)];
            size_t new_size3 = strlen(orig3) + 1;
            mbstowcs_s(&converted_chars, name3, new_size3, orig3, _TRUNCATE);
            warehouse.addRecord(Record(5501, name3, GoodsSpace::GoodsTypes::Appliances, 30));

            const char* orig4 = "T-Shirt";

            TCHAR* name4 = new TCHAR[strlen(orig4)];
            size_t new_size4 = strlen(orig4) + 1;
            mbstowcs_s(&converted_chars, name4, new_size4, orig4, _TRUNCATE);
            warehouse.addRecord(Record(5503, name4, GoodsSpace::GoodsTypes::Clothes, 130));

            const char* orig5 = "Headphones";

            TCHAR* name5 = new TCHAR[strlen(orig5)];
            size_t new_size5 = strlen(orig5) + 1;
            mbstowcs_s(&converted_chars, name5, new_size5, orig5, _TRUNCATE);
            warehouse.addRecord(Record(5504, name5, GoodsSpace::GoodsTypes::Devices, 500));
        }
    }
    

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    // Init main window (mainDlg)
    if (!DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlg))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MARTINSPROJECT));

    MSG msg;

    // Messages processing cycle
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


// Handler of Main window
INT_PTR CALLBACK MainDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        //When window is being created
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        {
            switch (wParam)
            {
            case IDC_ADD_REC_BUTTON:
                {
                    //Creating Add window
                    HWND hWndAddDlg= CreateDialog(hInst, MAKEINTRESOURCE(IDD_ADD), hDlg, (DLGPROC)AddDlg);
                    ShowWindow(hWndAddDlg, SW_SHOW);
                }
                break;
            case IDC_DEL_REC_BUTTON:
                {
                    //Creating Delete window
                    HWND hWndDeleteDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DELETE), hDlg, (DLGPROC)DeleteDlg);
                    ShowWindow(hWndDeleteDlg, SW_SHOW);
                }
                break;
            case IDC_SHOW_ALL_BUTTON:
                {
                    //Creating Warehouse window
                    HWND hWndWarehouseDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_WAREHOUSE), hDlg, (DLGPROC)WarehouseDlg);
                    ShowWindow(hWndWarehouseDlg, SW_SHOW);
                }
                break;
            case IDC_ORDER_BUTTON:
                {
                    //Creating Order window
                    HWND hWndOrderDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ORDER), hDlg, (DLGPROC)OrderDlg);
                    ShowWindow(hWndOrderDlg, SW_SHOW);
                }
                break;
            case IDC_ORDER_STATE_BUTTON:
            {
                //Creating OrderState window
                HWND hWndOrderStateDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ORDER_STATE), hDlg, (DLGPROC)OrderStateDlg);
                ShowWindow(hWndOrderStateDlg, SW_SHOW);
            }
            break;
            default:
                return DefDlgProc(hDlg, message, wParam, lParam);
            }
        }
        break;

    case WM_CLOSE:
        //When window is closing
        {
            EndDialog(hDlg, 0);
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hDlg, &ps);
            EndPaint(hDlg, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return (INT_PTR)FALSE;
}

//Handler of Warehouse window
INT_PTR CALLBACK WarehouseDlg(HWND hWarehouseDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            //Primary filling of combo box(dropdown menu)
            for (int i = 0; i < GoodsSpace::GoodsTypes::Size; i++) {
                SendDlgItemMessage(hWarehouseDlg, IDC_WRHSGOODSCOMBO, CB_ADDSTRING, 0, LPARAM(GoodsSpace::GoodsTypesTCHAR[i]));
            }
            SendDlgItemMessage(hWarehouseDlg, IDC_WRHSGOODSCOMBO, CB_SETCURSEL, 0, 0);
            //Calling a function, that will update list box, according to combo box current state
            UpdateListBox(hWarehouseDlg);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_WRHSGOODSCOMBO:
            //When combo box sent message
            {
                if (HIWORD(wParam) == CBN_SELCHANGE) { //If combo box state is changed(selection changed)
                    //Update list box, according to combo box current state
                    UpdateListBox(hWarehouseDlg);
                }
            }
            break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWarehouseDlg, &ps);
        EndPaint(hWarehouseDlg, &ps);
    }
    break;

    case WM_CLOSE:
    {
        EndDialog(hWarehouseDlg, 0);
    }
    break;
    
    }
    return (INT_PTR)FALSE;
}

//Handler of Add window
INT_PTR CALLBACK AddDlg(HWND hAddDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        {
            switch (wParam)
            {
            case ID_OK_BUTTON:
                {
                    TCHAR** info = new TCHAR*[GoodsSpace::GOODS_PARAMETERS]; //Declaring array of TCHAR strings
                    for (int i = 0; i < GoodsSpace::GOODS_PARAMETERS; i++) {
                        info[i] = new TCHAR[GoodsSpace::PARAMETER_LENGTH];
                    }
                    //Reading all fields content
                    GetDlgItemText(hAddDlg, IDC_INDEX_EDIT, info[0], GoodsSpace::PARAMETER_LENGTH);
                    GetDlgItemText(hAddDlg, IDC_NAME_EDIT, info[1], GoodsSpace::PARAMETER_LENGTH);
                    GetDlgItemText(hAddDlg, IDC_TYPE_EDIT, info[2], GoodsSpace::PARAMETER_LENGTH);
                    GetDlgItemText(hAddDlg, IDC_COUNT_EDIT, info[3], GoodsSpace::PARAMETER_LENGTH);


                    bool validType = false;
                    //Checking if entered type exists in the system
                    for (int i = 0; i < GoodsSpace::GoodsTypes::Size; i++) {
                        if (!wcscmp(info[2], GoodsSpace::GoodsTypesTCHAR[i])) {
                            validType = true;
                            break;
                        }
                    }

                    if (!validType) {
                        //If no such type found
                        SetDlgItemText(hAddDlg, IDC_INFO_TEXT, L"No such type!");
                    }
                    else {
                        //If type exists
                        int index = _wtoi(info[0]); //Converting TCHAR string to int
                        int type = Utils::TCHARtoTYPE(info[2]); //Converting TCHAR string to type

                        int count = _wtoi(info[3]);
                        warehouse.addRecord(Record(index, info[1], type, count));

                        SetDlgItemText(hAddDlg, IDC_INFO_TEXT, L"Success");
                    }
                }
                break;
            case ID_CANCEL_BUTTON:
                EndDialog(hAddDlg, 0);
                break;
            }
        }
        break;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hAddDlg, &ps);
                EndPaint(hAddDlg, &ps);
            }
        break;

    case WM_CLOSE:
        EndDialog(hAddDlg, 0);
        break;

    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DeleteDlg(HWND hAddDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (wParam)
        {
        case ID_OK_BUTTON:
        {
            TCHAR** info = new TCHAR * [GoodsSpace::GOODS_PARAMETERS];
            for (int i = 0; i < GoodsSpace::GOODS_PARAMETERS; i++) {
                info[i] = new TCHAR[GoodsSpace::PARAMETER_LENGTH];
            }
            GetDlgItemText(hAddDlg, IDC_INDEX_EDIT, info[0], GoodsSpace::PARAMETER_LENGTH);
            GetDlgItemText(hAddDlg, IDC_NAME_EDIT, info[1], GoodsSpace::PARAMETER_LENGTH);
            GetDlgItemText(hAddDlg, IDC_TYPE_EDIT, info[2], GoodsSpace::PARAMETER_LENGTH);
            GetDlgItemText(hAddDlg, IDC_COUNT_EDIT, info[3], GoodsSpace::PARAMETER_LENGTH);

            bool validType = false;
            for (int i = 0; i < GoodsSpace::GoodsTypes::Size; i++) {
                if (!wcscmp(info[2], GoodsSpace::GoodsTypesTCHAR[i])) {
                    validType = true;
                    break;
                }
            }

            if (!validType) {
                SetDlgItemText(hAddDlg, IDC_INFO_TEXT, L"No such type!");
            }
            else {
                int index = _wtoi(info[0]);
                int type = Utils::TCHARtoTYPE(info[2]);

                int count = _wtoi(info[3]);
                int res = warehouse.deleteRecord(Record(index, info[1], type, count));
                if (res == -1) SetDlgItemText(hAddDlg, IDC_INFO_TEXT, L"No Such Record!");
                else SetDlgItemText(hAddDlg, IDC_INFO_TEXT, L"Success");
            }
        }
        break;
        case ID_CANCEL_BUTTON:
            EndDialog(hAddDlg, 0);
            break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hAddDlg, &ps);
        EndPaint(hAddDlg, &ps);
    }
    break;

    case WM_CLOSE:
        EndDialog(hAddDlg, 0);
        break;

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK OrderDlg(HWND hOrderDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (wParam)
        {
        case ID_OK_BUTTON:
            {
                TCHAR** info = new TCHAR * [2]; //array of TCHAR strings
                for (int i = 0; i < 2; i++) {
                    info[i] = new TCHAR[2];
                }
                //Reading all fields content
                GetDlgItemText(hOrderDlg, IDC_NAME_EDIT, info[0], GoodsSpace::PARAMETER_LENGTH);
                GetDlgItemText(hOrderDlg, IDC_COUNT_EDIT, info[1], GoodsSpace::PARAMETER_LENGTH);

                int count = _wtoi(info[1]);
                int result = warehouse.buy(info[0], count); //Calling a function, that will create order and launch it
                if (result == -1) SetDlgItemText(hOrderDlg, IDC_INFO_TEXT, L"No Such Goods!");
                else if(result == -2) SetDlgItemText(hOrderDlg, IDC_INFO_TEXT, L"We don't have so many!");
                else {
                    string infoStr = "Order number - ";
                    TCHAR* infoTCHAR = new TCHAR[50];
                    const char* orig = infoStr.c_str();
                    size_t converted_chars = 0;
                    size_t new_size = strlen(orig) + 1;
                    mbstowcs_s(&converted_chars, infoTCHAR, new_size, orig, _TRUNCATE);
                    TCHAR* orderNumberTCHAR = new TCHAR[10];
                    _itow_s(result, orderNumberTCHAR, 10, 10);
                    lstrcatW(infoTCHAR, orderNumberTCHAR);
                    SetDlgItemText(hOrderDlg, IDC_INFO_TEXT, infoTCHAR);
                }
            }
        break;
        case ID_CANCEL_BUTTON:
            EndDialog(hOrderDlg, 0);
            break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hOrderDlg, &ps);
        EndPaint(hOrderDlg, &ps);
    }
    break;

    case WM_CLOSE:
        EndDialog(hOrderDlg, 0);
        break;

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK OrderStateDlg(HWND hOrderStateDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (wParam)
        {
        case ID_OK_BUTTON:
        {
            TCHAR* orderNumberTCHAR = new TCHAR[10];
            GetDlgItemText(hOrderStateDlg, IDC_ORDER_NUMBER_EDIT, orderNumberTCHAR, GoodsSpace::PARAMETER_LENGTH);

            int orderNumber = _wtoi(orderNumberTCHAR);
            OrdersSpace::Order order = warehouse.getOrder(orderNumber);
            if (order.getNumber() == -1) SetDlgItemText(hOrderStateDlg, IDC_INFO_TEXT, L"No Such Order!");
            else {
                lock_guard<recursive_mutex> locker(*order.mut); //locking order object to get it's state
                string orderStateStr = order.getState();
                //Converting 
                TCHAR* orderStateTCHAR = new TCHAR[orderStateStr.size()];
                const char* orig = orderStateStr.c_str();
                size_t converted_chars = 0;
                size_t new_size = strlen(orig) + 1;
                mbstowcs_s(&converted_chars, orderStateTCHAR, new_size, orig, _TRUNCATE);
                SetDlgItemText(hOrderStateDlg, IDC_ORDER_STATE_TEXT, orderStateTCHAR);
            }
        }
        break;
        case ID_CANCEL_BUTTON:
            EndDialog(hOrderStateDlg, 0);
            break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hOrderStateDlg, &ps);
        EndPaint(hOrderStateDlg, &ps);
    }
    break;

    case WM_CLOSE:
        EndDialog(hOrderStateDlg, 0);
        break;

    }
    return (INT_PTR)FALSE;
}

void UpdateListBox(HWND hWarehouseDlg) {
    SendDlgItemMessage(hWarehouseDlg, IDC_WRHS_LIST, LB_RESETCONTENT, 0, 0); //Reset list box
    TCHAR* SelectedGoodType = new TCHAR[GoodsSpace::PARAMETER_LENGTH];
    GetDlgItemText(hWarehouseDlg, IDC_WRHSGOODSCOMBO, SelectedGoodType, GoodsSpace::PARAMETER_LENGTH); //Reading selected goods type
    int type = Utils::TCHARtoTYPE(SelectedGoodType);

    vector<Record> all_of_type = warehouse.get_all_of_type(type);
    TCHAR*** recordsTCHAR = Utils::VECTORtoTCHAR(all_of_type); //2d array of TCHAR string to convert all info about found records

    for (int i = 0; i < all_of_type.size(); i++) {
        //Constructing string, that we will add to list bot
        int string_size = wcslen(recordsTCHAR[i][0]) + wcslen(recordsTCHAR[i][1]) + wcslen(recordsTCHAR[i][2]) + wcslen(recordsTCHAR[i][3]);
        string_size += 6;
        TCHAR* string_to_add = new TCHAR[string_size];
        lstrcpyW(string_to_add, recordsTCHAR[i][0]);
        lstrcatW(string_to_add, L"\t");
        lstrcatW(string_to_add, recordsTCHAR[i][1]);

        if(wcslen(recordsTCHAR[i][1]) > 7) lstrcatW(string_to_add, L"\t"); // name -> type
        else lstrcatW(string_to_add, L"\t\t");

        lstrcatW(string_to_add, recordsTCHAR[i][2]);
        
        if (type == 0 || type == 1) lstrcatW(string_to_add, L"\t\t"); // type -> count
        else lstrcatW(string_to_add, L"\t\t\t");
        lstrcatW(string_to_add, recordsTCHAR[i][3]);

        SendDlgItemMessage(hWarehouseDlg, IDC_WRHS_LIST, LB_ADDSTRING, 0, LPARAM(string_to_add)); //Adding resulting string to list box
    }
}