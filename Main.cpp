#include <Common/Structs.h>
#include <Geometry/Point.h>
#include <Game/Game.h>

#include <GL/glut.h>

namespace MAIN
{
    void drawText(const std::string& i_text,
                  double i_xCoordinate, double i_yCoordinate)
    {
        glColor3d(0, 0, 0);
        glRasterPos2d(i_xCoordinate, i_yCoordinate);
        for (auto chr : i_text)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, static_cast<int>(chr));
    }


    #define COUNT_VERTICES 32
    #define RADIUS_NECKLACE 0.8
    #define RADIUS_BEAD 0.05
    const int Timer = 50;
    const double ColorRanges[] = { 0.2, 0.8 };
    const double LengthColorRanges = (ColorRanges[1] - ColorRanges[0]);
    const int Width = 1000, Height = 1000;
    int size = 2;
    NGame::Game game{};
    std::array<NGeometry::Point3, NGame::EGP_BEADS_COUNT> colors;
    void keyboardFunc(int i_key, int i_x, int i_y)
    {
        switch(i_key)
        {
            case GLUT_KEY_F2:
                size = 2;
                break;
            case GLUT_KEY_F3:
                size = 3;
                break;
            case GLUT_KEY_F4:
                size = 4;
                break;
            case GLUT_KEY_F6:
                size = 6;
                break;
            case GLUT_KEY_F12:
                size = 12;
                break;
            case GLUT_KEY_LEFT:
                game.rotateCycleBySize(size, NGame::EDirection::ED_LEFT);
                break;
            case GLUT_KEY_RIGHT:
                game.rotateCycleBySize(size, NGame::EDirection::ED_RIGHT);
                break;
            case GLUT_KEY_UP:
                game.shiftCycleBySize(size, NGame::EDirection::ED_LEFT);
                break;
            case GLUT_KEY_DOWN:
                game.shiftCycleBySize(size, NGame::EDirection::ED_RIGHT);
                break;
        }
    }
    void drawCircle(const NGeometry::Point2& i_center, const NGeometry::Point3& i_color,
                    double i_radius, bool i_fill, int i_id)
    {
        if (i_fill)
            glBegin(GL_POLYGON);
        else
            glBegin(GL_LINE_LOOP);
        glColor3d(i_color[0], i_color[1], i_color[2]);
        double angle = M_PI * 2. / COUNT_VERTICES;
        for (int i = 0; i <= COUNT_VERTICES; ++i)
        {
            auto vertex = NGeometry::Point2(std::vector<double>{
                                            cos(angle * i) * i_radius,
                                            sin(angle * i) * i_radius}) + i_center;
            glVertex2d(vertex[0], vertex[1]);
        }
        glEnd();
        drawText(std::to_string(i_id + 1), i_center[0], i_center[1]);
    }
    void drawCycle(const NGame::Cycle& i_cycle, const NGeometry::Point3& i_color)
    {
        glBegin(GL_LINE_LOOP);
        glColor3d(i_color[0], i_color[1], i_color[2]);
        for (int i = 0, pos = i_cycle.getBegin(); i < i_cycle.getSize();
            ++i, pos = i_cycle.next(pos))
        {
            auto vertex = NGame::Bead::calculatePosition(pos, RADIUS_NECKLACE);
            glVertex2d(vertex[0], vertex[1]);
        }
        glEnd();
    }
    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        static const std::vector<NGeometry::Point3> cycleColors{
            NGeometry::Point3(std::vector<double>{ 1, 1, 0 }),
            NGeometry::Point3(std::vector<double>{ 1, 0, 0 }),
            NGeometry::Point3(std::vector<double>{ 0, 1, 0 }),
            NGeometry::Point3(std::vector<double>{ 0, 0, 1 }),
            NGeometry::Point3(std::vector<double>{ 0, 1, 1 }),
        };
        int cycleId = 0;
        for (auto it = game.beginCycle(); it != game.endCycle(); ++it)
        {
            if ((*it)->getSize() == size)
                drawCycle(**it, NGeometry::Point3(std::vector<double>{1, 1, 1})
                          /*cycleColors[cycleId]*/);
            cycleId++;
        }
        for (int i = 0; i < NGame::EGP_BEADS_COUNT; ++i)
        {
            const auto& center = NGame::Bead::calculatePosition(i, RADIUS_NECKLACE);
            auto circleNumber = game.getNecklace()[i].getNumber();
            const auto& color = colors[circleNumber];
            drawCircle(center, color, RADIUS_BEAD, 1, circleNumber);
        }
        glutSwapBuffers();
    }
    void timer(int)
    {
        draw();
        glutTimerFunc(Timer, timer, 0);
    }
}

using namespace MAIN;

int main(int argc, char** argv)
{
    const int CountActions = 125;
    for (int i = 0; i < NGame::EGP_BEADS_COUNT; ++i)
    {
        colors[i] = NGeometry::Point3(std::vector<double>{
            std::Random::randomDouble(0.5, 1.),
            std::Random::randomDouble(0.5, 1.),
            std::Random::randomDouble(0.5, 1.)});
    }
    static int buttons[] = {
        GLUT_KEY_F2,
        GLUT_KEY_F3,
        GLUT_KEY_F4,
        GLUT_KEY_F6,
        GLUT_KEY_F12,
        GLUT_KEY_LEFT,
        GLUT_KEY_RIGHT,
        GLUT_KEY_UP,
        GLUT_KEY_DOWN,
    };
    for (int i = 0; i < CountActions; ++i)
    {
        keyboardFunc(buttons[std::Random::randomInt(0, 5)], 0, 0);
        keyboardFunc(buttons[std::Random::randomInt(5, 9)], 0, 0);
    }
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(Width,Height);
	glutCreateWindow("Game");
 
    glutSpecialFunc(keyboardFunc);
	glutDisplayFunc(draw);
    glutTimerFunc(Timer, timer, 0);

	glutMainLoop();
    return 0;
}