#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int data_scatter[][2] = {
    {99, 82},
    {68, 68},
    {99, 80},
    {99, 82},
    {70, 68},
    {10, 30},
    {50, 80},
    {30, 80}
};

void DrawCircle(HDC hdc, int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 1 - r;

    while (x <= y) {
        // Menggambar 8 simetri titik lingkaran
        SetPixel(hdc, xc + x, yc + y, RGB(255, 0, 0));
        SetPixel(hdc, xc - x, yc + y, RGB(255, 0, 0));
        SetPixel(hdc, xc + x, yc - y, RGB(255, 0, 0));
        SetPixel(hdc, xc - x, yc - y, RGB(255, 0, 0));
        SetPixel(hdc, xc + y, yc + x, RGB(255, 0, 0));
        SetPixel(hdc, xc - y, yc + x, RGB(255, 0, 0));
        SetPixel(hdc, xc + y, yc - x, RGB(255, 0, 0));
        SetPixel(hdc, xc - y, yc - x, RGB(255, 0, 0));

        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow){
    MSG msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Line";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Grid", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);

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

    static wchar_t *ver1 = L"1";

    // dimensi 5
    int angka_x = 5; 
    int angka_y = 105;

    switch(msg){
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            color = GetSysColor(COLOR_BTNFACE);
            SetBkColor(hdc, color);

            // MoveToEx(hdc, 10, 0, NULL);
            // LineTo(hdc, 10, 200);

            for (int x = 0; x <= 800; x += 20){
                MoveToEx(hdc, x, 0, NULL);
                LineTo(hdc, x, 450);
            }

            for (int y = 20; y <= 450; y += 20){
                MoveToEx(hdc, 0, y, NULL);
                LineTo(hdc, 800, y);
            }

            //DrawCircle(hdc, 200, 200, 10);  // (10, 10)

            for (int i = 0; i < 10; i++){
                // dibagi untuk dimensi 5 // akhir adalah jari jari
                DrawCircle(hdc, (data_scatter[i][0] * 20)/5, 440 - ((data_scatter[i][1] * 20)/5), 5);
            }

            hFont = CreateFontW(15, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0,
                0, 0, 0, 0, L"Arial");
            holdFont = SelectObject(hdc, hFont);
            // TextOutW(hdc, 15, 445,  ver1,  lstrlenW(ver1));

            for (int i = 0; i <= 400; i += 20){
                wchar_t buffer[10];

                wsprintfW(buffer, L"%d", angka_y);
    
                // Menampilkan angka di window
                TextOutW(hdc, 15, 15 + i, buffer, wcslen(buffer));
                angka_y -= 5;
            }

            for (int i = 0; i <= 700; i += 20){
                wchar_t buffer[10];

                wsprintfW(buffer, L"%d", angka_x);
    
                // Menampilkan angka di window
                TextOutW(hdc, 15 + i, 445, buffer, wcslen(buffer));
                angka_x += 5;
            }


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