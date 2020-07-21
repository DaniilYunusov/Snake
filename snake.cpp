#include <QPainter>
#include <QTime>
#include "Snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);

    loadImages();
    initGame();
}

void Snake::loadImages() {

    dot.load("dot.png");
    head.load("head.png");
    apple.load("apple.png");
}
