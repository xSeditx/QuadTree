#include"QuadTree.h"
#include"Window.h"


int Particle::ParticleCount = 0;
std::vector<Particle *> Particle::ParticleList; 

Particle::~Particle()
{
//    free;
}


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


void Particle::ClampPosition()
{
    if(Position.x < 0)    Position.x += 1281;
    if(Position.x > 1280) Position.x -= 1280;
    if(Position.y < 0)    Position.y += 940;
    if(Position.y > 940)  Position.y -= 940;    
}


Node::~Node()
{
}
Node::Node(Vec2 pos, Vec2 size)
    : Position(pos),
      Size(size),
      Capacity(10),
      IsLeaf(true),
      Facing(NE)
{
    SubNodes[NW] =
    SubNodes[NE] =
    SubNodes[SW] =
    SubNodes[SE] = nullptr;
    Entities.reserve(40);
}


void  Node::Subdivide()
{
    for_loop(Index, 4)
    {
        SubNodes[Index] = new  Node( NewPos(Position, (Direction)Index), Vec2( Size.x * 0.5f, 
                                                                               Size.y * 0.5f));
        SubNodes[Index]->Facing = (Direction)Index;
    }
}

bool  Node::Insert(Particle *object)
{
    if(IsContained(object))               // If the Object Fits in this Square
    {
        if(IsLeaf == true)                // And its a Leaf Node
        {
            if(Entities.size() < Capacity)     // And the Capacity of the Square is not full 
            {
                Entities.push_back(object);   // Than add this Object to the Current Object list and exit the function
                return true;
            }
            else                       // Else If its full than make the Node a Branch
            {
                IsLeaf = false;  
                Subdivide();           // And Subdivide it

                for(Particle *object: Entities)  // Put the Particles that were in this Node in their respective SubNodes
                {
                   PushDown(object);
                }
            
                Entities.clear();             // And Delete the particles from this Now branch node
                if(SubNodes[NE]->Insert(object) == true) return true; // Attempt to place the Particle in one of the newly
                if(SubNodes[SE]->Insert(object) == true) return true; // Created Subnodes
                if(SubNodes[NW]->Insert(object) == true) return true; 
                if(SubNodes[SW]->Insert(object) == true) return true;
                
            }
        }
        else                        // If this node is a Branch and not a leaf than try the Subnodes and see if any of them are leaves
        {
            if(SubNodes[NE]->Insert(object) == true) return true;
            if(SubNodes[SE]->Insert(object) == true) return true;
            if(SubNodes[NW]->Insert(object) == true) return true;
            if(SubNodes[SW]->Insert(object) == true) return true;
        }
    }
    else   // Finally if the Particle is not in this quadrent at all just return false
    {      // This is done for completeness as it would fall through to a false return anyway by default
        return false;
    }
  return false;
}


bool  Node::IsContained(Particle *object){
    return( object->Position.x >= (Position.x - Size.x) && object->Position.x <= (Position.x + Size.x) &&
            object->Position.y >= (Position.y - Size.y) && object->Position.y <= (Position.y + Size.y));
}


bool  Node::PushDown(Particle *object)
{
    if(SubNodes[NE]->Insert(object) == true) return true;
    if(SubNodes[SE]->Insert(object) == true) return true;
    if(SubNodes[NW]->Insert(object) == true) return true;
    if(SubNodes[SW]->Insert(object) == true) return true;
  return false;
}


void  Node::Moveup(Particle *Object)
{
// Needs work and possibly is not needed at all
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
            delete node->SubNodes[i];
            *node->SubNodes = nullptr;
        }

           
        node->IsLeaf =true;
        //node->Entities.empty();
    }

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



QT::QT(Vec2 position, Vec2 size)
  : Position(position),
    Size(size)
{
}


void QT::Init()
{
    RootNode = new Node(Position,Size);
    for_loop(Index, Particle::ParticleCount)
    {
        RootNode->Insert(Particle::ParticleList[Index]);
    }
}


void QT::Update()
{
    RootNode->Prune(RootNode);

     for_loop(Index, Particle::ParticleCount)
     {
         RootNode->Insert(Particle::ParticleList[Index]);
     }
 }


bool  Node::Intersects(Vec2 position, Vec2 size)
{
   return !(position.x - size.x > Position.x + Size.x ||
            position.x + size.x < Position.x - Size.x ||
            position.y - size.y > Position.y + Size.y ||
            position.y + size.y < Position.y - Size.y);
            
}


std::vector<Particle*> Node::QueryRange(Vec2 position, Vec2 size)
{

std::vector<Particle *> results;

    if (!(Intersects(position,size)))
    {
        return results; 
    }
    for_loop (Index, Entities.size())
    {
        if (IsContained(Entities[Index]))
        {
             results.push_back(Entities[Index]);
        }
    }

    if (IsLeaf == true)
    {
        return results;
    }
    
    for_loop(SubIndex, 4)
    {
       std::vector<Particle*> S; 
       S = SubNodes[SubIndex]->QueryRange(position,size);
       if (S.size() > 0) 
       {
          results.insert(results.end(), S.begin(), S.end());
       }
    }

    SCREEN->SET_DRAW_COLOR(RGB(0,255,0));
    SCREEN->BOX(position.x - size.x, position.y - size.y,
                position.x + size.x, position.y + size.y);

return results;
}
