#include "DxLib.h"

char Key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ChangeWindowMode(TRUE);               
    if (DxLib_Init() == -1) return -1;     

    SetDrawScreen(DX_SCREEN_BACK);        

    int image;                       
    image = LoadGraph("char.png");      
    int x = 0, y = 0;

    int White;
    White = GetColor(255, 255, 255); 

    //fps取得
    char fpstext[1024] = "0.00fps";
    unsigned long fpskizyuntick, fpsmaetime, fpsnowtime;
    int fpscount;
    fpscount = 0;
    fpskizyuntick = GetTickCount();
    fpsmaetime = fpsnowtime = 0;

    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //↑メッセージ処理         ↑画面をクリア          ↑キーボード入力状態取得       ↑ESCが押されていない

        
        if (Key[KEY_INPUT_LEFT])x -= 3;
        if (Key[KEY_INPUT_RIGHT])x += 3;
        if (Key[KEY_INPUT_UP])y -= 3;
        if (Key[KEY_INPUT_DOWN])y += 3;
        DrawGraph(x, y, image, FALSE);    //char.pngを表示

        //fpsの計測
        fpsnowtime = GetTickCount() - fpskizyuntick;
        if (fpsnowtime >= 1000) {
            wsprintf(fpstext, "%d.%02dfps",
                fpscount + ((1000 - fpsmaetime) * 100 / (fpsnowtime - fpsmaetime)) / 100,
                ((1000 - fpsmaetime) * 100 / (fpsnowtime - fpsmaetime)) % 100);
            fpskizyuntick = GetTickCount();
            fpsmaetime = 0;
            fpscount = 0;
        }
        else {
            fpscount++;
            fpsmaetime = fpsnowtime;
        }
        DrawString(10, 10, fpstext, White);
        ScreenFlip();
    }

    DxLib_End();                            
    return 0;
}