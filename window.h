#pragma once
#define SDL_MAIN_HANDLED
#define _SDL_

#include<C:\Users\Curt\Documents\Visual Studio 2012\Libraries\SDL2\include\sdl.h>
#include <iostream>
#include <chrono>
#include <vector>

#include<functional>




/* Constants rounded for 21 decimals. */
#define     M_E           2.71828182845904523536
#define     M_LOG2E       1.44269504088896340736
#define     M_LOG10E      0.434294481903251827651
#define     M_LN2         0.693147180559945309417
#define     M_LN10        2.30258509299404568402
#define     M_PI          3.14159265358979323846
#define     M_PI_2        1.57079632679489661923
#define     M_PI_4        0.785398163397448309616
#define     M_1_PI        0.318309886183790671538
#define     M_2_PI        0.636619772367581343076
#define     M_1_SQRTPI    0.564189583547756286948
#define     M_2_SQRTPI    1.12837916709551257390
#define     M_SQRT2       1.41421356237309504880
#define     M_SQRT_2      0.707106781186547524401
                      


#define     Print(x)                  std::cout << (x) << std::endl
#define     GetRandom( min, max )     ((rand() % (int)(((max) + 1) - (min))) + (min))  
#define     RANDOM(x)                 ((rand() * (1.0 / (1.0 + RAND_MAX))) * (x))
#define     RANDOM_RANGE(x)           (RANDOM(x * 2) - (x))

#ifdef RGB
#undef RGB
#endif

#define     RGB(r,g,b)                ((int)(b) + ((int)(g)<< 8) + ((int)(r) << 16))
#define     RADIANS(angle)            ((angle) * .0174532925199444)
           
#define     LOOP(x)                   for(int count = 0; count < (x); count++)
#define     for_loop(x,c)             for(int (x) = 0; (x) < (c); (x)++)
           
#define     SCREENWIDTH        1280 //680 
#define     SCREENHEIGHT       960 //460 
           
#define     _LOOP_GAME         LOOP_GAME()        // This is being done for future compatibility with various Graphics Libraries
#define     _CLS                     CLS()        //
#define     _SYNC                   SYNC()        //
                               
#define     _COS(a)               cos(RADIANS(a))  //   Cos[(int)a] // 
#define     _SIN(a)               sin(RADIANS(a)) //  Sin[(int)a] //
           
#define     MIN(a,b)          ((a<b) ? a : b)
#define     MAX(a,b)          ((a>b) ? a : b)
           
#define     PICK_ONE(a,b)          ((RANDOM(1) > .5) ? a : b)
           
#define     Speed_Test(x)     \
    float Timer = SDL_GetTicks();  \
    x  \
       \
    std::cout << "Speed:" << SDL_GetTicks() - Timer << std::endl;
                        


extern float Cos[360], 
             Sin[360]; 



struct Vec2{
    Vec2(){}
    Vec2(float X, float Y):x(X),y(Y){}
    union{
        struct{
            float x,y;
        };
        struct{
            float w,h;
        };
    };
};







 
class GUI;





class CallBack{
    public:
        CallBack(){};
        ~CallBack(){};

       void (*CallBackOnEvent)                (SDL_Event* Event);

       void (*CallBackOnInputFocus)           ();
       void (*CallBackOnInputBlur)            ();
       void (*CallBackOnKeyDown)              (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier , Uint8 rep);                                                    //(SDL_Keysym sym, int mod, Uint16 unicode);
       void (*CallBackOnKeyUp)                (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier );                                                               //(SDL_Keysym sym, int mod, Uint16 unicode);
       void (*CallBackOnMouseFocus)           ();
       void (*CallBackOnMouseBlur)            ();
       void (*CallBackOnMouseMove)            (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
       void (*CallBackOnMouseWheel)           (bool Up, bool Down); 
                                             
       void (*CallBackOnLButtonDown )         (int mX, int mY);
       void (*CallBackOnLButtonUp  )          (int mX, int mY);
       void (*CallBackOnRButtonDown)          (int mX, int mY);
       void (*CallBackOnRButtonUp )           (int mX, int mY);
       void (*CallBackOnMButtonDown)          (int mX, int mY);
       void (*CallBackOnMButtonUp   )         (int mX, int mY);


       void (*CallBackOnJoyAxis)              (Uint8 which, Uint8 axis, Sint16 value);
       void (*CallBackOnJoyButtonDown)        (Uint8 which, Uint8 button);
       void (*CallBackOnJoyButtonUp)          (Uint8 which, Uint8 button);
       void (*CallBackOnJoyHat)               (Uint8 which, Uint8 hat, Uint8 value);
       void (*CallBackOnJoyBall)              (Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
       void (*CallBackOnMinimize)             ();
       void (*CallBackOnRestore)              ();
       void (*CallBackOnResize)               (int w,int h);
       void (*CallBackOnExpose)               ();
       void (*CallBackOnExit)                 ();
       void (*CallBackOnUser)                 (Uint8 type, int code, void* data1, void* data2);


        

       void SetOnEvent(SDL_Event* Event);

       void SetOnInputFocus();
       void SetOnInputBlur();
       
       void SetOnKeyDown(void (*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier , Uint8 rep)) {CallBackOnKeyDown     = f;}
       void SetOnKeyUp  (void (*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier ))            {CallBackOnKeyUp       = f;}
       
       void SetOnMouseFocus                   ();
       void SetOnMouseBlur                    ();
       void SetOnMouseMove                    (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
       void SetOnMouseWheel                   (bool Up, bool Down);    
       
       void SetOnLButtonDown(void (*f)        (int, int))                                            {CallBackOnLButtonDown = f;}
       void SetOnLButtonUp(void (*f)          (int, int))                                            {CallBackOnLButtonUp   = f;}
       void SetOnRButtonDown(void (*f)        (int, int))                                            {CallBackOnRButtonDown = f;}
       void SetOnRButtonUp(void (*f)          (int, int))                                            {CallBackOnRButtonUp   = f;}
       void SetOnMButtonDown(void (*f)        (int, int))                                            {CallBackOnMButtonDown = f;}
       void SetOnMButtonUp(void (*f)          (int, int))                                            {CallBackOnMButtonUp   = f;}
       
       void SetOnJoyAxis                      (Uint8 which, Uint8 axis, Sint16 value);
       void SetOnJoyButtonDown                (Uint8 which, Uint8 button);
       void SetOnJoyButtonUp                  (Uint8 which, Uint8 button);
       void SetOnJoyHat                       (Uint8 which, Uint8 hat, Uint8 value);
       void SetOnJoyBall                      (Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
       
       void SetOnMinimize                     ();
       void SetOnRestore                      ();
       void SetOnResize                       (int w,int h);
       void SetOnExpose                       ();
       void SetOnExit                         ();
       void SetOnUser                         (Uint8 type, int code, void* data1, void* data2);

};

 //      void CallBackOnKeyDown((void*)funcptr, SDLKey sym, SDLMod mod, Uint16 unicode);

class Window{

public:
	Window();~Window();
	Window(int,int,int,int,char*);


	 int       X,
	       	   Y,
		       WIDTH,
		       HEIGHT;

	 char     *TITLE;


     SDL_Window             *HWND;
	 SDL_Texture            *BackBuffer;
     SDL_Renderer           *Renderer;

	 Uint32                  *WindowPixels;

	 Uint32                  WindowFormat; 
	 SDL_Event               Event;
	 SDL_Surface            *WindowSurface;
	 SDL_PixelFormat        *MappingFormat;

     SDL_Surface            *FONT_SURFACE;
     SDL_Texture            *FONT_TEXTURE;
     int FONT_SET[96*256];
// Mouse Position and Velocity can be accessed as either SDL_Point or via its X,Y Coords. 
// This is done for Future implementations with SDL;

     struct{
         float Angle,
               Speed;

         union {
             struct{
                 float X,
                       Y;
             }Velocity;
             SDL_Point MouseVelocity;
         };


         struct{
             bool Left,
                  Right,
                  Center;
         }Button;


         union{
             struct{
                 float X,
                       Y;
             }Position;
             SDL_Point MousePosition;
         };
// Methods possible callback registry;
         void OnClick();
         void MouseOver();
         void MouseMove();
     }Mouse;

     CallBack CallBacks;

     struct{
         struct keytype{
             int  Modifier;
             int  Code;
             int  ScanCode;
             bool State;
         }Key;
        const Uint8 *KeyState;
    }Keyboard;


    GUI *thisGUI;


    unsigned long           DRAW_COLOR;
	float  FPS;
 

    double TIME;

    int   FrameCounter;
    int   CYCLE_COUNTER;

    int   CyclePerSecond;
   
    float CYCLE_TIMER;
	float TIMER;

    inline void  Set_Sync_rate(float rate){Sync_rate = rate;}
    inline float Get_Sync_rate(){return Sync_rate;}

private:
    
    float Sync_rate;

public:

  void      SYNC               ();
  void      CLS                ();
  bool      LOOP_GAME          ();

  void      SET_PIXEL          (int, int, Uint32);
  void      SET_PIXELII        (int, int, Uint32);
  void      SET_DRAW_COLOR     (unsigned long Col);
  void      LINE               (int x1,int y1,int x2,int y2);
  void      LINE2              (int x,int y, float Angle,int Length);
  void      CIRCLE             (int x, int y, float radius);
  void      FILLED_CIRCLE      (int x, int y, float radius);
  void      BOX                (int X1, int Y1, int X2, int Y2);
  void      FILLED_BOX         (int X1, int Y1, int X2, int Y2);
 

  bool      Is_CLICK           (int X, int Y);

  int       WINDOW_OFFSET;
  int       LEFT_BOUNDS;
  int       TOP_BOUNDS;
  int       RIGHT_BOUNDS;
  int       BOTTOM_BOUNDS;

  void      LOCK_PIXELS();
  void      UNLOCK_PIXELS();

  void      PRINT_SCREEN(char *text);
  void      PRINT_FONT(char*);

  float OldMouseX;
  float OldMouseY;

  void SetGUI(GUI *gui){ thisGUI = gui;}
  private:
       void EventHandler(SDL_Event &Event);

       bool Active;
       bool Alive;

private:
    float ResizeAspect;
};
 
extern   Window   *SCREEN; 
extern   bool      SetActiveWindow(Window *active); 


class Widgit{
public :
        Widgit(){};

    Widgit *Parent;
    Widgit *Child;
virtual void Update();
};
class Frame : public Widgit{
public:
        Frame(){}
        Frame(Vec2 pos,Vec2 size);
        Vec2 Position;
        Vec2 Size;
        void Update();
private:
        void Render();
};
class TextBox : public Widgit{
public:
    TextBox(){}
    TextBox(Vec2 pos , float width);
        void Update();
        Vec2 Position;
        Vec2 Size;
private:
        void Render();
};
class Button : public Widgit{
public:
    Button(){}
    Button(int x, int y, float height, float width);

        Vec2 Position;
        Vec2 Size;
        
        bool HasFocus;
        bool IsVisible;
        
        void (*CallBackOnClick )     (int mL, int mR);
        void (*CallBackMouseOver )   (int mx, int my);
        
        void SetOnClick  (void (*f)  (int mL, int mR))    {CallBackOnClick   = f;} 
        void SetMouseOver(void (*f)  (int mx, int my))    {CallBackMouseOver = f;}
        
        void Update();

private:
        void Render();
};
class GUI{
public:
    GUI();
    GUI(Window &parent);
   ~GUI();
    Window *Parent;

    std::vector<Widgit*> Widgits;

    Button*  Make_Button(int x, int y, int height, int width);
    TextBox* Make_TextBox(Vec2 topleft, float width);
    Frame*   Make_Frame(Vec2 pos,Vec2 size);

    void Update();
    int NumberOfWidgits;

static bool GUI::GUIActive;
};


//____________________________________________________________________________________________________________________________________________________________
//---------------------------------- TOOL BOX FUNCTIONS -------------------------------------------------------------------------------------------------- 
//=============================================================================================================================== 


extern   float     FindAngle          (SDL_Point A, SDL_Point B);
extern inline int MODULO(int x, int n);
extern float FAST_SQRT(float X);

