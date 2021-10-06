#include "qimageviewregionwidget.h"

QImageViewRegionWidget::QImageViewRegionWidget(QWidget *parent) : QWidget(parent)
{
    background_color_.setRgb(60, 30, 30);
    image_scale_ = 100;

    connect(this, SIGNAL(backgroundColorChanged()), SLOT(repaint()));
    connect(this, SIGNAL(imageChanged()), SLOT(repaint()));

    key_ctrl_plus_ = new QShortcut(this);
    key_ctrl_plus_->setKey(Qt::CTRL | Qt::Key_Plus);
    connect(key_ctrl_plus_, SIGNAL(activated()), this, SLOT(slotZoomIn()));

    key_ctrl_minus_ = new QShortcut(this);
    key_ctrl_minus_->setKey(Qt::CTRL | Qt::Key_Minus);
    connect(key_ctrl_minus_, SIGNAL(activated()), this, SLOT(slotZoomOut()));

    key_ctrl_asterisk_ = new QShortcut(this);
    key_ctrl_asterisk_->setKey(Qt::CTRL | Qt::Key_Asterisk);
    connect(key_ctrl_asterisk_, SIGNAL(activated()), this, SLOT(slotZoomDefault()));
}

const QString &QImageViewRegionWidget::image_file_name() const
{
    return image_file_name_;
}

void QImageViewRegionWidget::setImage_file_name(const QString &newImage_file_name)
{
    image_file_name_ = newImage_file_name;
    emit imageFileNameChanged(newImage_file_name);
}

int QImageViewRegionWidget::image_scale() const
{
    delete key_ctrl_plus_;
    delete key_ctrl_minus_;
    delete key_ctrl_asterisk_;

    return image_scale_;
}

void QImageViewRegionWidget::setImage_scale(int newImage_scale)
{
    image_scale_ = newImage_scale;
    emit imageScaleChanged();
}

void QImageViewRegionWidget::setImage_actual_rect(const int scale)
{
    if(scale == 100)
    {
        image_actual_rect_ = image_default_rect_;
    }
    else
    {
        image_actual_rect_.setWidth(image_default_rect_.width() * scale / 100);
        image_actual_rect_.setHeight(image_default_rect_.height() * scale / 100);
    }
    emit imageChanged();
}

const QImage &QImageViewRegionWidget::image() const
{
    return image_;
}

void QImageViewRegionWidget::setImage(const QImage &newImage)
{
    if (image_ == newImage)
        return;
    image_ = newImage;
    emit imageChanged();
}

const QColor &QImageViewRegionWidget::background_color() const
{
    return background_color_;
}

void QImageViewRegionWidget::setBackground_color(const QColor &newBackground_color)
{
    background_color_ = newBackground_color;
    emit backgroundColorChanged();
}

void QImageViewRegionWidget::slotZoomIn()
{
    if(image_scale_ < 400)
    {
        int image_scale = image_scale_ +  5;
        setImage_actual_rect(image_scale);
        setImage_scale(image_scale);
    }
}

void QImageViewRegionWidget::slotZoomOut()
{
    if(image_scale_ > 25)
    {
        int image_scale = image_scale_ -  5;
        setImage_actual_rect(image_scale);
        setImage_scale(image_scale);
    }
}

void QImageViewRegionWidget::slotZoomDefault()
{
    if(image_scale_ != 100)
    {
        int image_scale = 100;
        setImage_actual_rect(image_scale);
        setImage_scale(image_scale);
    }
}


void QImageViewRegionWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QString file_name = QFileDialog::getOpenFileName(this);

        if (!file_name.isEmpty())
        {
            setImage_file_name(file_name);
            setImage(QImage(file_name));
            image_default_rect_.setSize(image_.size());
            setImage_actual_rect(image_scale_);
        }
    }
}

void QImageViewRegionWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();

    painter.setBrush(background_color_);
    painter.drawRect(this->rect());

    painter.restore();

    if (!image_.isNull())
    {
        painter.drawImage(image_actual_rect_, image_);
    }
}
