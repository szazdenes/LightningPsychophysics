#include "imagehandlingform.h"
#include "ui_imagehandlingform.h"

ImageHandlingForm::ImageHandlingForm(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::ImageHandlingForm)
{
    ui->setupUi(this);
    zoom = 1;
}

ImageHandlingForm::~ImageHandlingForm()
{
    delete ui;
}

void ImageHandlingForm::slotLoadImage(QImage &image, int timems)
{
    QGraphicsScene *scene = new QGraphicsScene();
    this->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(image));

    this->scale(1.0/zoom, 1.0/zoom);
    QRectF imageRect = (QRectF)image.rect();
    QRectF rect = this->viewport()->rect();
    double fitSize = qMin<double>(rect.width() / imageRect.width(), rect.height() / imageRect.height());
    this->scale(fitSize, fitSize);
    zoom = fitSize;

    QTimer::singleShot(timems, this, &ImageHandlingForm::clearScene);
}

void ImageHandlingForm::clearScene()
{
    this->scene()->clear();
}
