#include"Window.h"
#include"Vertex.h"
#include"QuadTree.h"




void MouseClick(int mX, int mY)
{
    Particle *P = new Particle(Vec2((float)mX,(float)mY));
}


void main()
{
    Window MainWindow(0,0,1280,940,"QuadTree Particle Test");
    MainWindow.CallBacks.SetOnLButtonDown(MouseClick);
    MainWindow.CallBacks.SetOnLButtonUp(MouseClick);
    for_loop(Index,1000)
    {
        Particle *Part = new Particle(Vec2(rand()%1280, rand()%940));
    }
    QT Tree = QT(Vec2(1280/2,940/2),Vec2(1280/2,940/2));
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