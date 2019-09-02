#ifndef BURGERBUTTON_H
#define BURGERBUTTON_H

#include "BurgerMenuData.h"

#include <QPushButton>
#include <QDebug>
#include <QWidget>
#include <QAction>
#include <QObject>

class BurgerButton : public QPushButton
{
    Q_OBJECT
  public:
    BurgerButton(QAction *action, BurgerMenuData *menuData, QWidget *parent = Q_NULLPTR);

    void setIconSize(const QSize &size);
    QAction *action() const;

    bool isToggled();
    void setToggled(bool value);

  private:
    QSize mIconSize;
    QAction *mAction = Q_NULLPTR;
    bool m_toggled = false;
    BurgerMenuData *menuData = Q_NULLPTR;


    // QWidget interface
  protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif  // BURGERBUTTON_H
