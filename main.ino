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

    uint8_t getMenuSiize() const {
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

void setup(){
    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
        Serial.println();
        for(;;){}
    }
    display.clearDisplay();
    display.display();
}

void loop(){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Hello World!");
    display.display();
}
