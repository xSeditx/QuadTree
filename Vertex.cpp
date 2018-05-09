// *******Credit for Verctor classes and Matrix Code goes to Cherno and were written for his Sparky Game Engine.


#include "Vertex.h"
#include "Window.h"

//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________

//C:\Users\Curt\Documents\Visual Studio 2012\Libraries\glm-0.9.2.7\glm;
//glm::vec3  Vec3ToGlm(Vec3 vec){
//    return glm::vec3(vec.x,vec.y,vec.z);
//}
//Vec3 GlmtoVec3(glm::vec3  vec){
//    return Vec3(vec.x,vec.y,vec.z);
//}

Vec2::Vec2()
    : x(0.0f),
      y(0.0f)
{}

Vec2::Vec2(const float& X,const float& Y)
    :x(X),
     y(Y)
{}

Vec2& Vec2::add(const Vec2& other){
	x += other.x; y += other.y;
	return *this;
}
Vec2& Vec2::subtract(const Vec2& other){
	x -= other.x; y -= other.y;
	return *this;
}
Vec2& Vec2::divide(const Vec2& other){
	x /= other.x; y /= other.y;
	return *this;
}
Vec2& Vec2::multiply(const Vec2& other){
	x *= other.x; y *= other.y;
	return *this;
}


Vec2 operator +(Vec2 left, const Vec2& right){return left.add(right);}
Vec2 operator -(Vec2 left, const Vec2& right){return left.subtract(right);}
Vec2 operator /(Vec2 left, const Vec2& right){return left.divide(right);}
Vec2 operator *(Vec2 left, const Vec2& right){return left.multiply(right);}
//_____________________________________________________________________________________________________________________________________
Vec2& Vec2::operator +=(const Vec2& other){return add(other);}
Vec2& Vec2::operator -=(const Vec2& other){return subtract(other);}
Vec2& Vec2::operator *=(const Vec2& other){return multiply(other);}
Vec2& Vec2::operator /=(const Vec2& other){return divide(other);}
//_____________________________________________________________________________________________________________________________________

//_____________________________________________________________________________________________________________________________________
bool Vec2::operator ==(const Vec2& other){return x == other.x && y == other.y;}
bool Vec2::operator !=(const Vec2& other){return !(*this == other);}
//_____________________________________________________________________________________________________________________________________

std::ostream& operator<<(std::ostream& stream,const Vec2& vector){
	stream << "vec2: (" << vector.x <<") vec2: ("<< vector.y<<")";
	return stream;
}


Vec2& Vec2::operator =(const float& value){
    x = value;    y = value;
    return *this;
} // My work needs Testing
Vec2& Vec2::operator +(const float& value){
    x += value; y += value;
    return *this;
}
Vec2& Vec2::operator -(const float& value){
    x -= value;  y -= value;
    return *this;
}
Vec2& Vec2::operator *(const float& value){
    x *= value; y *= value;
    return *this;
}
Vec2& Vec2::operator /(const float& value){
    this->x /= value;
    this->y /= value;
    return *this;
}



//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________

Vec3::Vec3():
    x (0.0f),
    y (0.0f),
    z (0.0f)
{}
Vec3::Vec3(const float& X,const float& Y,const float& Z)
    :x(X),
     y(Y),
     z(Z)
{}

Vec3::Vec3(glm::vec3 other)
{
          x  = other.x;
          y  = other.y;
          z  = other.z;
}

Vec3& Vec3::add(const Vec3& other)
{
	x += other.x; y += other.y; z += other.z;
	return *this;
}
Vec3& Vec3::subtract(const Vec3& other)
{
	x -= other.x; y -= other.y;z -= other.z;
	return *this;
}
Vec3& Vec3::divide(const Vec3& other)
{
	x /= other.x; y /= other.y;z /= other.z;
	return *this;
}
Vec3& Vec3::multiply(const Vec3& other)
{
	x *= other.x; y *= other.y;z *= other.z;
	return *this;
}

Vec3 operator +(Vec3 left, const Vec3& right)
{
	return left.add(right);
}
Vec3 operator -(Vec3 left, const Vec3& right)
{
	return left.subtract(right);
}
Vec3 operator /(Vec3 left, const Vec3& right)
{
	return left.divide(right);
}
Vec3 operator *(Vec3 left, const Vec3& right)
{
	return left.multiply(right);
}

//_____________________________________________________________________________________________________________________________________
Vec3& Vec3::operator +=(const Vec3& other){return add(other);}
Vec3& Vec3::operator -=(const Vec3& other){return subtract(other);}
Vec3& Vec3::operator *=(const Vec3& other){return multiply(other);}
Vec3& Vec3::operator /=(const Vec3& other){return divide(other);}
//_____________________________________________________________________________________________________________________________________

bool Vec3::operator ==(const Vec3& other)
{
return x == other.x && y == other.y && z == other.z;
}
bool Vec3::operator !=(const Vec3& other)
{
return !(*this == other);
}

Vec3& Vec3::operator =(const float& value) {
    this->x = value;
    this->y = value;
    this->z = value;
    return *this;
} // My work needs Testing

Vec3 Vec3::operator +(const float& value) const{
    return Vec3(x + value, y + value, z + value);
}
Vec3 Vec3::operator -(const float& value) const{
    return Vec3(x - value, y - value, z - value);
}
Vec3 Vec3::operator *(const float& value) const{
    return Vec3(x * value, y * value, z * value);
}
Vec3 Vec3::operator /(const float& value) const{
    return Vec3(x / value, y / value, z / value);
}

Vec3::operator glm::vec3()
{
    glm::vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
   return v;
}

//_____________________________________________________________________________________________________________________________________

std::ostream& operator<<(std::ostream& stream,const Vec3& vector)
{
	stream << "Vec3:X (" << vector.x <<") Vec3:Y ("<< vector.y<<") Vec3:Z ("<< vector.z << ")";
		return stream;
}

Vec3  Vec3::Normalize(const Vec3 &vec){
    float magnitude = sqrt(Squared(vec.x) + Squared(vec.y) + Squared(vec.z));
    Vec3 Ret = vec;
    if (magnitude != 0)
    {
        Ret.x /= magnitude;
        Ret.y /= magnitude;
        Ret.z /= magnitude;
    }
    return Ret;
}

void  Vec3::Normalize() 
{
  float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));

    if (magnitude != 0)
    {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
}

float Vec3::GetDistance   (const Vec3 &other){
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;
    
    return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}
float Vec3::GetDistance   (const Vec3 &v1, const Vec3 &v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    
    return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}
                          
float Vec3::DotProduct    (const Vec3 &vec) const
{
            return (x * vec.x) + (y * vec.y) + (z * vec.z);
}     
float Vec3::DotProduct    (const Vec3 &vec, const Vec3 &vec2){
     return (vec.x * vec2.x) + (vec.y * vec2.y) + (vec.z * vec2.z);
}
                          
//Vec3  Vec3::CrossProduct  (const Vec3 &first, const Vec3 &other)
//{
//return Vec3(first.y * other.z - first.z * other.y, 
//            first.z * other.x - first.x * other.z,
//            first.x * other.y - first.y * other.x);
//}
Vec3  Vec3::CrossProduct  (const Vec3 &other)
{
return Vec3(y * other.z - z * other.y, 
            z * other.x - x * other.z,
            x * other.y - y * other.x);
}
Vec3  Vec3::CrossProduct  (const Vec3 &A, const Vec3 &B)
{
return Vec3(
     A.y *B.z - A.z * B.y,
     A.z *B.x - A.x * B.z,
     A.x* B.y - A.y * B.x);
}


Vec3 Vec3::GetNormal(Vec3 v1, Vec3 v2, Vec3 v3)
 {
     Vec3 Normal;
	  // Calculate vectors
	  float var1_x = v2.x - v1.x;
	  float var1_y = v2.y - v1.y;
	  float var1_z = v2.z - v1.z;
 
	  float var2_x = v3.x - v1.x;
	  float var2_y = v3.y - v1.y;
	  float var2_z = v3.z - v1.z;
 
  	// Get cross product of vectors
  	Normal.x = (var1_y * var2_z) - (var2_y * var1_z);
	Normal.y = (var1_z * var2_x) - (var2_z * var1_x);
  	Normal.z = (var1_x * var2_y) - (var2_x * var1_y);
 
	// Normalise final vector
  	float vLen = sqrt( (Normal.x * Normal.x) + (Normal.y * Normal.y) + (Normal.z * Normal.z) );
 
	Normal.x = Normal.x/vLen;
	Normal.y = Normal.y/vLen;
  	Normal.z = Normal.z/vLen;
    return Normal;
 }

//static Vec3 GetNormal(Vec3 v1, Vec3 v2, Vec3 v3)
//{
//            Vec3 D1 = v2 - v1; 
//            Vec3 D2 = v3 - v2;
//
//            Vec3 Cross = Vec3::CrossProduct  (D1, D2);
//
//            float Distance = sqrt( Squared(Cross.x) +  Squared(Cross.y) +  Squared(Cross.z));
//
//           return Vec3(Cross.x / Distance, 
//                       Cross.y / Distance, 
//                       Cross.z / Distance);
//}                                                                                  
//          





//TODO:
// THIS NEEDS TO BE REVIDE
Vec3 Vec3::RayCast(Vec3 pos, Vec3 angle, float distance)
{
    float Offset = 90;

    float  SIN_X = sin(RADIANS(angle.x  - Offset));

    return Vec3((-pos.x) - (cos(RADIANS(angle.y - Offset)) * SIN_X) * distance,
                (-pos.y) -  cos(RADIANS(angle.x - Offset)) * distance,
                (-pos.z) - (sin(RADIANS(angle.y - Offset)) * SIN_X) * distance);

}


// REVIEW THESE I BELIEVE THEM TO BE FLAWED

float Vec3::RayX(float x, float angle, float distance)
{
        return (x) - (cos(RADIANS(angle - 90)) * sin(RADIANS(angle - 90)) * distance);
}

float Vec3::RayY(float y, float angle, float distance)
{
        return (y) -  cos(RADIANS(angle - 90)) * distance;
}

float Vec3::RayZ(float z, float angle, float distance)
{
     return (z - (sin(RADIANS(angle - 90)) * sin(RADIANS(angle - 90))) * distance);
}


//--------------------------------------------------------------------------------------------------------------
//


// angle_deg = RADIANS(acos(Vec3::DotProduct(VectorA.Normalize(), VectorB.Normalize() ))
//float Vec3::Get_Angle(Vec3 A, Vec3 B)
//{
//    return acos(Vec3::DotProduct(Vec3::Normalize(A), Vec3::Normalize(B))); 
//}
//
//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________


Vec4::Vec4()
    :
    x ( 0.0f),
    y ( 0.0f),
    z ( 0.0f),
    w ( 0.0f)
{}
Vec4::Vec4(const float& X,const float& Y,const float& Z,const float& W)
    :
    x (X),
    y (Y),
    z (Z),
    w (W)
{}

Vec4& Vec4::add(const Vec4& other)
{
	x += other.x; y += other.y;z += other.z;w += other.w;
	return *this;
}
Vec4& Vec4::subtract(const Vec4& other)
{
	x -= other.x; y -= other.y;z -= other.z;w -= other.w;
	return *this;
}
Vec4& Vec4::divide(const Vec4& other)
{
	x /= other.x; y /= other.y;z /= other.z;w /= other.w;
	return *this;
}
Vec4& Vec4::multiply(const Vec4& other)
{
	x *= other.x; y *= other.y;z *= other.z;w *= other.w;
	return *this;
}


Vec4 operator +(Vec4 left, const Vec4& right)
{
	return left.add(right);
}
Vec4 operator -(Vec4 left, const Vec4& right)
{
	return left.subtract(right);
}
Vec4 operator /(Vec4 left, const Vec4& right)
{
	return left.divide(right);
}
Vec4 operator *(Vec4 left, const Vec4& right)
{
	return left.multiply(right);
}

//_____________________________________________________________________________________________________________________________________
Vec4& Vec4::operator +=(const Vec4& other){return add(other);}
Vec4& Vec4::operator -=(const Vec4& other){return subtract(other);}
Vec4& Vec4::operator *=(const Vec4& other){return multiply(other);}
Vec4& Vec4::operator /=(const Vec4& other){return divide(other);}
//_____________________________________________________________________________________________________________________________________

bool Vec4::operator ==(const Vec4& other)
{
return x == other.x && y == other.y && z == other.z && w == other.w;
}
bool Vec4::operator !=(const Vec4& other)
{
return !(*this == other);
}

//_____________________________________________________________________________________________________________________________________

std::ostream& operator<<(std::ostream& stream,const Vec4& vector)
{
	stream << "Vec4:X (" << vector.x <<") Vec4:Y ("<< vector.y<<") Vec4:Z ("<< vector.z << ") Vec4:W (" << vector.w << ")";
	return stream;
}



//_____________________________________________________________________________________________________________________________________

//__________Matrix Initializations_____________________________________________________________________________________________________

Matrix4::Matrix4()
{
    for(int i=0;i<4;i++)
		           elements[i]=0.0f;
}
Matrix4::Matrix4(float diagonal)
{
  for(int i=0;i < 4*4; i++)
		           elements[i]=0.0f;

  elements[0 + 0 * 4] = diagonal;
  elements[1 + 1 * 4] = diagonal;
  elements[2 + 2 * 4] = diagonal;
  elements[3 + 3 * 4] = diagonal;
}

Matrix4 Matrix4::Identity()
{  
	return Matrix4(1.0f);
}

//_____________________________________________________________________________________________________________________________________

Matrix4& Matrix4::Multiply(const Matrix4& other)
{
  float sum = 0.0f;
  float data[16] = {0};

 for (int row = 0;row < 4;row++){

	   for (int col= 0; col < 4; col++){
               sum = 0.0f;
		    for (int e = 0; e < 4; e++){
				 sum += elements[e + row * 4] * other.elements[col + e * 4];
			}
			data[col + row * 4] = sum;
	   }
       
 }
//Matrix4 Result;
//  for( int k=0; k<=12; k+=4){
//    for(int i=0; i<4; i++){
//        int bCount=0;
//        for (int j=0; j < 4; j++, bCount+=4){
//            Result.elements[k+i] += elements[k+j%4] * other.elements[bCount+i%4];
//        }
//    }
//}
//
//
memcpy(elements, data, 4 * 4 * sizeof(float));
return *this;
}





//_____________________________________________________________________________________________________________________________________
//__________Operator Overloads_________________________________________________________________________________________________________

 //Matrix4 operator*( Matrix4, Matrix4 const &)
 Matrix4 operator *(Matrix4 left, Matrix4 const &right)
{
	return left.Multiply(right);
}

 Matrix4& Matrix4::operator *=(const Matrix4& other){
return Multiply(other);
}

//____________________________________________________________________________________________________________________________________
//____________Matrixes________________________________________________________________________________________________________________

 Matrix4 Matrix4::Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far)
 {
 	Matrix4 result(1.0f);
 
 	result.elements[0 + 0 * 4] = 2.0f/ (Right - Left);
 	result.elements[1 + 1 * 4] = 2.0f/ (Top - Bottom);
 	result.elements[2 + 2 * 4] = 2.0f/ (Near - Far);
 
 	result.elements[0 + 3 * 4] = (Left + Right) / (Left - Right);
 	result.elements[1 + 3 * 4] = (Bottom - Top) / (Bottom - Top);
 	result.elements[2 + 3 * 4] = (Far - Near) / (Far - Near);
 
 	return result;
 }
 Matrix4 Matrix4::Perspective(float FOV,float Aspect_Ratio,float Near,float Far)
 {
 	Matrix4 result(1.0f);
 
 	float q = 1.0f / (float)tan((.5 * (3.14159 / 180.0f))*FOV);
 	float a = q / Aspect_Ratio;
 
 	float b = (Near + Far) / (Near - Far);
 	float c = (2.0f * Near * Far) / (Near - Far);
 
 	result.elements[0 + 0 * 4] = a;
 	result.elements[1 + 1 * 4] = q;
 	result.elements[2 + 2 * 4] = b;
 
 	result.elements[3 + 2 * 4] = -1.0f;
     result.elements[2 + 3 * 4] = c;
 
 	return result;
 }	   
 Matrix4 Matrix4::Rotation(float Angle,const Vec3& Axis)
 {
 	Matrix4 result(1.0f);
 
 	float r = (float)(Angle  * (3.14159 / 180.0f));
 	float c = cos(r);
 	float s = sin(r);
 	float omc = 1.0f - c;
 
 	float x = Axis.x;
 	float y = Axis.y;
 	float z = Axis.z;
 
 	result.elements[0 + 0 * 4] = x  * omc + c;
 	result.elements[1 + 0 * 4] = y * x * omc + z * s;
 	result.elements[2 + 0 * 4] = x * z * omc - y * s; 	
 
 	result.elements[0 + 1 * 4] = x * y * omc - z * s;
 	result.elements[1 + 1 * 4] = y * omc + c;
 	result.elements[2 + 1 * 4] = y * z * omc + x * s;
 
 	result.elements[0 + 2 * 4] = x * z * omc + y * s;
 	result.elements[1 + 2 * 4] = y * z * omc + x * s;
 	result.elements[2 + 2 * 4] = z * omc + c; 
 
 	return result;
 }
 Matrix4 Matrix4::Translation(const Vec3& Translation)
 {
 	Matrix4 result(1.0f);
 
 	result.elements[0 + 3 * 4] = Translation.x;
 	result.elements[1 + 3 * 4] = Translation.y;
 	result.elements[2 + 3 * 4] = Translation.z;
 
 	return result;
 }
 Matrix4 Matrix4::Scale(const Vec3& Scale)
 {
 	Matrix4 result(1.0f);
 
 	result.elements[0 + 0 * 4] = Scale.x;
 	result.elements[1 + 1 * 4] = Scale.y;
 	result.elements[2 + 2 * 4] = Scale.z;
 
 	return result;
 
 }
 

float Matrix4::Element(int posx, int posy){
    return elements[posx + 4 * posy];
}



std::ostream& operator<<(std::ostream& stream,const Matrix4& mat4){
   // for(int col = 0; col < 4; col++){
   // 	stream << "X (" << mat4.columns[col].x <<") Y ("<< mat4.columns[col].y<<") Z ("<< mat4.columns[col].z <<") W ("<<mat4.columns[col].w<<")" << std::endl;
   // }
    for(int row =0;row < 4;row++){
        for(int col=0;col < 4;col++){
    stream << "[ " << mat4.elements[row + 4 * col] << " ]" ;
        }
        std::cout << " "<< std::endl;
    }
    return stream;
}



Matrix4 LookAt(const Vec3 &eyePos, const Vec3 &centerPos, const Vec3 &upDir)
{
		Vec3 forward, side, up;
		Matrix4 m;

		forward = centerPos - eyePos;
		up = upDir;

		forward.Normalize();

		// Side = forward x up
		side = forward.CrossProduct(up);
		side.Normalize();

		// Recompute up as: up = side x forward
		up = side.CrossProduct(forward);

		m.elements[0 + 4 * 0] = side.x;
		m.elements[1 + 4 * 0] = side.y;
		m.elements[2 + 4 * 0] = side.z;

		m.elements[0 + 4 * 1] = up.x;
		m.elements[1 + 4 * 1] = up.y;
		m.elements[2 + 4 * 1] = up.z;

		m.elements[0 + 4 * 2] = -forward.x;
		m.elements[1 + 4 * 2] = -forward.y;
		m.elements[2 + 4 * 2] = -forward.z;

        
//		m = m * Matrix4::Translation(Vec3(-eyePos.x, -eyePos.y, -eyePos.z));
		return m;
}


	/**
	 * Rotate vector around three axis.
	 * @param ax Angle (in degrees) to be rotated around X-axis.
	 * @param ay Angle (in degrees) to be rotated around Y-axis.
	 * @param az Angle (in degrees) to be rotated around Z-axis.
	 */
//	void rotate(T ax, T ay, T az)
//	{
//		T a = cos(DEG2RAD(ax));
//		T b = sin(DEG2RAD(ax));
//		T c = cos(DEG2RAD(ay));
//		T d = sin(DEG2RAD(ay));
//		T e = cos(DEG2RAD(az));
//		T f = sin(DEG2RAD(az));
//		T nx = c * e * x - c * f * y + d * z;
//		T ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
//		T nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
//		x = nx;
//		y = ny;
//		z = nz;
//
//	}




