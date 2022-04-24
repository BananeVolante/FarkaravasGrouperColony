#include "Camera.h"
#include <iostream>

using namespace Fakarava3d;
using namespace Eigen;

Camera::Camera(Vector3f position,  Matrix3f rotMat, float width, float height, float focal, float screenWidth, float screenHeight) : ThreeDObj(position, {1,1,1}, rotMat), width(width), height(height), focal(focal)
{


    float k = screenWidth/width; 
    float l = -screenHeight/height; 
    float alpha = focal*k; 
    float beta = focal*l; 
    float cx = screenWidth/2;
    float cy = screenHeight/2;
   cameraMatrix << alpha, 0, cx, 0, beta, cy, 0, 0, 1;
    updateExtrisincParam();

}


float Camera::getWidth() const
{return width;}

float Camera::getHeight() const
{return height;}


Vector2f Camera::project(const Vector3f& p) const
{

    Vector4f pHomogenousCoordinates(p[0], p[1], p[2], 1);
    Vector3f tmp = M * pHomogenousCoordinates;

    return Vector2f(tmp[0]/tmp[2], tmp[1]/tmp[2]);
}


void Camera::updateExtrisincParam()
{
    const Matrix3f& rotationMatrix = getRotation();
    extrisincParam <<rotationMatrix(0,0), rotationMatrix(0,1), rotationMatrix(0,2), -getPosition()[0], rotationMatrix(1,0), rotationMatrix(1,1), rotationMatrix(1,2), -getPosition()[1], rotationMatrix(2,0), rotationMatrix(2,1), rotationMatrix(2,2), -getPosition()[2];
    M = cameraMatrix*extrisincParam;
}

void Camera::setRotation(const Matrix3f& newMat)
{
    ThreeDObj::setRotation(newMat);
    updateExtrisincParam();
}

void Camera::setPosition(const Vector3f& newPos)
{
    ThreeDObj::setPosition(newPos);
    updateExtrisincParam();
}

void Camera::rotate(const AngleAxisf& rotation)
{
    setRotation(rotation.toRotationMatrix() * getRotation());
}

