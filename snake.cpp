#include <QPainter>
#include <QApplication>
#include <QTime>
#include "Snake.h"
#include <QProcess>

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

void Snake::initGame() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();

    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {

        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/3));
    qp.drawText(-textWidth/2, 0, message);


    QString message2 = "To play again click 'r'";
    QFont font2("Courier", 10, QFont::DemiBold);
    QFontMetrics fm2(font2);
    int textWidth2 = fm.width(message2);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font2);
    int h2 = height();
    int w2 = width();

    qp.translate(QPoint(w2/1.25, h2/3));
    qp.drawText(-textWidth2, 0, message2);


    QString message3 = "Press 'ESC' to exit";
    QFont font3("Courier", 10, QFont::DemiBold);
    QFontMetrics fm3(font3);
    int textWidth3 = fm.width(message3);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font3);
    int h3 = height();
    int w3 = width();

    qp.translate(QPoint(w3/4, h3/5));
    qp.drawText(-textWidth3*1.4, 0, message3);
}




void Snake::checkApple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        locateApple();
    }
}

void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {

    for (int z = dots; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::locateApple() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {

        checkApple();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if (((key == Qt::Key_Left) || (key == Qt::Key_A)) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if (((key == Qt::Key_Right) || (key == Qt::Key_D)) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if (((key == Qt::Key_Up) || (key == Qt::Key_W)) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if (((key == Qt::Key_Down) || (key == Qt::Key_S))&& (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Escape) && (inGame == false)){
        QWidget::close();
    }

    if ((key == Qt::Key_R) && (inGame == false)){
        QProcess process;
        process.startDetached("Snake",QStringList());

        qApp->quit();
    }


    QWidget::keyPressEvent(e);
}
