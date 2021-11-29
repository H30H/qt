#include "mainwindow.h"


void MainWindow::initializeGL() {
    initializeOpenGLFunctions();

//    glClearColor(0, 0, 0, 1);           // Let OpenGL clear to black
//    m_object = makeObject();            // Generate an OpenGL display list
//    glShadeModel(GL_FLAT);
//    glClear(Qt::white); // заполняем экран белым цветом
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

//    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
//    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон
}

void MainWindow::glVertex(int x, int y) {
    glVertex2d(((double)x)/size().width()*2-1, -((double)y)/size().height()*2+1);
}

void MainWindow::drawCircle(int x, int y, int r, QColor color) {
    glColor3ub(color.red(), color.green(), color.blue());

    glBegin(GL_POLYGON); // говорим, что рисовать будем прямоугольник
    // задаем вершины многоугольника

    for (int i = 0; i <= 360; i+=m_circle_delta) {
        glColor3ub(color.red(), color.green(), color.blue());
        glVertex((int)(m_circle_coords[i/m_circle_delta].first*r) + x,
                 (int)(m_circle_coords[i/m_circle_delta].second*r) + y);
    }
    glEnd();
}

void MainWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
//    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
//    glLoadIdentity();           // загрузка единичную матрицу

    //       QColor halfGreen(0, 128, 0, 255); // устанавливаем цвет квадрата

    //glColor3ub(0, 127, 0); // задаем цвет

    for (auto &i : m_elements) {
        drawCircle((int)i.m_coords.first, (int)i.m_coords.second, i.m_radius, i.m_color);
    }

/*
    int radius = 350;
    int start_x = 800;
    int start_y = 400;

    glBegin(GL_POLYGON); // говорим, что рисовать будем прямоугольник
    // задаем вершины многоугольника

    glColor3ub(127, 127, 127);
    glVertex(start_x, start_y);

    for (int i = 0; i <= 360; i+=m_circle_delta) {

        auto color = QColor::fromHsv((i + m_step)%360, 255, 255);
//        qDebug() << '{' << color.red() << ' ' << color.green() << ' ' << color.blue() << '\n';
        glColor3ub(color.red(), color.green(), color.blue());
        glVertex((int)(m_circle_coords[i/m_circle_delta].first*radius) + start_x,
                 (int)(m_circle_coords[i/m_circle_delta].second*radius) + start_y);
    }
    glEnd();
*/
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{ 
    for (int i = 0; i <= 360; i+=m_circle_delta) {
//
        m_circle_coords.push_back(std::pair(cos(M_PI*i/180), sin(M_PI*i/180)));
//        glVertex( + start_x, *radius) + start_y);
    }

    m_elements.push_back(Element(20, std::pair<int, int>(200, 200),
                                 std::pair<int, int>(15, 15), std::pair<int, int>(0, 0),
                                 QColor(QString("#ff7700"))));
    m_elements.push_back(Element(20, std::pair<int, int>(400, 400),
                                 std::pair<int, int>(10, 20), std::pair<int, int>(0, 0),
                                 QColor(QString("#7700ff"))));
    m_elements.push_back(Element(20, std::pair<int, int>(300, 300),
                                 std::pair<int, int>(-19, 8), std::pair<int, int>(0, 0),
                                 QColor(QString("#00ff00"))));
    m_elements.push_back(Element(20, std::pair<int, int>(200, 400),
                                 std::pair<int, int>(17, -4), std::pair<int, int>(0, 0),
                                 QColor(QString("#ff0055"))));
    m_elements.push_back(Element(20, std::pair<int, int>(400, 200),
                                 std::pair<int, int>(3, 27), std::pair<int, int>(0, 0),
                                 QColor(QString("#00ffff"))));
    m_elements.push_back(Element(20, std::pair<int, int>(200, 300),
                                 std::pair<int, int>(17, 27), std::pair<int, int>(0, 0),
                                 QColor(QString("#777777"))));
}

MainWindow::~MainWindow()
{
}

myTimer::myTimer(): _time(clock_t::now()) {}

myTimer::myTimer(const myTimer& timer) = default;

void myTimer::reset() {
    _time = clock_t::now();
}

double myTimer::time() {
    return std::chrono::duration_cast<second_t>(clock_t::now() - _time).count();
}
