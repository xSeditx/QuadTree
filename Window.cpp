//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
//        SDL FRAMEWORK FOR GRAPHICS OPERATIONS                                                                                                                                                                                                                                                                                                                        
//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
// TARGET: WINDOW *SCREEN pointer. This is where all functions read from and draw to.   
//
// TODO: Fix the KEYBOARD Handler so that a callback class is made and various functions can be added to the 
// callback Vector 
// Change the structure of the Mouse information in the class so its called MOUSE.Position Angle etc... etc
//=====================================================================================================================                                                                                                                                                                                                                                                                                                                                      

#include"window.h"
#include<windows.h>
#include<iostream>
#include<vector>

#define __DEBUG_

Window *SCREEN ={0};
int WINDOW_OFFSET = 1;
int LEFT_BOUNDS = 0 + WINDOW_OFFSET;
int TOP_BOUNDS = 0 + WINDOW_OFFSET;
int RIGHT_BOUNDS = SCREENWIDTH - WINDOW_OFFSET;
int BOTTOM_BOUNDS = SCREENHEIGHT - WINDOW_OFFSET;

float Cos[360];// = {0}, 
float Sin[360]; // = {0};
 

// CONSTRUCTS A BASIC WINDOW AND BACKBUFFER ASSOCIATED WITH WINDOW



//Submit GLMAPBUFFER();

Window::~Window()
{
    delete(WindowPixels);
}
Window::Window(int x,int y,int width,int height,char *title)
      : 
      X(x),
      Y(y),
      WIDTH(width),
      HEIGHT(height),
      TITLE( title),
      Active(true),
      Alive(true)
{
        Mouse.MouseVelocity.x = 
        Mouse.MouseVelocity.y = 
        Mouse.Angle           = 0; // Initialize Mouse to Zero since no constructor currently exist


        if(SDL_Init(SDL_INIT_VIDEO) !=0) Print("Init Video Error");
        HWND = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       WIDTH, 
                                       HEIGHT, 0); 
        if(!HWND) Print("ERROR: Initializing SDL Window");


        Renderer = SDL_CreateRenderer(HWND, -1, SDL_RENDERER_ACCELERATED);                                                          
        
        if(!Renderer) Print("ERROR: Initializing SDL Renderer");
            
        if(SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255) != 0) Print("Set Color Error");
        
        BackBuffer = SDL_CreateTexture(Renderer,
                                       SDL_PIXELFORMAT_ARGB8888, 
                                       SDL_TEXTUREACCESS_STREAMING, 
                                       WIDTH, 
                                       HEIGHT);

        SDL_SetRenderTarget(Renderer, BackBuffer);

        SDL_SetWindowResizable(HWND, SDL_TRUE);
        
        WindowSurface   = SDL_GetWindowSurface     (HWND);
        WindowFormat    = SDL_GetWindowPixelFormat (HWND);
        
        WindowPixels = new Uint32[WIDTH * (HEIGHT + 400) + 1];
        memset(WindowPixels, 255, WIDTH * HEIGHT * sizeof(Uint32)); 


        thisGUI = nullptr;

        FrameCounter=0;
        CYCLE_COUNTER=0;
        FPS =0;
        CyclePerSecond=0;
        Sync_rate = 0;
        TIMER = SDL_GetTicks();

//------------------------ Lookup Tables --------------------------------------------------------------------------
       for_loop(count, 360){
         Cos[count] = cos(RADIANS(count));
         Sin[count] = sin(RADIANS(count));
       }
//-----------------------------------------------------------------------------------------------------------------


        CallBacks.CallBackOnEvent          = NULL;
        CallBacks.CallBackOnInputFocus     = NULL;
        CallBacks.CallBackOnInputBlur      = NULL;
        CallBacks.CallBackOnKeyDown        = NULL;
        CallBacks.CallBackOnKeyUp          = NULL;
        CallBacks.CallBackOnMouseFocus     = NULL;
        CallBacks.CallBackOnMouseBlur      = NULL;
        CallBacks.CallBackOnMouseMove      = NULL;
        CallBacks.CallBackOnMouseWheel     = NULL;
                                           
        CallBacks.CallBackOnLButtonDown    = NULL;
        CallBacks.CallBackOnLButtonUp      = NULL;
        CallBacks.CallBackOnRButtonDown    = NULL;
        CallBacks.CallBackOnRButtonUp      = NULL;
        CallBacks.CallBackOnMButtonDown    = NULL;
        CallBacks.CallBackOnMButtonUp      = NULL;
                                         
        CallBacks.CallBackOnJoyAxis        = NULL;
        CallBacks.CallBackOnJoyButtonDown  = NULL;
        CallBacks.CallBackOnJoyButtonUp    = NULL;
        CallBacks.CallBackOnJoyHat         = NULL;
        CallBacks.CallBackOnJoyBall        = NULL;
        CallBacks.CallBackOnMinimize       = NULL;
        CallBacks.CallBackOnRestore        = NULL;
        CallBacks.CallBackOnResize         = NULL;
        CallBacks.CallBackOnExpose         = NULL;
        CallBacks.CallBackOnExit           = NULL;
        CallBacks.CallBackOnUser           = NULL;



    SetActiveWindow(this);


    OldMouseX =0;
    OldMouseY =0;
}
bool SetActiveWindow(Window *active)
{
	if(SCREEN = active)
	    return true;
    else
        return false;
}


void Window::CLS(){

float delta = SDL_GetTicks() - TIMER;
      FPS = 1000 / delta ; //SDL_GetTicks() - SCREEN->TIMER/1000 ;////SCREEN->FRAME_COUNTER ; 
      TIMER = SDL_GetTicks();
      memset(WindowPixels, 0, WIDTH * HEIGHT * sizeof(Uint32));  //SDL_RenderClear(SCREEN->RENDER);

}
void Window::SYNC(){

        float delta = SDL_GetTicks() - TIMER;
    	SDL_UpdateTexture(BackBuffer, NULL, WindowPixels, WIDTH * sizeof(Uint32)); // SLOW
        SDL_RenderCopy(Renderer, BackBuffer, NULL, NULL);
        SDL_RenderPresent(Renderer);

}
bool Window::LOOP_GAME()
 {
     	CYCLE_COUNTER++;
        FrameCounter++;
        float delta = SDL_GetTicks() - SCREEN->CYCLE_TIMER;
        

        if(delta < (1000 / SCREEN->Get_Sync_rate())){ // <-- Frame Rate Limiter
                SDL_Delay((1000 / SCREEN->Get_Sync_rate()) - delta);
        }

	    CyclePerSecond = 1000 / delta ;
		CYCLE_TIMER = SDL_GetTicks();
 

  		SDL_PollEvent(&Event);
        EventHandler(Event);

        if (CallBacks.CallBackOnEvent != nullptr) 
            CallBacks.CallBackOnEvent(&Event);

        if (Alive == false) return false;
        SDL_Point Delta = {Mouse.Position.X - OldMouseX,
                           Mouse.Position.Y - OldMouseY};
        OldMouseX = Mouse.Position.X;
        OldMouseY = Mouse.Position.Y;
        Mouse.Angle = FindAngle( Mouse.MousePosition, Delta);
     
 return true;
 }

void Window::EventHandler(SDL_Event &Event)
 {
        if(thisGUI != nullptr) thisGUI->Update();

        int XX =0,YY=0;
        SDL_GetRendererOutputSize(Renderer, &XX, &YY);
        
           

        switch (Event.type)
        {

   
              
                // SDL_Log("Window %d exposed", event->window.windowID);
//============================================================================= EXIT ============================================
                case SDL_QUIT:
                        Alive  = false;
                        Active = false;
	          	        return;
                break;
//=========================================================================== MOUSE BUTTON UP ========================================
                    float ResizeAspect;

                case SDL_WINDOWEVENT_RESIZED:
                     Print("RESIZE");
                break;

                case SDL_MOUSEBUTTONUP:

                        if (Event.button.button == SDL_BUTTON_LEFT)
                        {
                            Mouse.Button.Left = false;
                          if(CallBacks.CallBackOnLButtonUp != nullptr) 
                              CallBacks.CallBackOnLButtonUp( Mouse.Position.X, Mouse.Position.Y);
                        }
                        if (Event.button.button == SDL_BUTTON_RIGHT)
                        {
                            Mouse.Button.Right = false;
                            if(CallBacks.CallBackOnRButtonUp != nullptr)
                                CallBacks.CallBackOnRButtonUp( Mouse.Position.X, Mouse.Position.Y);
                        }
                        break;
 
                        if (Event.button.button == SDL_BUTTON_MIDDLE)
                        {
                            Mouse.Button.Center = false;
                            if(CallBacks.CallBackOnMButtonUp != nullptr)
                                CallBacks.CallBackOnMButtonUp( Mouse.Position.X, Mouse.Position.Y);
                        }

//========================================================================== MOUSE BUTTON DOWN ====================================

                case SDL_MOUSEBUTTONDOWN:
                        if (Event.button.button == SDL_BUTTON_LEFT)
                        {
                            Mouse.Button.Left = true;
                            if(CallBacks.CallBackOnLButtonDown != nullptr)
                                CallBacks.CallBackOnLButtonDown( Mouse.Position.X, Mouse.Position.Y);
                        }

                        if (Event.button.button == SDL_BUTTON_RIGHT)
                        {
                            Mouse.Button.Right = true;
                            if(CallBacks.CallBackOnRButtonDown != nullptr)
                                CallBacks.CallBackOnRButtonDown( Mouse.Position.X, Mouse.Position.Y);
                        }

                        if (Event.button.button == SDL_BUTTON_MIDDLE)
                        {
                            Mouse.Button.Center = true;
                            if(CallBacks.CallBackOnMButtonDown != nullptr)
                                CallBacks.CallBackOnMButtonDown( Mouse.Position.X, Mouse.Position.Y);
                        }

//============================================================================================================================

                        
 //=============================================================================== MOUSE MOTION ===============================

                case SDL_MOUSEMOTION:
                        SDL_Point DELTA;
                        DELTA.x = Event.motion.x;
                        DELTA.y = Event.motion.y;
                        
				        Mouse.Position.X = Event.motion.x;
                        Mouse.Position.Y = Event.motion.y;
                        Mouse.Velocity.X = Event.motion.x - Mouse.Position.X;
                        Mouse.Velocity.Y = Event.motion.y - Mouse.Position.Y;
                    

                   if(CallBacks.CallBackOnMouseMove != nullptr)
                        CallBacks.CallBackOnMouseMove(Event.motion.x, Event.motion.y, Event.motion.xrel, Event.motion.yrel,  Mouse.Button.Left, Mouse.Button.Right, Mouse.Button.Center);

                break;

//=================================================================================== KEYBOARD ====================================
//______________________________________________________________________________________________________________________________________
//=====================================================================================================================================
//  BITMASK FOR KEYBOARD
//  Bit-AND(&&) it with KMOD_SHIFT


	            case SDL_KEYDOWN:
                        Keyboard.KeyState     = SDL_GetKeyboardState(NULL);
                        Keyboard.Key.Modifier = SDL_GetModState();
                        Keyboard.Key.Code     = Event.key.keysym.sym; 
                        Keyboard.Key.ScanCode = Event.key.keysym.scancode; 
                        Keyboard.Key.State    = true;

                        if (CallBacks.CallBackOnKeyDown != nullptr) 
                            CallBacks.CallBackOnKeyDown(Event.key.keysym.sym, Event.key.keysym.scancode , Event.key.keysym.mod ,Event.key.repeat);
                      
                break;

                case SDL_KEYUP:
                        Keyboard.KeyState     = SDL_GetKeyboardState(NULL);
                        Keyboard.Key.Modifier = SDL_GetModState();
                        Keyboard.Key.Code     = Event.key.keysym.sym; 
                        Keyboard.Key.ScanCode = Event.key.keysym.scancode;
                        Keyboard.Key.State    = false;
                       

                       if (CallBacks.CallBackOnKeyDown != nullptr) 
                           CallBacks.CallBackOnKeyUp(Event.key.keysym.sym, Event.key.keysym.scancode , Event.key.keysym.mod);
                       
                break;
        }
//============================================================================================================================
}

void Window::LOCK_PIXELS(){
	int   PITCH;
	void *PIXELS;
	SDL_LockTexture(SCREEN->BackBuffer, NULL, &PIXELS,  &PITCH);
}
void Window::UNLOCK_PIXELS(){
	SDL_UnlockTexture(SCREEN->BackBuffer);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// PRIMATIVE DRAWING OPERATIONS ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SET_DRAW_COLOR     (unsigned long Col){
         SCREEN->DRAW_COLOR = Col; //SETS THE DRAWING COLOR FOR ALL PRIMATIVE DRAWING OPERATIONS
}

void Window::SET_PIXEL(int x, int y, Uint32 COLOR)
{
//  SETTING A PIXELS WITHOUT PROTECTION 
//                                                            **NOTE** 
//Currently only overflows in Y direction and much space has been allocated as a buffer to prevent this issue... do not mistake it for being correct value just because it does not overflow
	SCREEN->WindowPixels[(y * SCREEN->WIDTH) + x] = COLOR; //((Uint32*)pixels)[ x + ( y * SCREEN_WIDTH ) ] = SDL_MapRGB(fmt, 255, 0, 0);

}
void Window::SET_PIXELII(int x, int y, Uint32 COLOR){
//SETS A PIXEL WITH BOUNDS CHECKING FOR THE SCREEN
           x = MODULO(x, SCREENWIDTH);
           y = MODULO(y, SCREENHEIGHT);
	SCREEN->WindowPixels[((y) * SCREEN->WIDTH) + (x)] = COLOR;
}

void Window::FILLED_BOX(int X1, int Y1, int X2, int Y2){
  double xt,yt,xb,yb;

  if (X1 < X2){xt = X1;xb = X2;}else{xt = X2;xb = X1;}
  if (Y1 < Y2){yt = Y1;yb = Y2;}else{yt = Y2;yb = Y1;}

    for(int y = yt; y < yb;y++){
        LINE(xt,y,xb,y);
    }
}
void Window::BOX(int X1, int Y1, int X2, int Y2){
    LINE(X1,Y1,X1,Y2);
    LINE(X1,Y2,X2,Y2);
    LINE(X2,Y2,X2,Y1);
    LINE(X2,Y1,X1,Y1);
}

void Window::CIRCLE(int x, int y, float radius){
    float X1 = x + .5,Y1 =  + .5;
       for (float Angle =0;Angle < 360; Angle++){
           X1 = x + radius * _COS((int)Angle);
           Y1 = y + radius * _SIN((int)Angle);
               SET_PIXELII(X1,Y1, SCREEN->DRAW_COLOR);
       }
}
void Window::FILLED_CIRCLE(int x, int y, float radius){
    float X1 = x ,Y1 = y ;
    unsigned long color = SCREEN->DRAW_COLOR;
     for(float r = 0;r < radius;r++){
         float Theta = (360 / (8 * r));
       for (float Angle =0;Angle < 360; Angle+= Theta){
           X1 = x + r * _COS((int)(Angle));    //X1 = x + r * cos(RADIANS(Angle));
           Y1 = y + r * _SIN((int)(Angle));    //Y1 = y + r * sin(RADIANS(Angle));

           SET_PIXELII(X1,Y1, color);
       }
     }
}

void Window::LINE2(int x,int y, float Angle,int Length){
         float Xpos = x,Ypos = y; 
         unsigned long color = SCREEN->DRAW_COLOR;
     LOOP(Length){
          Xpos += _COS((int)(Angle)),
          Ypos += _SIN((int)(Angle));
          SET_PIXELII(Xpos,Ypos,color);
     }
}
void Window::LINE(int x1,int y1,int x2,int y2)
{
 int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
 dx=x2-x1; dy=y2-y1;
 dx1=abs(dx); dy1=abs(dy); //fabs
 px=2*dy1-dx1; py=2*dx1-dy1;

 long c = SCREEN->DRAW_COLOR; //RGB(155,155,55);

 if(dy1<=dx1){
      if(dx>=0){
           x=x1; y=y1;
           xe=x2;
      }else{
           x=x2; y=y2;
           xe=x1;
      }
      SET_PIXELII(x,y,c);
      for(i=0;x<xe;i++){
           x=x+1;
           if(px<0){
                px=px+2*dy1;
           }else{
            if((dx<0 && dy<0) || (dx>0 && dy>0)){
                 y=y+1;
            }else{
                 y=y-1;
            }
            px=px+2*(dy1-dx1);
           }
           SET_PIXELII(x,y,c);
      }
 }else{
  if(dy>=0){
       x=x1;
       y=y1;
       ye=y2;
  }else{
       x=x2;
       y=y2;
       ye=y1;
  }
  SET_PIXELII(x,y,c);
  for(i=0;y<ye;i++){
       y=y+1;
       if(py<=0){
             py=py+2*dx1;
       }else{
        if((dx<0 && dy<0) || (dx>0 && dy>0)){
             x=x+1;
        }else{
             x=x-1;
        }
             py=py+2*(dx1-dy1);
       }
       SET_PIXELII(x,y,c);
  }
 }
}

void Window::PRINT_FONT(char*text){
	std::cout << "ERROR YOU HAVE NOT SETUP THE PRINT FONT FUNCTION FOR SDL YET DUMBASS" << std::endl;
}
void Window::PRINT_SCREEN(char *text){
	std::cout << "ERROR YOU HAVE NOT SETUP THE PRINT FUNCTION FOR SDL YET DUMBASS" << std::endl;
return;
}


float JavidSine(float f)
{
        float twopi = 2.0f * 3.14159f;
        float divpi = 1.0f / twopi;
        float s = f * divpi;
        float x = s - (int)s;
    return 9.922029f*x*(2.0f*x*x - 3.0f*x + 1.0f);   // return y = 9.922029f*x*(2.0f*x*x - 3.0f*x + 1.0f);
}
float NEWX(float x,float dist,float angle){
		return x + dist * cos(RADIANS(angle));
}
float NEWY(float y,float dist,float angle){
		return y + dist * sin(RADIANS(angle));
}
float FindAngle(SDL_Point A, SDL_Point B) // THIS NEEDS FIXED, I dont thing its returning the correct angle but I got other shit to do right now
{
// RETURNS ANGLE IN DEGREES
    return atan2f(B.y - A.y, B.x - A.x ) * (57.2958);
}

float FAST_SQRT(float x){

    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return (1 / x);
}
bool  Is_CLICK(int X, int Y){
   if((int)(X) <= SCREEN->Mouse.Position.X + 10 && 
      (int)(X) >= SCREEN->Mouse.Position.X - 10
                    &&
      (int)(Y) <= SCREEN->Mouse.Position.Y + 10 &&
      (int)(Y) >= SCREEN->Mouse.Position.Y - 10) return true;
   return false;
}

inline 
int   MODULO(int x, int n){ return (x % n + n) % n ;}


//=========================================================================================================================================
//                               EXPERIMENTAL GUI CODE                                                                        
//=========================================================================================================================================

void Widgit::Update()
{
  
}

GUI::GUI(Window &parent)
{
    parent.SetGUI(this);
    NumberOfWidgits = 0;
    this->Parent = &parent;
}
GUI::~GUI()
{
    for_loop(count,NumberOfWidgits)
    {
        delete(Widgits[count]);
    }
}
void GUI::Update()
{
    for(auto &W: Widgits)
    {
        W->Update();
    }
}








Frame*    GUI::Make_Frame(Vec2 pos,Vec2 size)
{
    Frame *TempFrame = new Frame(pos,size);
    Widgits.push_back(TempFrame);
    NumberOfWidgits++;
    return TempFrame;
}
Button*   GUI::Make_Button(int x, int y, int height, int width)
{
    Button *PushButton = new Button(x, y , height, width);

    Widgits.push_back(PushButton);
    return PushButton;
}
TextBox*  GUI::Make_TextBox(Vec2 topleft, float width)
{
    TextBox *box = new TextBox(topleft, width);

    Widgits.push_back(box);
    return box;
}




Frame::Frame(Vec2 pos,Vec2 size)
     : Position(pos),
       Size(size)
{
}
void Frame::Update()
{
    Render();
}
void Frame::Render()
{
    SCREEN->SET_DRAW_COLOR(RGB(150,150,150));
    SCREEN->FILLED_BOX(Position.x,Position.y, 
    Position.x + Size.w, Position.y +Size.h);
}


TextBox::TextBox(Vec2 pos, float width)
{
     Position = pos;
     Size     = Vec2(width, 20);
}
void TextBox::Update()
{
    Render();
}
void TextBox::Render()
{
    SCREEN->SET_DRAW_COLOR(RGB(255,255,255));
    SCREEN->FILLED_BOX(Position.x,Position.y, 
                    Position.x + Size.w, Position.y +Size.h);
    SCREEN->SET_DRAW_COLOR(RGB(0,0,0));
    SCREEN->BOX(Position.x,Position.y, 
                    Position.x + Size.w, Position.y +Size.h);
}


Button::Button(int x, int y, float height, float width)
{
    Position = Vec2(x,y);
    Size = Vec2(width,height);
}
void Button::Update()
{
    Render();
}
void Button::Render()
{
    SCREEN->SET_DRAW_COLOR(RGB(15,15,15));
    SCREEN->FILLED_BOX(Position.x,Position.y, 
                       Position.x + Size.w, Position.y +Size.h); 
}  
            
    