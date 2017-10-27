#ifndef THEMEAPPICON_H
#define THEMEAPPICON_H

#include <QObject>

class ThemeAppIcon : public QObject
{
    Q_OBJECT
public:
    explicit ThemeAppIcon(QObject *parent = 0);
    ~ThemeAppIcon();

    static const QPixmap getIcon(const QString iconName, const int size);
};

#endif // THEMEAPPICON_H
