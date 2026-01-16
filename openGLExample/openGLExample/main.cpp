#include "openGLExample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyGLWidget window;
    window.show();
    window.resize(800, 600); // 창 크기 설정
    return app.exec();
}
