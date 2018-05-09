#include"QuadTree.h"
#include"Window.h"


int Particle::ParticleCount = 0;
std::vector<Particle *> Particle::ParticleList; 


Particle::Particle(Vec2 pos)
        : Position(pos),
          Speed(0),
          Angle(0),
          ID(ParticleCount++)
{
    ParticleList.push_back(this);
}
void Particle::Render()
{
    SCREEN->SET_PIXEL(Position.x,Position.y, 0xFF0000);
}
void Particle::RenderAll()
{
     for_loop(Index, Particle::ParticleCount)
     {
         Particle::ParticleList[Index]->Render();
     }
}





Node::~Node()
{
    if(IsLeaf != true)
    {
        if ( this->SubNodes[NW] != NULL ) delete this->SubNodes[NW];
        if ( this->SubNodes[NE] != NULL ) delete this->SubNodes[NE];
        if ( this->SubNodes[SW] != NULL ) delete this->SubNodes[SW];
        if ( this->SubNodes[SE] != NULL ) delete this->SubNodes[SE];
    }
}


Node::Node(Vec2 pos, Vec2 size)
    : Position(pos),
      Size(size),
      Capacity(10),
      IsLeaf(true),
      Facing(NE)
{
    SubNodes[0] =SubNodes[1] =SubNodes[2] =SubNodes[3] = nullptr;
    Entities.reserve(6);
}

void  Node::Subdivide()
{
    for_loop(Index,4)
    {
        SubNodes[Index] = new Node(NewPos( Position, (Direction)Index), Vec2(Size.x * 0.5f,Size.y * .5));
        SubNodes[Index]->Facing = (Direction)Index;
    }


}

bool  Node::Insert(Particle &object){
    if(IsContained(&object))
    {
        if(Entities.size() < Capacity)
        {
            Entities.push_back(object);
            return true;
        }
        else
        {
            if(IsLeaf == true)Subdivide();
           
            for(Particle &object: Entities)
            {
               if(SubNodes[NE]->Insert(object) == true) continue;
               if(SubNodes[SE]->Insert(object) == true) continue;
               if(SubNodes[NW]->Insert(object) == true) continue;
               if(SubNodes[SW]->Insert(object) == true) continue;
            }


            Entities.clear();
             IsLeaf = false;
            if(SubNodes[NE]->Insert(object) == true) return true;
            if(SubNodes[SE]->Insert(object) == true) return true;
            if(SubNodes[NW]->Insert(object) == true) return true;
            if(SubNodes[SW]->Insert(object) == true) return true;
            
        }
    }
    else
    {
        return false;
    }

return false;
}

bool  Node::IsContained(Particle *object){
    return( object->Position.x >= (Position.x - Size.x) && object->Position.x <= (Position.x + Size.x) &&
            object->Position.y >= (Position.y - Size.y) && object->Position.y <= (Position.y + Size.y));
}

Vec2  Node::NewPos(Vec2 pos, Direction direction){
    Vec2 NewPos = pos;
    if(direction == NE)
    {
        NewPos.x += (Size.x * .5);
        NewPos.y -= (Size.y * .5);
    }                     
    if(direction == SE)   
    {                     
        NewPos.x += (Size.x * .5);
        NewPos.y += (Size.y * .5);
    }                      
    if(direction == NW)   
    {                     
        NewPos.x -= (Size.x * .5);
        NewPos.y -= (Size.y * .5);
    }                     
    if(direction == SW)   
    {                     
        NewPos.x -= (Size.x * .5);
        NewPos.y += (Size.y * .5);
    }
    return NewPos;
}



void  Node::Render(){
    float X1 = (Position.x - (Size.x ));
    float Y1 = (Position.y - (Size.y ));
    float X2 = (Position.x + (Size.x ));
    float Y2 = (Position.y + (Size.y ));

  // if(Facing == NE) SCREEN->SET_DRAW_COLOR(RGB(255,0,0));
  // if(Facing == NW) SCREEN->SET_DRAW_COLOR(RGB(0,255,0));
  // if(Facing == SW) SCREEN->SET_DRAW_COLOR(RGB(0,0,255));
   // if(Facing == SE) 
    SCREEN->SET_DRAW_COLOR(RGB(255,255,255));


   // SCREEN->LINE(Position.x, Y1, Position.x , Y2);
   // SCREEN->LINE(X1, Position.y, X2,  Position.y);
    SCREEN->BOX(X1,Y1,X2,Y2);

    if(IsLeaf == false)
    {
        for_loop(Index,4)
        {
            SubNodes[Index]->Render();
        }
    }
}



QT::QT(Vec2 position, Vec2 size)
    :Position(position),
     Size(size)
{
}

 void QT::Init()
 {
     RootNode = new Node(Position,Size);
     for_loop(Index, Particle::ParticleCount)
     {
         RootNode->Insert(*Particle::ParticleList[Index]);
     }
 }

void QT::Update()
 {
    RootNode->Prune(RootNode);

     for_loop(Index, Particle::ParticleCount)
     {
         RootNode->Insert(*Particle::ParticleList[Index]);
     }
 }

void  Node::Prune (Node *node)
{
    if( node != nullptr )
    {
        for_loop( i, 4 )
        {
            if(node->IsLeaf == false)
            {
                Prune(node->SubNodes[i]);
            }
            node->SubNodes[i] = nullptr;
        }
            node->IsLeaf =true;
            node->Entities.empty();
    }
}





  //  bool containsX = boundary.x0 <= data.latitude && data.latitude <= boundary.x1;
  //  bool containsY = boundary.y0 <= data.longitude && data.longitude <= boundary.y1;
  //  
  //  return containsX && containsY;