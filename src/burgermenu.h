#pragma once
#include <QWidget>
#include <QList>
#include <QSize>
#include <QIcon>

#include "BurgerButton.h"
#include "BurgerMenuData.h"

class QPushButton;
class QActionGroup;
class QAction;
class QString;

class BurgerMenu : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QIcon icon READ burgerIcon WRITE setBurgerIcon NOTIFY iconChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
    Q_PROPERTY(int menuWidth READ menuWidth WRITE setMenuWidth NOTIFY menuWidthChanged)
    //    Q_PROPERTY(bool animated READ animated WRITE setAnimated NOTIFY animatedChanged)

  public:
    BurgerMenu(BurgerMenuData *mData, QWidget *parent = nullptr);

    QIcon burgerIcon() const;
    QSize iconSize() const;
    int menuWidth() const;
    QList< QAction * > actions() const;
    bool animated() const;

  signals:
    void iconChanged() const;
    void iconSizeChanged(const QSize &size) const;
    void menuWidthChanged(int width) const;
    void animatedChanged(bool animated) const;
    void triggered(QAction *action) const;

  public slots:
    QAction *addMenuAction(QAction *action, bool firstOnStartup = false);
    QAction *addMenuAction(const QString &label, bool firstOnStartup = false);
    QAction *addMenuAction(const QIcon &icon, const QString &label, bool firstOnStartup = false);
    void removeMenuAction(QAction *action);

    void setBurgerIcon(const QIcon &icon);
    void setIconSize(const QSize &size);
    void setMenuWidth(int width);

  protected:
    void paintEvent(QPaintEvent *) override;

  private:
    void registerAction(QAction *action, bool firstOnStartup = false);
    void unRegisterAction(QAction *action);
    void toggle(bool checked);

    QActionGroup *mActions;
    //    QPushButton *mBurgerButton;
    QPushButton *mBurgerButton;
    int mMenuWidth;
    bool toggled = false;

    BurgerButton *lastTriggeredButton = Q_NULLPTR;
    BurgerButton *triggeredButton = Q_NULLPTR;

    QList< BurgerButton * > buttons;

    BurgerMenuData *menuData = Q_NULLPTR;

  private slots:
    void onMenuTriggered(QAction *action);
    void onBurgerButtonPressed();
    void onButtonClicked();
};
