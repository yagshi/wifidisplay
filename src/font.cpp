#include <esp_system.h>
unsigned char font55[][5] = {
    //// 00
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// 10
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// 20
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00100, 0b00100, 0b00100, 0b00000, 0b00100},
    //
    {0b01010, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b01010, 0b11111, 0b01010, 0b11111, 0b01010},
    //
    {0b01111, 0b10100, 0b01110, 0b00101, 0b11110},
    //
    {0b10001, 0b00010, 0b00100, 0b01000, 0b10001},
    //
    {0b01100, 0b10010, 0b01100, 0b10010, 0b11111},
    //
    {0b00100, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00010, 0b00100, 0b00100, 0b00100, 0b00010},
    //
    {0b00100, 0b00010, 0b00010, 0b00010, 0b00100},
    //
    {0b10101, 0b01110, 0b11111, 0b01100, 0b10101},
    //
    {0b00100, 0b00100, 0b11111, 0b00100, 0b00100},
    //
    {0b00000, 0b00000, 0b00000, 0b00100, 0b01000},
    //
    {0b00000, 0b00000, 0b11111, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b01000},
    //
    {0b00001, 0b00010, 0b00100, 0b01000, 0b10000},
    //// 30
    {0b01110, 0b10011, 0b10101, 0b11001, 0b01110},
    //
    {0b00100, 0b01100, 0b00100, 0b00100, 0b01110},
    //
    {0b01110, 0b10001, 0b00110, 0b01000, 0b11111},
    //
    {0b11110, 0b00001, 0b01110, 0b00001, 0b11110},
    //
    {0b00110, 0b01010, 0b10010, 0b11111, 0b00010},
    //
    {0b11111, 0b10000, 0b11110, 0b00001, 0b11110},
    //
    {0b01110, 0b10000, 0b11110, 0b10001, 0b01110},
    //
    {0b11111, 0b00001, 0b00010, 0b00100, 0b00100},
    //
    {0b01110, 0b10001, 0b01110, 0b10001, 0b01110},
    //
    {0b01110, 0b10001, 0b01111, 0b00001, 0b01110},
    //
    {0b00000, 0b00100, 0b00000, 0b00100, 0b00000},
    //
    {0b00000, 0b00100, 0b00000, 0b00100, 0b01000},
    //
    {0b00010, 0b00100, 0b01000, 0b00100, 0b00010},
    //
    {0b00000, 0b11111, 0b00000, 0b11111, 0b00000},
    //
    {0b01000, 0b00100, 0b00010, 0b00100, 0b01000},
    //
    {0b01110, 0b10001, 0b00110, 0b00000, 0b00100},
    //// 40 //////////////////////////
    {0b11110, 0b00001, 0b11111, 0b10001, 0b01110},
    //
    {0b00100, 0b01010, 0b10001, 0b11111, 0b10001},  // A
    //
    {0b11110, 0b10001, 0b11110, 0b10001, 0b11111},
    //
    {0b01110, 0b10001, 0b10000, 0b10001, 0b01110},
    //
    {0b11110, 0b10001, 0b10001, 0b10001, 0b11110},
    //
    {0b11111, 0b10000, 0b11110, 0b10000, 0b11111},
    //
    {0b11111, 0b10000, 0b11110, 0b10000, 0b10000},  // F
    //
    {0b01111, 0b10000, 0b10011, 0b10001, 0b01111},
    //
    {0b10001, 0b10001, 0b11111, 0b10001, 0b10001},
    //
    {0b01110, 0b00100, 0b00100, 0b00100, 0b01110},
    //
    {0b00111, 0b00010, 0b00010, 0b10010, 0b01100},
    //
    {0b10010, 0b10100, 0b11000, 0b10100, 0b10010},
    //
    {0b10000, 0b10000, 0b10000, 0b10000, 0b11111},
    //
    {0b10001, 0b11011, 0b10101, 0b10001, 0b10001},  // M
    //
    {0b10001, 0b11001, 0b10101, 0b10011, 0b10001},
    //
    {0b01110, 0b10001, 0b10001, 0b10001, 0b01110},
    //// 50
    {0b11110, 0b10001, 0b11110, 0b10000, 0b10000},
    //
    {0b01110, 0b10001, 0b10001, 0b10011, 0b01111},
    //
    {0b11110, 0b10001, 0b11110, 0b10100, 0b10010},
    //
    {0b01111, 0b10000, 0b01110, 0b00001, 0b11110},  // S
    //
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100},
    //
    {0b10001, 0b10001, 0b10001, 0b10001, 0b01110},
    //
    {0b10001, 0b10001, 0b01010, 0b01010, 0b00100},
    //
    {0b10001, 0b10101, 0b10101, 0b10101, 0b01010},
    //
    {0b01001, 0b01010, 0b00100, 0b01010, 0b10001},
    //
    {0b10001, 0b01010, 0b00100, 0b00100, 0b00100},
    //
    {0b11111, 0b00010, 0b00100, 0b01000, 0b11111},  // Z
    //
    {0b00110, 0b00100, 0b00100, 0b00100, 0b00110},  // [
    //
    {0b10000, 0b01000, 0b00100, 0b00010, 0b00001},  // \ 
    //
    {0b01100, 0b00100, 0b00100, 0b00100, 0b11000},  // ]
    //
    {0b00100, 0b01010, 0b00000, 0b00000, 0b00000},  // ^
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b11111},  // _
    //// 60
    {0b00100, 0b00010, 0b00000, 0b00000, 0b00000},  // `
    //
    {0b01110, 0b00001, 0b01111, 0b10001, 0b01111},  // a
    //
    {0b10000, 0b10000, 0b11100, 0b10010, 0b11100},
    //
    {0b00000, 0b01110, 0b10000, 0b10001, 0b01110},
    //
    {0b00001, 0b00001, 0b00111, 0b01001, 0b00111},  // d
    //
    {0b01110, 0b10001, 0b11110, 0b10000, 0b01110},
    //
    {0b00110, 0b00100, 0b01110, 0b00100, 0b00100},
    //
    {0b01111, 0b10001, 0b01111, 0b00001, 0b01110},
    //
    {0b01000, 0b01010, 0b01101, 0b01001, 0b01001},
    //
    {0b00100, 0b00000, 0b00100, 0b00100, 0b00100},
    //
    {0b00010, 0b00000, 0b00010, 0b01010, 0b00100},
    //
    {0b10000, 0b10010, 0b10100, 0b11000, 0b10110},
    //
    {0b00100, 0b00100, 0b00100, 0b00100, 0b00010},
    //
    {0b00000, 0b11010, 0b10101, 0b10101, 0b10101},
    //
    {0b00000, 0b11110, 0b10001, 0b10001, 0b10001},
    //
    {0b00000, 0b01110, 0b10001, 0b10001, 0b01110},  // o
    //// 70
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// 80 //////////////////////////
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// 90
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// a0
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// b0
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// c0 //////////////////////////
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// d0
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// e0
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //// f0
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    //
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    ////
};
