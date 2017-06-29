#ifndef IMAGEHANDLINGFORM_H
#define IMAGEHANDLINGFORM_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
class ImageHandlingForm;
}

class ImageHandlingForm : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ImageHandlingForm(QWidget *parent = 0);
    ~ImageHandlingForm();

public slots:
    void slotLoadImage(QImage &image, int timems);

private:
    Ui::ImageHandlingForm *ui;
    double zoom;
//    QGraphicsScene *picscene;

    void clearScene();

};

#endif // IMAGEHANDLINGFORM_H
