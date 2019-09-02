# burger-menu
A extended burger menu widget implementation for Qt.
designer_plugin wont work anymore.

Added a small rectangle to the active menu.
If menu is open it will close on clicking a menu button.
Added a data class to have more options how it should look. You can find the options in the main file after instance the "BurgerMenuData".

Little bug on "menuData->setHideMenu(true);". If false it doesnt work like expected.

![Example image](https://github.com/lancedelgardo/burger-menu/blob/master/example/images/newPreview.jpg)
