#include "constants.h"
#include "containerwidget.h"
#include "item/pluginsitem.h"

#include <QDebug>
#include <QDragEnterEvent>

#define ITEM_HEIGHT         30
#define ITEM_WIDTH          30

ContainerWidget::ContainerWidget(QWidget *parent)
    : QWidget(parent),

      m_centralLayout(new QHBoxLayout)
{
    m_centralLayout->addStretch();
    m_centralLayout->setSpacing(0);
    m_centralLayout->setMargin(0);

    setLayout(m_centralLayout);
    setFixedHeight(ITEM_HEIGHT);
    setFixedWidth(ITEM_WIDTH);
    setAcceptDrops(true);
}

void ContainerWidget::addWidget(QWidget * const w)
{
    w->setParent(this);
    w->setFixedSize(ITEM_WIDTH, ITEM_HEIGHT);
    m_centralLayout->addWidget(w);
    m_itemList.append(w);

    setFixedWidth(ITEM_WIDTH * std::max(1, m_itemList.size()));
}

void ContainerWidget::removeWidget(QWidget * const w)
{
    m_centralLayout->removeWidget(w);
    m_itemList.removeOne(w);

    setFixedWidth(ITEM_WIDTH * std::max(1, m_itemList.size()));
}

int ContainerWidget::itemCount() const
{
    return m_itemList.count();
}

const QList<QWidget *> ContainerWidget::itemList() const
{
    return m_itemList;
}

bool ContainerWidget::allowDragEnter(QDragEnterEvent *e)
{
    if (!e->mimeData()->hasFormat(DOCK_PLUGIN_MIME))
        return false;

    PluginsItem *pi = static_cast<PluginsItem *>(e->source());
    if (pi && pi->allowContainer())
        return true;

    return false;
}

void ContainerWidget::dragEnterEvent(QDragEnterEvent *e)
{
    if (allowDragEnter(e))
        return e->accept();
}
