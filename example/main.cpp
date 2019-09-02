#include <QApplication>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QIcon>
#include <QAction>
#include "../src/burgermenu.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.setMinimumSize(500, 400);

    BurgerMenuData *menuData = new BurgerMenuData();
    menuData->setAnimated(true);                      // Animation of Menu
    menuData->setHideMenu(true);                      // false = Show Menu as long as menuButton clicked again | true = hide menu by clicking button
    menuData->setMenuOpenDuration(400);               // Speed of Opening Menu
    menuData->setOffset(15);                          // Space between markToggled and Button
    menuData->setMarkToggledButton(true);             // Show Toggle Mark
    menuData->setToggledColor(QColor(51, 204, 255));  // Color of Toggle Mark
    menuData->setToggleSize(3);                       // Size of Toggle Mark
    menuData->setExtendedMenuSize(100);               // Toggled Menu Size
    BurgerMenu *menu = new BurgerMenu(menuData);

    QTextEdit*  textEdit = new QTextEdit();

    window.setLayout(new QHBoxLayout());
    window.layout()->setContentsMargins(0,0,0,0);
    window.layout()->setSpacing(0);
    window.layout()->addWidget(menu);
    window.layout()->addWidget(textEdit);

    menu->setMenuWidth(100);
    menu->setBurgerIcon(QIcon(":/images/burger.png"));
    menu->addMenuAction(QIcon(":/images/collections.png"), "Collection");
    menu->addMenuAction(QIcon(":/images/folders.png"),     "Folders");
    menu->addMenuAction(QIcon(":/images/albums.png"),      "Albums");

    window.setStyleSheet("BurgerMenu                  { background-color: black;   }"
                         "#BurgerMenu                 { background-color: black;   }"
                         "#BurgerButton               { background-color: black;   color: white; font-size: 18px; }"
                         "#BurgerButton:hover         { background-color: #3480D2; }"
                         "#BurgerButton:checked       { background-color: #106EBE; }"
                         "#BurgerButton:checked:hover { background-color: #3480D2; }"
                         "#MainBurgerButton           { background-color: black;   border: none; } "
                         "#MainBurgerButton:hover     { background-color: #333;    } "
                        );

    QObject::connect(menu, &BurgerMenu::triggered, [&](QAction* action)
    {
        textEdit->setText(QString("Action \"%1\" clicked.").arg(action->iconText()));
    });

    window.show();
    return a.exec();
}
