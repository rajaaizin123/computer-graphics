#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
x1,y1 = tbp
x2,y2 = uas
x3,y3 = tugas
x4,y4 = uts
*/

float rata_tbp = 40.4f;
float rata_uas = 85.5f;
float rata_tugas = 90;
float rata_uts = 70.5f;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow){
    MSG msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Radar";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Radar Chartku", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 1000, 600, NULL, NULL, hInstance, NULL);

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;

    DWORD color;

    HFONT hFont, holdFont;

    static wchar_t *tbp = L"TBP";
    static wchar_t *uas = L"UAS";
    static wchar_t *tugas = L"Tugas";
    static wchar_t *uts = L"UTS";

    // dimensi 5
    int angka_x = 5; 
    int angka_y = 105;

    switch(msg){
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            color = GetSysColor(COLOR_BTNFACE);
            SetBkColor(hdc, color);

            int x1 = 300, y1 = 100;
            int x2 = 700, y2 = 100;
            int x3 = 700, y3 = 500;
            int x4 = 300, y4 = 500;
            int dimensi_angka = 100;

            // tulis data
            hFont = CreateFontW(15, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0,
                0, 0, 0, 0, L"Arial");
            holdFont = SelectObject(hdc, hFont);
            TextOutW(hdc, x1 - 20, y1 - 20,  tbp,  lstrlenW(tbp));
            TextOutW(hdc, x2, y2 - 20,  uas,  lstrlenW(uas));
            TextOutW(hdc, x3, y3,  tugas,  lstrlenW(tugas));
            TextOutW(hdc, x4 - 20, y4,  uts,  lstrlenW(uts));

            // garis ke pusat
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, 500, 300);

            MoveToEx(hdc, x2, y2, NULL);
            LineTo(hdc, 500, 300);

            MoveToEx(hdc, x3, y3, NULL);
            LineTo(hdc, 500, 300);

            MoveToEx(hdc, x4, y4, NULL);
            LineTo(hdc, 500, 300);


            // titik nilai
            int nilai_tbp = (100 - rata_tbp) / 10;
            int x_tbp = x1 + (20 * nilai_tbp);
            int y_tbp = y1 + (20 * nilai_tbp);

            int nilai_uas = (100 - rata_uas) / 10;
            int x_uas = x2 - (20 * nilai_uas);
            int y_uas = y2 + (20 * nilai_uas);

            int nilai_tugas = (100 - rata_tugas) / 10;
            int x_tugas = x3 - (20 * nilai_tugas);
            int y_tugas = y3 - (20 * nilai_tugas);

            int nilai_uts = (100 - rata_uts) / 10;
            int x_uts = x4 + (20 * nilai_uts);
            int y_uts = y4 - (20 * nilai_uts);
            
            HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 250, 0));
            HPEN hOldPen = (HPEN) SelectObject(hdc, hPen);

            MoveToEx(hdc, x_tbp, y_tbp, NULL);
            LineTo(hdc, x_uas, y_uas);

            MoveToEx(hdc, x_uas, y_uas, NULL);
            LineTo(hdc, x_tugas, y_tugas);

            MoveToEx(hdc, x_tugas, y_tugas, NULL);
            LineTo(hdc, x_uts, y_uts);

            MoveToEx(hdc, x_uts, y_uts, NULL);
            LineTo(hdc, x_tbp, y_tbp);
            
            SelectObject(hdc, hOldPen);
            DeleteObject(hPen);

            for (int i = 1; i <= 10; i++){
                MoveToEx(hdc, x1, y1, NULL);
                LineTo(hdc, x2, y2);
    
                MoveToEx(hdc, x2, y2, NULL);
                LineTo(hdc, x3, y3);
    
                MoveToEx(hdc, x3, y3, NULL);
                LineTo(hdc, x4, y4);
    
                MoveToEx(hdc, x4, y4, NULL);
                LineTo(hdc, x1, y1);

                // menulis dimensi angka
                wchar_t buffer[10];
                wsprintfW(buffer, L"%d", dimensi_angka);
                TextOutW(hdc, 500 - 5, y1 - 10, buffer, wcslen(buffer));
                dimensi_angka -= 10;

                x1 += 20; y1 += 20;
                x2 -= 20; y2 += 20;
                x3 -= 20; y3 -= 20;
                x4 += 20; y4 -= 20;

            }

            // MoveToEx(hdc, 400, 400, NULL);
            // LineTo(hdc, 500, 300);
            


            SelectObject(hdc, holdFont);
            DeleteObject(hFont);

            EndPaint(hwnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}