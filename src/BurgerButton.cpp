#include "BurgerButton.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionButton>
#include <QPaintEvent>

static const QString BurgerButtonObjectName("BurgerButton");

BurgerButton::BurgerButton(QAction *action, BurgerMenuData *menuData, QWidget *parent) : QPushButton(parent), mAction(action), mIconSize(QSize(64, 64))
{
    this->menuData = menuData;
    setObjectName(BurgerButtonObjectName);
    connect(action, &QAction::destroyed, this, &BurgerButton::deleteLater);
    setCursor(Qt::PointingHandCursor);
    setText(action->text());

    connect(mAction, SIGNAL(changed()), this, SLOT(update()));
}

void BurgerButton::setIconSize(const QSize &size)
{
    mIconSize = size;
    setFixedHeight(mIconSize.height());
    update();
}

QAction *BurgerButton::action() const { return mAction; }

bool BurgerButton::isToggled() { return m_toggled; }

void BurgerButton::setToggled(bool value)
{
    m_toggled = value;
    repaint();
}

void BurgerButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (m_toggled && menuData->getMarkToggledButton())
    {
        painter.setRenderHint(QPainter::Antialiasing, true);

        QPen pen;
        pen.setColor(menuData->getToggledColor());
        pen.setWidth(menuData->getToggleSize());
        painter.setPen(pen);

        painter.drawRect(0, 0, menuData->getToggleSize(), mIconSize.height());
    }
    painter.translate(menuData->getOffset(), 0);
    QStyleOptionButton opt;
    opt.initFrom(this);
    opt.state |= (mAction->isChecked() ? QStyle::State_On : QStyle::State_Off);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    if (!mAction->icon().isNull())
    {
        QIcon::Mode mode = /*QIcon::Disabled; */ ((opt.state & QStyle::State_MouseOver) == 0) ? QIcon::Normal : QIcon::Active;
        if (!isEnabled()) mode = QIcon::Disabled;
        QIcon::State state = mAction->isChecked() ? QIcon::On : QIcon::Off;
        painter.drawPixmap(QRect(QPoint(0, 0), mIconSize), mAction->icon().pixmap(mIconSize, mode, state));
    }

    opt.rect = rect().adjusted(mIconSize.width(), 0, 0, 0);
    opt.text = fontMetrics().elidedText(mAction->iconText(), Qt::ElideRight, opt.rect.width(), Qt::TextShowMnemonic);
    style()->drawControl(QStyle::CE_CheckBoxLabel, &opt, &painter, this);
}
