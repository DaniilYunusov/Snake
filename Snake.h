#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget{

public:
    Snake(QWidget *parent = 0);


protected:
    void paintEvent   (QPaintEvent *);
    void timerEvent   (QTimerEvent *);
    void keyPressEvent(QKeyEvent   *);

private:
    QImage dot;
    QImage head;
    QImage apple;

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    static const int DOT_SIZE = 10;
    static const int ALL_DOTS = 900;
    static const int RAND_POS = 29;
    static const int DELAY = 90;

    int timerId;
    int dots;
    int apple_x;
    int apple_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;

    loadImages();
    initGame();

};
