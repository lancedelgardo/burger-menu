#include "burgermenu.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QString>
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

// TODO TextFarbe Menu ändern

static const QString BurgerButtonObjectName("BurgerButton");
static const QString BurgerMenuName("BurgerMenu");
static const QString MainBurgerButtonObjectName("MainBurgerButton");

BurgerMenu::BurgerMenu(BurgerMenuData *mData, QWidget *parent) : QWidget(parent), mActions(new QActionGroup(this)), mBurgerButton(new QPushButton(this)), mMenuWidth(200)
{
    this->menuData = mData;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mBurgerButton->setObjectName(MainBurgerButtonObjectName);
    mBurgerButton->setFlat(true);
    mBurgerButton->setIconSize(QSize(64, 64));
    mBurgerButton->setFixedSize(48, 48);

    //    mBurgerButton->setCheckable(true);
    //    mBurgerButton->setCursor(Qt::PointingHandCursor);
    mActions->setExclusive(true);

    auto burgerWidget = new QWidget(this);
    burgerWidget->setObjectName(BurgerMenuName);
    auto burgerLay = new QHBoxLayout();
    burgerLay->setContentsMargins(0, 0, 0, 0);
    burgerLay->setSpacing(0);
    burgerLay->addWidget(mBurgerButton);
    burgerLay->addWidget(burgerWidget);

    auto lay = new QVBoxLayout();
    setLayout(lay);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(50);

    lay->addLayout(burgerLay);
    lay->addStretch();

    if (!mData->getHideMenu())
    {
        connect(mBurgerButton, SIGNAL(pressed()), this, SLOT(onBurgerButtonPressed()));
        connect(mActions, SIGNAL(triggered(QAction *)), this, SLOT(onMenuTriggered(QAction *)));
    }
    else
    {
        connect(mBurgerButton, SIGNAL(pressed()), this, SLOT(onBurgerButtonPressed()));
        connect(mActions, SIGNAL(triggered(QAction *)), this, SLOT(onMenuTriggered(QAction *)));
    }
}

QIcon BurgerMenu::burgerIcon() const { return mBurgerButton->icon(); }

QSize BurgerMenu::iconSize() const { return mBurgerButton->iconSize(); }

int BurgerMenu::menuWidth() const { return mMenuWidth; }

QList< QAction * > BurgerMenu::actions() const { return mActions->actions(); }

QAction *BurgerMenu::addMenuAction(QAction *action, bool firstOnStartup)
{
    mActions->addAction(action);
    registerAction(action, firstOnStartup);
    return action;
}

QAction *BurgerMenu::addMenuAction(const QString &label, bool firstOnStartup)
{
    auto action = mActions->addAction(label);
    action->setCheckable(true);
    registerAction(action, firstOnStartup);
    return action;
}

QAction *BurgerMenu::addMenuAction(const QIcon &icon, const QString &label, bool firstOnStartup)
{
    auto action = mActions->addAction(icon, label);
    action->setCheckable(true);
    registerAction(action, firstOnStartup);
    return action;
}

void BurgerMenu::removeMenuAction(QAction *action)
{
    mActions->removeAction(action);
    unRegisterAction(action);
}

void BurgerMenu::setBurgerIcon(const QIcon &icon)
{
    mBurgerButton->setIcon(icon);
    emit iconChanged();
}

void BurgerMenu::setIconSize(const QSize &size)
{
    if (size == mBurgerButton->iconSize()) return;

    mBurgerButton->setIconSize(size);
    mBurgerButton->setFixedSize(size);
    auto buttons = findChildren< BurgerButton * >(BurgerButtonObjectName);
    for (auto btn : buttons)
        btn->setIconSize(size);

    if (mBurgerButton->isChecked())
        setFixedWidth(size.width() + mMenuWidth);
    else
        setFixedWidth(size.width());

    emit iconSizeChanged(size);
}

void BurgerMenu::setMenuWidth(int width)
{
    if (width == mMenuWidth) return;

    mMenuWidth = width;

    if (mBurgerButton->isChecked())
        setFixedWidth(mBurgerButton->iconSize().width() + mMenuWidth);
    else
        setFixedWidth(mBurgerButton->iconSize().width() + menuData->getOffset());

    emit menuWidthChanged(mMenuWidth);
}

void BurgerMenu::toggle(bool checked)
{
    if (menuData->getHideMenu()) toggled = checked;
    if (menuData->isAnimated())
    {
        auto anim = new QPropertyAnimation(this, "minimumWidth", this);
        anim->setDuration(menuData->getMenuOpenDuration());
        anim->setStartValue(mBurgerButton->iconSize().width());
        anim->setEndValue(mBurgerButton->iconSize().width() + mMenuWidth + menuData->getExtendedMenuSize());
        anim->setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
        anim->setEasingCurve(checked ? QEasingCurve::OutCubic : QEasingCurve::InCubic);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        if (checked)
            setFixedWidth(mBurgerButton->iconSize().width() + mMenuWidth);
        else
            setFixedWidth(mBurgerButton->iconSize().width() + menuData->getOffset());
    }
}

void BurgerMenu::registerAction(QAction *action, bool firstOnStartup)
{
    auto button = new BurgerButton(action, menuData, this);
    buttons.append(button);
    button->setIconSize(mBurgerButton->iconSize());
    auto lay = static_cast< QVBoxLayout * >(layout());
    lay->insertWidget(lay->count() - 1, button);

    if (firstOnStartup)
    {
        button->setToggled(true);
        lastTriggeredButton = button;
        triggeredButton = button;
    }

    connect(button, SIGNAL(pressed()), this, SLOT(onButtonClicked()));
}

void BurgerMenu::unRegisterAction(QAction *action)
{
    auto buttons = findChildren< BurgerButton * >(BurgerButtonObjectName);
    auto btn = std::find_if(buttons.begin(), buttons.end(), [&](BurgerButton *btn) { return btn->action() == action; });
    if (btn != buttons.end()) delete *btn;
}

void BurgerMenu::onMenuTriggered(QAction *action)
{
    if (toggled && menuData->getHideMenu()) toggle(false);
    triggered(action);
}

void BurgerMenu::onBurgerButtonPressed()
{
    if (!toggled && menuData->getHideMenu())
        toggle(true);
    else
        toggle(false);
}

void BurgerMenu::onButtonClicked()
{
    auto button = static_cast< BurgerButton * >(sender());
    auto action = button->action();
    if (action->isCheckable() && !action->isChecked())
    {
        action->toggle();
    }

    if (lastTriggeredButton)
    {
        lastTriggeredButton->setToggled(false);
    }
    triggeredButton = button;
    lastTriggeredButton = triggeredButton;
    triggeredButton->setToggled(true);

    action->trigger();
}

void BurgerMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
