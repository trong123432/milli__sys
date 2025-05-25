#include <windows.h>

extern int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    char* szCmdLine = GetCommandLineA();
    return WinMain(hInstance, NULL, szCmdLine, SW_SHOWDEFAULT); // Gọi WinMain với chế độ hiển thị mặc định
}