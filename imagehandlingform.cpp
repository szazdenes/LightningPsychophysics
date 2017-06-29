#include "imagehandlingform.h"
#include "ui_imagehandlingform.h"

ImageHandlingForm::ImageHandlingForm(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::ImageHandlingForm)
{
    ui->setupUi(this);
//    zoom = 1;

    picscene = new QGraphicsScene();
    this->setScene(picscene);
    this->setBackgroundBrush(Qt::black);
}

ImageHandlingForm::~ImageHandlingForm()
{
    delete picscene;
    delete ui;
}

void ImageHandlingForm::slotLoadImage(QImage &image, int timems)
{
    picscene->addPixmap(QPixmap::fromImage(image));

    this->setMatrix(QMatrix());
//    this->scale(1.0/zoom, 1.0/zoom);
    QRectF imageRect = (QRectF)image.rect();
    QRectF rect = this->viewport()->rect();
    double fitSize = qMin<double>(rect.width() / imageRect.width(), rect.height() / imageRect.height());
    this->scale(fitSize, fitSize);
//    zoom = fitSize;

    QTimer::singleShot(timems, this, &ImageHandlingForm::clearScene);
}

void ImageHandlingForm::clearScene()
{
    this->scene()->clear();
}
