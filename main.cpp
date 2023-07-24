#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QSoundEffect>

class ColorfulCircle : public QWidget
{
Q_OBJECT
public:
    ColorfulCircle(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QColor calculateColor();

    QColor mColor = Qt::green;
    QSoundEffect mSoundEffect;
};

ColorfulCircle::ColorfulCircle(QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(200, 250);
    mSoundEffect.setSource(QUrl::fromLocalFile("/Users/gasoline/Downloads/DL6NBR8-funny-jumper.wav"));
}

void ColorfulCircle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int circleSize = qMin(width(), height()) - 20;
    int xOffset = (width() - circleSize) / 2;
    int yOffset = (height() - circleSize) / 2;
    QRect circleRect(xOffset, yOffset, circleSize, circleSize);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(mColor);
    painter.drawEllipse(circleRect);
}

void ColorfulCircle::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mColor = calculateColor();
    mSoundEffect.play();
    update();
}

QColor ColorfulCircle::calculateColor()
{
    if (mColor == Qt::green)
        return Qt::yellow;
    else if (mColor == Qt::yellow)
        return Qt::red;
    else
        return Qt::green;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(300, 350);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    ColorfulCircle *circle = new ColorfulCircle(&window); // Specify the parent widget
    layout->addWidget(circle);

    window.show();

    return app.exec();
}

#include "main.moc"
