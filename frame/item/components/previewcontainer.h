#ifndef PREVIEWCONTAINER_H
#define PREVIEWCONTAINER_H

#include <QWidget>
#include <QHBoxLayout>

#include "dbus/dbusdockentry.h"
#include "constants.h"

#include <DWindowManagerHelper>

DWIDGET_USE_NAMESPACE

class PreviewContainer : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewContainer(QWidget *parent = 0);

signals:
    void requestActivateWindow(const WId wid) const;
    void requestPreviewWindow(const WId wid) const;
    void requestCancelPreview() const;
    void requestHidePreview() const;

public:
    void setWindowInfos(const WindowDict &infos);

public slots:
    void updateLayoutDirection(const Dock::Position dockPos);

protected:
    void leaveEvent(QEvent *e);
    void enterEvent(QEvent *e);

private slots:
    void updateContainerSize();
    void checkMouseLeave();

private:
    QBoxLayout *m_windowListLayout;

    DWindowManagerHelper *m_wmHelper;

    QTimer *m_mouseLeaveTimer;

    QMap<WId, QWidget *> m_windows;
};

#endif // PREVIEWCONTAINER_H
