#include"Window.h"
#include"Vertex.h"
#include"QuadTree.h"

QT Tree = QT(Vec2(1280/2,940/2),Vec2(1280/2,940/2));
float QX= 0,QY =0;

void MouseClick(int mX, int mY)
{
    Particle *P = new Particle(Vec2((float)mX,(float)mY));
}

void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    QX = mX;
    QY = mY;
}


std::vector<Particle*> results;
void main()
{
    Window MainWindow(0,0,1280,940,"QuadTree Particle Test");
    MainWindow.CallBacks.SetOnLButtonDown(MouseClick);
    MainWindow.CallBacks.SetOnLButtonUp(MouseClick);
    MainWindow.CallBacks.SetOnMouseMove(MouseMove);
    for_loop(Index,1000)
    {
        Particle *Part = new Particle(Vec2(rand()%1280, rand()%940));
    }

    Tree.Init();

    while(MainWindow.LOOP_GAME())
    {
        MainWindow.CLS();
     for_loop(Index, Particle::ParticleCount)
     {
         Particle::ParticleList[Index]->Position.x += RANDOM(6) - 3;
         Particle::ParticleList[Index]->Position.y += RANDOM(6) - 3;
         Particle::ParticleList[Index]->ClampPosition();

     }

        Tree.Update();
      std::vector<Particle*>  results = Tree.RootNode->QueryRange(Vec2(QX,QY),Vec2(100,100));
        for(Particle *P: results)
        {
            SCREEN->CIRCLE(P->Position.x,P->Position.y,3);
        }
           Tree.RootNode->Render();
           Particle::RenderAll();
               //Particle *P = new Particle(Vec2(1280/2,940/2));
        MainWindow.SYNC();
        Print(SCREEN->FPS);
    }

    for_loop(Index, Particle::ParticleCount)
    {
         delete(Particle::ParticleList[Index]);
    }
  
}