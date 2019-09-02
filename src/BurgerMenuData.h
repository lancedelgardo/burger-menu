#ifndef BURGERMENUDATA_H
#define BURGERMENUDATA_H

#include <QColor>

class BurgerMenuData
{
  public:
    BurgerMenuData();

    bool getHideMenu() const;
    void setHideMenu(bool value);

    QColor getToggledColor() const;
    void setToggledColor(const QColor &value);

    int getToggleSize() const;
    void setToggleSize(int value);

    int getOffset() const;
    void setOffset(int value);

    int getMenuOpenDuration() const;
    void setMenuOpenDuration(int value);

    bool isAnimated() const;
    void setAnimated(bool value);

    bool getMarkToggledButton() const;
    void setMarkToggledButton(bool value);

    int getExtendedMenuSize() const;
    void setExtendedMenuSize(int value);

    private:
    bool markToggledButton = true;
    QColor toggledColor = QColor(51, 204, 255);
    int toggleSize = 3;
    int offset = 15;
    int menuOpenDuration = 200;
    bool hideMenu = false;
    bool _isAnimated = true;
    int extendedMenuSize = 0;
};

#endif  // BURGERMENUDATA_H
