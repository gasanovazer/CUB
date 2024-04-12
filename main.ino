#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>

// Encoder
#define CLK 16
#define DT 17
#define SW 15

// SSD1306 OLED display width, height in pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

bool boolmenu = false;

// Объявление класса MenuItem
class MenuItem{
public:
    MenuItem(const char* name, void (*function)(), bool hasSubMenu = false) : name(name), function(function), hasSubMenuFlag(hasSubMenu){}
    const char* getName() const{return name;}
    void executeFunction() const {if (function != nullptr) function();}
    bool hasSubMenu() const {return hasSubMenuFlag;}
private:
    const char* name;
    void (*function)();
    bool hasSubMenuFlag;
};
// Оъявление класса меню
class Menu {
public:
    std::vector<MenuItem> menuItems;
    int currentMenuItemIndex = 0;

    void addMenuItem(const char* name, void (*function)()) {
        menuItems.emplace_back(name, function);
    }

    void moveCursorRight() {
        currentMenuItemIndex++;
        if (currentMenuItemIndex >= menuItems.size()) {
            currentMenuItemIndex = 0;
        }
    }

    void moveCursorLeft(){
        currentMenuItemIndex--;
        if (currentMenuItemIndex<0) {
            currentMenuItemIndex = menuItems.size() - 1;
        }
    }

    MenuItem& getMenuItem(int index){
        return menuItems[index];
    }

    uint8_t getMenuSize() const {
        return menuItems.size();
    }

    void resetCurrentMenuItemIndex() {
        currentMenuItemIndex = 0;
    }
    void clearMenuItems(){
        menuItems.clear();
    }
};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Menu mainMenu;
Menu subMenu;
const uint8_t ITEMS_PER_PAGE = 3;

bool inSubMenu = false;
String currentMenuName = "Menu";

void main_menu(){
    mainMenu.addMenuItem("Dashboard", nullptr);
    mainMenu.addMenuItem("ON/OFF", nullptr);
    mainMenu.addMenuItem("Status", status_incub);
    mainMenu.addMenuItem("Sensors", nullptr);
    mainMenu.addMenuItem("Settings", nullptr);    
    currentMenuName = "Menu";
    displayMenu(mainMenu, currentMenuName);
}

void status_incub() {
    subMenu.clearMenuItems();
    subMenu.addMenuItem("1 Status", nullptr);
    subMenu.addMenuItem("2 Status", nullptr);
    subMenu.addMenuItem("3 Status", nullptr);
    subMenu.addMenuItem("4 Status", nullptr);
    subMenu.addMenuItem("5 Status", nullptr);
    currentMenuName = "Status";
    inSubMenu = true;
    displayMenu(subMenu, currentMenuName);
}

void setting() {}
void on_off_incub() {}

void backFunction() {
    currentMenuName = "Menu";
    inSubMenu = false;
    subMenu.resetCurrentMenuItemIndex();
    displayMenu(subMenu, currentMenuName);
}

void displayMenu(Menu& menu, const String& menuName){
    display.clearDisplay();
    display.setCursor(0,0);

    // Вывод название меню
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20,0);
    display.println(menuName);
    display.drawLine(0,11,127,11, SSD1306_WHITE);

    // Определенение индекса первого пункта для отображения
    uint8_t startItem = max(0, menu.currentMenuItemIndex - 1);
    startItem = min(startItem, max(0, menu.getMenuSize() - 3));

    // Show item menu
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t index = startItem + i;
        display.setCursor(20, 15*(i+1));
        if (index == menu.currentMenuItemIndex) {
            display.drawRoundRect(5,14*(i+1), 120, 12, 4, SSD1306_WHITE);
        }
        if (index < menu.getMenuSiize()){
            display.println(menu.getMenuItem(index).getName());
        }
    }
    display.display();
}

void setup(){
    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
        Serial.println();
        for(;;){}
    }
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    main_menu();
    display.display();
}

void loop(){
    if (inSubMenu){
        return;
    } else {
        return;
    }
}
