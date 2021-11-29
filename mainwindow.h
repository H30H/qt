#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtOpenGL/QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_1_1>
//#include <QAxBindable>
#include <cmath>
#include <QTimer>
#include <vector>
#include <element.h>

#include <chrono>

class myTimer {
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> _time;
public:
    myTimer();

    myTimer(const myTimer& timer);

    void reset();

    double time();
};

class MainWindow : public QOpenGLWidget,
                   public QOpenGLFunctions_1_1
//                   public QAxBindable
{
    Q_OBJECT

    GLuint m_object = 0;
    QWidget* QMainWindow;
    int m_step = 0;

    int m_circle_delta = 1;
    std::vector<std::pair<float, float>> m_circle_coords;

    double m_simulate_speed = 15;
    int m_accuracy = 1;
    myTimer m_frame_speed;

    std::vector<Element> m_elements;

    double getDist(std::pair<float, float>coords_1, std::pair<float, float>coords_2) {
        return sqrtf(powf(coords_1.first - coords_2.first, 2) + powf(coords_1.second - coords_2.second, 2));
    }

    bool conflicts(const std::vector<std::pair<int, std::pair<float, float>>>& coords) {
        bool res = false;
        for (size_t i = 0; i < coords.size(); i++) {
            for (size_t j = i + 1; j < coords.size(); j++) {
                const auto &coord1 = coords[i], &coord2 = coords[j];
                if (pow(coord1.first + coord2.first, 2) >
                        pow(coord1.second.first - coord2.second.first, 2) +
                        pow(coord1.second.second - coord2.second.second, 2)) {
                    res = true;
                    std::swap(m_elements[i].m_velocity, m_elements[j].m_velocity);
                }
            }
        }
        return res;
    }

    std::pair<int, std::pair<float, float>> calculateElementCoords(Element& element, double time = 1, int accuracy = 1) {
        float coord_x = element.m_coords.first + element.m_velocity.first*m_simulate_speed*time/accuracy;
        if (coord_x < element.m_radius) {
            coord_x = element.m_radius*2 - coord_x;
            element.m_velocity.first *= -1;
        }

        else if (coord_x >= size().width() - element.m_radius) {
            coord_x = 2*(size().width() - element.m_radius) - coord_x;
            element.m_velocity.first *= -1;
        }

        float coord_y = element.m_coords.second + element.m_velocity.second*m_simulate_speed*time/accuracy;
        if (coord_y < element.m_radius) {
            coord_y = element.m_radius*2 - coord_y;
            element.m_velocity.second *= -1;
        }
        else if (coord_y >= size().height() - element.m_radius) {
            coord_y = 2*(size().height() - element.m_radius) - coord_y;
            element.m_velocity.second *= -1;
        }
        return {element.m_radius, {coord_x, coord_y}};
    }


protected:
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override {
        glViewport(0, 0, nWidth, nHeight); // установка точки обзора
        glMatrixMode(GL_PROJECTION); // установка режима матрицы
        glLoadIdentity(); // загрузка матрицы
    }
    void paintGL() override;
    void glVertex(int x, int y);
    void drawCircle(int x, int y, int r, QColor color = QColor(QString("#000000")));
public slots:
    void animate() {
        m_step+=1;
        auto frame_time = m_frame_speed.time();
        m_frame_speed.reset();//size().width() << size().height() << coord_x << coord_y;
        if (m_step >= 10) {
            m_step = 0;
            qDebug() << frame_time*1000;
        }

        for (int j = 0; j < m_accuracy; j++) {
            std::vector<std::pair<int, std::pair<float, float>>> coords(m_elements.size());

            do {
                for (size_t i = 0; i < m_elements.size(); i++) {
                    coords[i] = calculateElementCoords(m_elements[i], frame_time, m_accuracy);
                }
            } while(conflicts(coords));

            for (size_t i = 0; i < m_elements.size(); i++) {
                m_elements[i].m_coords = coords[i].second;
            }
        }
        update();

    }
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resetSimulateSpeed(double new_speed) {
        m_simulate_speed = new_speed;
    }

    void resetAccuracy(int new_accuracy) {
        m_accuracy = new_accuracy;
    }

    void startAnimation() {

    }
};
#endif // MAINWINDOW_H
