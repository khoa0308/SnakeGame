#include <iostream>
#include <SDL.h>
#include<bits/stdc++.h>
#include "SDL_mixer.h"
//#include <SDL2/SDL.h>
#include<SDL_ttf.h>
using namespace std;
///--------------------------------------------------------------
int x[1000],y[1000],a[1000][1000];
int c, d, i, j, n, lastXn, lastYn, lastPress ,diem,cham,dai,q;
string scr,Scr ;
int z,r,t,g;
int score;
SDL_Window* window;
    SDL_Renderer* renderer;
///--------------------------------------------------------------
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Keyboard in SDL";
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
///--------------------------------------------------------------
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect5);
void drawHead(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect);
void drawBody(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect2);
void drawMoi(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect3);
void drawSth(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect4);
///--------------------------------------------------------------
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
///--------------------------------------------------------------ttf
void Draw_Text(string Text,int X, int Y, int sizee)
{
        TTF_Quit();
        if (TTF_Init() < 0)
        {
            SDL_Log("%s", TTF_GetError());
            return ;
        }
        TTF_Font* font = NULL;
        font = TTF_OpenFont("font).ttf",  sizee);
        SDL_Color fg = { 51, 102, 0 };
        string text = Text;
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fg);
        surface = TTF_RenderText_Solid(font, text.c_str(), fg);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_Rect srcRest;
        SDL_Rect desRect;
        TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);
        srcRest.x = 0;
        srcRest.y = 0;
        desRect.x = X;
        desRect.y = Y;
        desRect.w = srcRest.w;
        desRect.h = srcRest.h;
        SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
        SDL_RenderPresent(renderer);
        //SDL_DestroyTexture(texture);
        //texture=NULL;
}
///--------------------------------------------------------------mixer_play
void Play_Music(){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("%s", Mix_GetError());
    }
}
///--------------------------------------------------------------mixer_pause
///--------------------------------------------------------------
int main(int argc, char* argv[])
{
    initSDL(window, renderer);
    SDL_Event e;
    ///------------------------------------------------------------------PHẦN MENU
    Play_Music();
    Mix_Music* music = Mix_LoadMUS("TN.mp3");
    Mix_PlayMusic(music,1000);
    SDL_Texture *background = loadTexture("nen2.bmp", renderer);
    //Nạp ảnh vào một biến texture
    //Nếu có lỗi thì giải phóng hai texture đã nạp, rồi kết thúc
    if (background == nullptr ){
        SDL_DestroyTexture(background);
        quitSDL(window, renderer);
    }
    //Xoá màn hình
    SDL_RenderClear(renderer);
    //Vẽ ảnh nền vào toàn bộ cửa sổ
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    diem=0;
    cham=0;
    while (true) {
        // Đợi 10 mili giây
        //SDL_Delay(10);
        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue;
        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;
        // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        // Nếu chuột (mouse) được nhấn (xuống)
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            //filled_rect.x = e.button.x; // Lấy hoành độ x của chuột
            //filled_rect.y = e.button.y; // Lấy tung độ y của chuột
            //cout<<filled_rect.x<<" "<<filled_rect.y<<endl;
            // Xoá toàn bộ màn hình và vẽ lại với màu sắc tuỳ thuộc chuột trái hay phải được nhấn
            if (e.button.button == SDL_BUTTON_LEFT){
                cout<<e.button.x<<" "<<e.button.y<<endl;
                if(e.button.x>= 184 && e.button.x <=348 && e.button.y>=290 && e.button.y<=336 && diem==0){///MENU START
                    diem=1;
                    Mix_CloseAudio();
                }
                if(e.button.x>= 174 && e.button.x <=360 && e.button.y>=362 && e.button.y<=408 && diem==0){///MENU CREDIT
                    diem=2;
                }
                if(e.button.x>= 104 && e.button.x <=426 && e.button.y>=432 && e.button.y<=494 && diem==0){///MENU QUIT GAME
                    break;
                }
            }
        }
        if(diem==1){///------------------------------------------------------------------PHẦN INGAME
            n=3;// đầu tiên con rắn có 2 ô
            score=0;
            scr=Scr='0';
            for(i=1;i<=39;i++){
                for(j=1;j<=29;j++){
                    a[i*20][j*20]=0;
                }
            }
            // Định nghĩa toạ độ ban đầu và kích cỡ của đầu rắn
            SDL_Rect filled_rect;//đầu
            SDL_Rect filled_rect2;//thân
            SDL_Rect filled_rect3;// mồi
            SDL_Rect filled_rect4;// xóa đuôi
            SDL_Rect filled_rect5;
            filled_rect.x = SCREEN_WIDTH / 2;
            filled_rect.y = SCREEN_HEIGHT / 2;
            filled_rect.w = 18;
            filled_rect.h = 18;
            x[1]=filled_rect.x;
            y[1]=filled_rect.y;
            a[filled_rect.x][filled_rect.y]=1;
            filled_rect2.w = 18;
            filled_rect2.h = 18;
///------------------------------------------------------------------
            filled_rect3.w = 10;
            filled_rect3.h = 10;
///------------------------------------------------------------------
            filled_rect4.w = 18;
            filled_rect4.h = 18;
///------------------------------------------------------------------
            filled_rect5.x = 0;
            filled_rect5.y = 500;
            filled_rect5.w = 800;
            filled_rect5.h = 20;
            for(i=2;i<=n;i++){
                x[i]=x[i-1]-20;
                y[i]=y[i-1];
                a[x[i]][y[i]]=2;
            }
            ///chọn vị trí của mồi
            srand(time(0));
            c=rand()%39*20;
            d=rand()%24*20;
            /// chọn vị trí khác nếu trùng vị trí
            if(a[c][d] !=0 ){
                while(a[c][d] ==1 || a[c][d]==2 || a[c][d]==3){
                    c=rand()%39*20;
                    d=rand()%24*20;
                 }
            }
            a[c][d]=4;
            x[0]=c;
            y[0]=d;
            // Bước nhảy mỗi khi dịch chuyển
            int step = 20;
            //
            refreshScreen(window, renderer, filled_rect5);
            for(i=0;i<=n;i++){
                if(i==1){
                    filled_rect.x=x[i];
                    filled_rect.y=y[i];
                    drawHead(window, renderer, filled_rect );
                }
                if(i>1){
                    filled_rect2.x=x[i];
                    filled_rect2.y=y[i];
                    drawBody(window, renderer, filled_rect2 );
                }
                if(i==0){
                    filled_rect3.x=x[i]+4.5;
                    filled_rect3.y=y[i]+4.5;
                    drawMoi(window, renderer, filled_rect3 );
                }
            }
            lastPress=0;
///------------------------------------------------------------------------------------ttf
            SDL_Texture *background = loadTexture("nenIG.bmp", renderer);
            //Nạp ảnh vào một biến texture
            //Nếu có lỗi thì giải phóng hai texture đã nạp, rồi kết thúc
            if (background == nullptr ){
                SDL_DestroyTexture(background);
                quitSDL(window, renderer);
            }
            //Xoá màn hình
            //SDL_RenderClear(renderer);
            //Vẽ ảnh nền vào toàn bộ cửa sổ
            renderTexture(background, renderer, 0, 520, SCREEN_WIDTH, 81);
            SDL_RenderPresent(renderer);
            string s="YOUR SCORE:";
            z=0;
            r=520;
            t=50;
            Draw_Text(s,z,r,t);
            z=430;
            t=50;
            Draw_Text(Scr,z,r,t);
///-------------------------------------------------------------------------------------
            while (true) {
                // Đợi 10 mili giây
                SDL_Delay(10);
                if (SDL_WaitEvent(&e) == 0) continue;/// Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
                if (e.type == SDL_QUIT) quitSDL(window, renderer);/// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát game
                if (e.type == SDL_KEYDOWN) {/// Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
                    // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
                    //if (e.key.keysym.sym == SDLK_ESCAPE) quitSDL(window, renderer);
                    if (e.key.keysym.sym == SDLK_LEFT ){
                        lastPress=1;
                        //filled_rect.x = (filled_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
                    }
                    if (e.key.keysym.sym == SDLK_RIGHT ){
                        lastPress=2;
                        //filled_rect.x = (filled_rect.x + step) % SCREEN_WIDTH;
                    }
                    if (e.key.keysym.sym == SDLK_DOWN ){
                        lastPress=3;
                        //filled_rect.y = (filled_rect.y + step) % SCREEN_HEIGHT;
                    }
                    if (e.key.keysym.sym == SDLK_UP ){
                        lastPress=4;
                        //filled_rect.y = (filled_rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
                    }
                    for(i=n;i>1;i--){
                        if(i==n){
                            lastXn=x[i];
                            lastYn=y[i];
                            a[x[i]][y[i]]=0;
                        }
                        x[i]=x[i-1];
                        y[i]=y[i-1];
                        a[x[i]][y[i]]=2;
                    }
                    switch(lastPress){
                        case 1:
                            filled_rect.x = (filled_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
                            break;
                        case 2:
                            filled_rect.x = (filled_rect.x + step) % SCREEN_WIDTH;
                            break;
                        case 3:
                            filled_rect.y = (filled_rect.y + step) % SCREEN_HEIGHT;
                            if(filled_rect.y==500 ){
                                filled_rect.y=0;
                            }
                            break;
                        case 4:
                            filled_rect.y = (filled_rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
                            if(filled_rect.y>500 ){
                                filled_rect.y=480;
                            }
                            break;
                    }
                    x[1]=filled_rect.x;
                    y[1]=filled_rect.y;
                    if(a[x[i]][y[i]]==2){
                        cham=1;
                        break;
                    }
                    //Hoạt ảnh ăn mồi
                    if(a[x[1]][y[1]]==4){
                        Play_Music();
                        Mix_Music* music = Mix_LoadMUS("TAM.mp3");
                        Mix_PlayMusic(music,0);
                        a[x[1]][y[1]]=1;
                        score=score+10;
                        g=score;
                        ///------------------------sửa điểm
                        SDL_Texture *background = loadTexture("nenIG.bmp", renderer);
                        if (background == nullptr ){
                            SDL_DestroyTexture(background);
                            quitSDL(window, renderer);
                        }
                        renderTexture(background, renderer, 0, 520, SCREEN_WIDTH, 81);
                        SDL_RenderPresent(renderer);
                        z=0;
                        r=520;
                        t=50;
                        Draw_Text(s,z,r,t);
                        z=430;
                        t=50;
                        scr=Scr=' ';
                        while(g>0){
                            scr=scr+char(g%10 + 48);
                            g=g/10;
                        }
                        dai=scr.length();
                        for(q=dai-1;q>=0;q--){
                            Scr=Scr+scr[q];
                        }
                        ///------------------------
                        while(a[c][d] ==1 || a[c][d]==2 || a[c][d]==3){
                            c=rand()%39*20;
                            d=rand()%24*20;
                        }
                        a[c][d]=4;
                        x[0]=c;
                        y[0]=d;
                        n++;
                        x[n]=lastXn;
                        y[n]=lastYn;
                        a[lastXn][lastYn]=2;
                        filled_rect3.x=c+4.5;
                        filled_rect3.y=d+4.5;
                        drawMoi(window, renderer, filled_rect3 );
                    }
                    else{
                        a[x[1]][y[1]]=1;
                    }
                    drawHead(window, renderer, filled_rect );
                    filled_rect2.x=x[2];
                    filled_rect2.y=y[2];
                    drawBody(window, renderer, filled_rect2 );
                    if(a[lastXn][lastYn]==0){
                    filled_rect4.x=lastXn;
                    filled_rect4.y=lastYn;
                    filled_rect4.w = 18;
                    filled_rect4.h = 18;
                    drawSth(window, renderer, filled_rect4 );
                    }
                    Draw_Text(Scr,z,r,t);
                    // Xoá toàn bộ màn hình và vẽ lại
                }
            }
            if(cham=1){
                    cout<<diem<<endl;;
                    diem=3;
                    Play_Music();
                Mix_Music* music = Mix_LoadMUS("TGO.mp3");
                Mix_PlayMusic(music,0);
                SDL_Texture *background = loadTexture("GO.bmp", renderer);
                if (background == nullptr ){
                    SDL_DestroyTexture(background);
                    quitSDL(window, renderer);
                }
                SDL_RenderClear(renderer);
                renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_RenderPresent(renderer);
                while (diem==3) {
                // Đợi 10 mili giây
                SDL_Delay(10);
                if ( SDL_WaitEvent(&e) == 0) continue;
                if (e.type == SDL_QUIT) quitSDL(window, renderer);
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT)
                        cout<<e.button.x<<" "<<e.button.y<<endl;
                        if(e.button.x>= 256 && e.button.x <=530 && e.button.y>=286 && e.button.y<=350 && diem==3){
                            diem=1;
                        }
                        if(e.button.x>= 328 && e.button.x <=470 && e.button.y>=352 && e.button.y<=424 && diem==3){
                            diem=0;
                        }
                    }
                    //cout<<diem<<endl;
                }
                if(diem==0){
                    Play_Music();
                            Mix_Music* music = Mix_LoadMUS("TN.mp3");
                            Mix_PlayMusic(music,1000);
                    SDL_Texture *background = loadTexture("nen2.bmp", renderer);
                    if (background == nullptr ){
                        SDL_DestroyTexture(background);
                        quitSDL(window, renderer);
                    }
                    SDL_RenderClear(renderer);
                    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_RenderPresent(renderer);
                    //cout<<diem;
                    //break;
                }
            }
        }
        if(diem==2){///------------------------------------------------------------------PHẦN CREDIT
            SDL_Texture *background = loadTexture("CREDIT.bmp", renderer);
            if (background == nullptr ){
                SDL_DestroyTexture(background);
                quitSDL(window, renderer);
            }
            SDL_RenderClear(renderer);
            renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            while (diem==2) {
                // Đợi 10 mili giây
                SDL_Delay(10);
                if ( SDL_WaitEvent(&e) == 0) continue;
                if (e.type == SDL_QUIT) quitSDL(window, renderer);
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT)
                        cout<<e.button.x<<" "<<e.button.y<<endl;
                        if(e.button.x>= 670 && e.button.x <=778 && e.button.y>=510 && e.button.y<=554 && diem==2){
                            diem=0;
                        }
                }
            }
            if(diem==0){
                SDL_Texture *background = loadTexture("nen2.bmp", renderer);
                if (background == nullptr ){
                    SDL_DestroyTexture(background);
                    quitSDL(window, renderer);
                }
                SDL_RenderClear(renderer);
                renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_RenderPresent(renderer);
            }
        }
    }
    cout<<"your score is:"<<score<<endl;
    cout<<"GAME OVER!!!";
    quitSDL(window, renderer);
    return 0;
}
///---------------------------------------------------------------------PHẦN VẼ
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
 //Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
 SDL_Texture *texture = nullptr;
 //Nạp ảnh từ tên file (với đường dẫn)
 SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
 //Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
 if (loadedImage != nullptr){
 texture = SDL_CreateTextureFromSurface(ren, loadedImage);
 SDL_FreeSurface(loadedImage);
 //Đảm bảo việc chuyển đổi không có lỗi
 if (texture == nullptr){
 logSDLError(std::cout, "CreateTextureFromSurface");
 }
 }
 else {
 logSDLError(std::cout, "LoadBMP");
 }
 return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
 //Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
 SDL_Rect dst;
 dst.x = x;
 dst.y = y;
 //Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
 SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
 SDL_RenderCopy(ren, tex, NULL, &dst);
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
 //Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
 SDL_Rect dst;
 dst.x = x;
 dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
 SDL_RenderCopy(ren, tex, NULL, &dst);
}
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect5)
{
    SDL_SetRenderDrawColor(renderer, 134 , 179 , 0, 0);   // xanh reu
    SDL_RenderClear(renderer);
    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
    SDL_RenderFillRect(renderer, &filled_rect5);
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}
//vẽ đầu
void drawHead(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect)
{
    SDL_SetRenderDrawColor(renderer, 127.5, 127.5, 127.5, 127.5);   // grey
    SDL_RenderFillRect(renderer, &filled_rect);
    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}
void drawBody(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect2)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
    SDL_RenderFillRect(renderer, &filled_rect2);
    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}
void drawMoi(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect3)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);   // red
    SDL_RenderFillRect(renderer, &filled_rect3);
    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}
void drawSth(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect4)
{
    SDL_SetRenderDrawColor(renderer, 134 , 179 ,0 , 0);   // xanh reu
    SDL_RenderFillRect(renderer, &filled_rect4);
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
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
//**************************************************************
