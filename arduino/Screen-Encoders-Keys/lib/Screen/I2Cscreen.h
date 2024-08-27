#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>

// Bitmaps definitions
extern const unsigned char Menu[];
extern const unsigned char WindowsStart[];
extern const unsigned char BattleStageGames[];
extern const unsigned char Mute[];
extern const unsigned char VS_Code[];
extern const unsigned char Pause[];
extern const unsigned char Volume[];
extern const unsigned char Spotify[];
extern const unsigned char Outplayed[];
extern const unsigned char Minecraft[];
extern const unsigned char Folder[];
extern const unsigned char Microfoon[];
extern const unsigned char Start[];
extern const unsigned char Discord[];
extern const unsigned char LightRoom[];
extern const unsigned char MasterVolume[];
extern const unsigned char item_sel_outline[];

extern const unsigned char *bitmapList[];

// Display and menu settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ITEMS_PER_PAGE 3
#define NUMBER_OF_PAGES 3
#define AMOUNT_OF_ROWS 3
#define AMOUNT_OF_COLS 4

// Button pins
#define BUTTON_DOWN_PIN 5
#define BUTTON_UP_PIN 4
#define BUTTON_BACK_PIN 3
#define BUTTON_SELECT_PIN 2

typedef struct {
    const unsigned char *icon;
    const char *name;
} IconItem;

typedef struct {
    int encoder;
    bool button;
} EncoderItem;

class Screen {
public:
    Screen(Adafruit_SSD1305 &display);
    void setup();
    void loop();
    void removeMenuItem(int index);
    void setMenuList(IconItem *ListItems);
    void setEncoderValues(int *values, bools *buttons);

private:
    Adafruit_SSD1305 &display;
    void drawBitmap(const unsigned char *bitmap, uint8_t x, uint8_t y);
    void displayMenu();
    void displayPage(int index);
    void switchPage(int index);
    int itemselected = 0;
    int currentPage = 0;
    int ActiveVolumeValues[2];
    int EncoderValues[2];
    int EncoderPrevieusValues[2];
    bool EncoderButtons[2];
    IconItem *menuList;  // Use the correct declaration
    EncoderItem *Encoders;





    // Key icons that should be shown per page thats activeted.
    const unsigned char *GamingPage[AMOUNT_OF_ROWS][AMOUNT_OF_COLS] = {
        {Discord, BattleStageGames, Minecraft, NULL},
        {WindowsStart, Spotify, Outplayed, NULL},
        {Start, Pause, Volume, Microfoon}};

    const unsigned char *LightRoomPage[AMOUNT_OF_ROWS][AMOUNT_OF_COLS] = {
        {LightRoom, Folder, NULL, NULL},
        {WindowsStart, Spotify, NULL, NULL},
        {Start, Pause, Volume, Microfoon}};
    // END//
};

#endif // SCREEN_H
