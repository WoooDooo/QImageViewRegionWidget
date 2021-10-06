#ifndef QIMAGEVIEWREGIONWIDGET_H
#define QIMAGEVIEWREGIONWIDGET_H

#include <QWidget>
#include <QImage>
#include <QShortcut>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>

class QImageViewRegionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QImageViewRegionWidget(QWidget *parent = nullptr);



private:
    QColor background_color_;
    QString image_file_name_;
    QImage image_;

    QRect image_default_rect_;
    QRect image_actual_rect_;

    int image_scale_;

    QShortcut* key_ctrl_plus_;
    QShortcut* key_ctrl_minus_;
    QShortcut* key_ctrl_asterisk_;

public:

    const QColor &background_color() const;
    void setBackground_color(const QColor &newBackground_color);

    const QImage &image() const;
    void setImage(const QImage &newImage);

    void setImage_actual_rect(const int scale);

    int image_scale() const;
    void setImage_scale(int newImage_scale);

signals:
    void backgroundColorChanged();
    void imageChanged();
    void imageScaleChanged();

public slots:
    void slotZoomIn();
    void slotZoomOut();
    void slotZoomDefault();

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // QIMAGEVIEWREGIONWIDGET_H
