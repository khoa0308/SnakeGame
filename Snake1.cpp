#include <iostream>
#include <SDL.h>
#include<bits/stdc++.h>
//#include <SDL2/SDL.h>
using namespace std;
int a[1000][1000];
int c,d,i,j;
//**************************************************************
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake game";
void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//**************************************************************
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect, const SDL_Rect& filled_rect2, const SDL_Rect& filled_rect3);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Event e;
    //**************************************************************
    for(i=1;i<=39;i++){
        for(j=1;j<=29;j++){
            a[i*20][j*20]=0;
        }
    }
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH / 2;
    filled_rect.y = SCREEN_HEIGHT / 2;
    filled_rect.w = 18;
    filled_rect.h = 18;
    a[filled_rect.x][filled_rect.y]=1;
    SDL_Rect filled_rect2;
    filled_rect2.x = filled_rect.x -20;
    filled_rect2.y = filled_rect.y ;
    filled_rect2.w = 18;
    filled_rect2.h = 18;
    a[filled_rect2.x][filled_rect2.y]=1;
    //**************************************************************
    srand(time(0));
    c=rand()%39*20;
    d=rand()%29*20;
    if(a[c][d] !=0){
        while(a[c][d] ==1){
            c=rand()%39*20;
            d=rand()%29*20;
        }
    }

    SDL_Rect filled_rect3;
    filled_rect3.x = c;
    filled_rect3.y = d;
    filled_rect3.w = 10;
    filled_rect3.h = 10;
    a[filled_rect3.x][filled_rect3.y]=3;
    // Bước nhảy mỗi khi dịch chuyển
    int step = 20;
    // Xoá toàn bộ màn hình và vẽ
    refreshScreen(window, renderer, filled_rect , filled_rect2,  filled_rect3);
    while (true) {
        // Đợi 10 mili giây
        SDL_Delay(10);
        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue;
        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;
        // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
        if (e.type == SDL_KEYDOWN) {
            // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
            if (e.key.keysym.sym == SDLK_ESCAPE) break;
                cout<<a[filled_rect.x][filled_rect.y]<<endl;
            cout<<a[c][d]<<endl;
            cout<<endl;
            // Nếu phím mũi tên trái, dịch sang trái
            // (cộng chiều rộng, trừ bước, rồi lấy phần dư để giá trị luôn dương, và hiệu ứng quay vòng)
            if (e.key.keysym.sym == SDLK_LEFT){
                a[filled_rect2.x][filled_rect2.y]=0;//reset lai o cuoi cung` trong m2h thanh ko co gi`
                filled_rect2.x=filled_rect.x;
                filled_rect2.y=filled_rect.y;
                filled_rect.x = (filled_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            }
            // Tương tự với dịch phải, xuống và lên
            if (e.key.keysym.sym == SDLK_RIGHT){
                a[filled_rect2.x][filled_rect2.y]=0;//reset lai o cuoi cung` trong m2h thanh ko co gi`
                filled_rect2.x = filled_rect.x;
                filled_rect2.y=filled_rect.y;
                filled_rect.x = (filled_rect.x + step) % SCREEN_WIDTH;
            }
            if (e.key.keysym.sym == SDLK_DOWN){
                a[filled_rect2.x][filled_rect2.y]=0;//reset lai o cuoi cung` trong m2h thanh ko co gi`
                filled_rect2.x=filled_rect.x;
                filled_rect2.y=filled_rect.y;
                filled_rect.y = (filled_rect.y + step) % SCREEN_HEIGHT;
            }
            if (e.key.keysym.sym == SDLK_UP){
                a[filled_rect2.x][filled_rect2.y]=0;//reset lai o cuoi cung` trong m2h thanh ko co gi`
                filled_rect2.x=filled_rect.x;
                filled_rect2.y=filled_rect.y;
                filled_rect.y = (filled_rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
            }
            /// tạo 1 mồi mới nếu ô đầu tiên ăn đc mồi
            if(a[filled_rect.x][filled_rect.y]==3){
                a[filled_rect.x][filled_rect.y]=1;
                while(a[c][d] ==1 ){
                    c=rand()%39*20;
                    d=rand()%29*20;
                }
            }
            a[filled_rect3.x][filled_rect3.y]=3;
            filled_rect3.x = c;
            filled_rect3.y = d;
            ///gán ô trong m2c chứa hai ô vuông
            a[filled_rect.x][filled_rect.y]=1;
            a[filled_rect2.x][filled_rect2.y]=1;
            // Xoá toàn bộ màn hình và vẽ lại
            refreshScreen(window, renderer, filled_rect , filled_rect2,  filled_rect3);
        }
    }
    quitSDL(window, renderer);
    return 0;
}
// Xoá và vẽ lại toàn bộ màn hình với 1 hình chữ nhật
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect, const SDL_Rect& filled_rect2, const SDL_Rect& filled_rect3)
{
    // Tô nền màu xanh lá
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   // green
    SDL_RenderClear(renderer);
    // Đặt màu vẽ về đen và vẽ hình chữ nhật
    SDL_SetRenderDrawColor(renderer, 127.5, 127.5, 127.5, 127.5);   // grey
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
    SDL_RenderFillRect(renderer, &filled_rect2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);   // red
    SDL_RenderFillRect(renderer, &filled_rect3);
    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}
//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
/// khởi tạo SDL
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
