#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xcb/xcb_misc.h"
#include "dbus/dbusdisplay.h"
#include "dbus/dbusdockadaptors.h"
#include "util/docksettings.h"

#include <QWidget>
#include <QTimer>
#include <QRect>

#include <DPlatformWindowHandle>
#include <DWindowManagerHelper>

class MainPanel;
class DBusDockAdaptors;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QRect panelGeometry();

private:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);

    void setFixedSize(const QSize &size);
    void internalMove(int x, int y);
    void initComponents();
    void initConnections();

    const QPoint x11GetWindowPos();
    void x11MoveWindow(const int x, const int y);
    void x11MoveResizeWindow(const int x, const int y, const int w, const int h);

signals:
    void panelGeometryChanged();

private slots:
    void positionChanged(const Position prevPos);
    void updatePosition();
    void updateGeometry();
    void clearStrutPartial();
    void setStrutPartial();
    void compositeChanged();

    void expand();
    void narrow(const Position prevPos);
    void resetPanelEnvironment(const bool visible);
    void updatePanelVisible();

    void adjustShadowMask();

private:
    bool m_updatePanelVisible;
    MainPanel *m_mainPanel;

    DPlatformWindowHandle m_platformWindowHandle;
    DWindowManagerHelper *m_wmHelper;

    QTimer *m_positionUpdateTimer;
    QTimer *m_expandDelayTimer;
    QVariantAnimation *m_sizeChangeAni;
    QPropertyAnimation *m_posChangeAni;
    QPropertyAnimation *m_panelShowAni;
    QPropertyAnimation *m_panelHideAni;

    XcbMisc *m_xcbMisc;
    DockSettings *m_settings;
};

#endif // MAINWINDOW_H
