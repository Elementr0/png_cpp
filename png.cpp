#include<iostream>
#include<fstream> //для работы с файлыми
#include <cstdio>  // Для sprintf
#include<string>

void creat_header_png(std::string name);
void create_png(std::string name,int Length, int Width);

int main(){

    //creat_header_png("test");
    int n = 123;
    char hexSt[8];
    sprintf(hexSt, "%x", n);
}


// void creat_header_png(std::string name){
//     std::ofstream file (name + ".png", std::ios::binary); //подключаем файл
//     unsigned char png_header[]={0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
//     file.write(reinterpret_cast<char*>(png_header), sizeof(png_header));//записываем в файл
//     file.closr(); 
// }

// void create_IHDR (std::string name,int Length, int Width){
//     std::ofstream file (name + ".png", std::ios::binary); //подключаем файл

// }