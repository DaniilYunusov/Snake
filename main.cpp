#include <QApplication>
#include <QIcon>
#include "Snake.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Snake window;

  window.setWindowTitle("Snake");
  window.show();
  window.setWindowIcon(QIcon("snake.png"));

  return app.exec();
}
