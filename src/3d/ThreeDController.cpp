#include "ThreeDController.h"
#include "Vector2.h"

#include <iostream>
#include "Utils.h"

using namespace Fakarava3d;
using namespace Eigen;

ThreeDController::ThreeDController(point3D position, float width, float height, float focal, float screenWidth, float screenHeight,
                                   drawPointFunction drawPoint, drawLineFunction drawLine, drawTriangleFunction drawTriangle, drawPixelFunction drawPixel) : camera(Vector3f(position.x, position.y, position.z), Matrix3f::Identity(),
                                                                                                                                       width, height, focal, screenWidth, screenHeight),
                                                                                                                                drawLine(drawLine), drawPoint(drawPoint), drawTriangle(drawTriangle), drawPixel(drawPixel),
                                                                                                                                rend(camera, screenWidth, screenHeight)
{
}


Camera &ThreeDController::getCamera()
{
    return camera;
}

void ThreeDController::drawMesh(const Mesh &mesh, char drawFlags)
{

    rend.queueRender(&mesh);
}

void ThreeDController::flushDrawings()
{
    for(std::array<Eigen::Vector3f, 3>& triangle : rend.render())
    {
        drawTriangle(
            Vector2<float>(triangle[0][0], triangle[0][1]),
            Vector2<float>(triangle[1][0], triangle[1][1]),
            Vector2<float>(triangle[2][0], triangle[2][1]),
            rgba({128, 128, 255, 200})
        );
    }
}

