#include "BurgerMenuData.h"

BurgerMenuData::BurgerMenuData() {}

bool BurgerMenuData::getHideMenu() const { return hideMenu; }

void BurgerMenuData::setHideMenu(bool value) { hideMenu = value; }

QColor BurgerMenuData::getToggledColor() const { return toggledColor; }

void BurgerMenuData::setToggledColor(const QColor &value) { toggledColor = value; }

int BurgerMenuData::getToggleSize() const { return toggleSize; }

void BurgerMenuData::setToggleSize(int value) { toggleSize = value; }

int BurgerMenuData::getOffset() const { return offset; }

void BurgerMenuData::setOffset(int value) { offset = value; }

int BurgerMenuData::getMenuOpenDuration() const { return menuOpenDuration; }

void BurgerMenuData::setMenuOpenDuration(int value) { menuOpenDuration = value; }

bool BurgerMenuData::isAnimated() const { return _isAnimated; }

void BurgerMenuData::setAnimated(bool value) { _isAnimated = value; }

bool BurgerMenuData::getMarkToggledButton() const { return markToggledButton; }

void BurgerMenuData::setMarkToggledButton(bool value) { markToggledButton = value; }

int BurgerMenuData::getExtendedMenuSize() const
{
    return extendedMenuSize;
}

void BurgerMenuData::setExtendedMenuSize(int value)
{
    extendedMenuSize = value;
}
