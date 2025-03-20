#include <iostream>
#include <fstream>  
#include <string>
#include <array>    

void creat_header_png(std::string name);
void create_IHDR(std::string name, int Length, int Width, int Bit_depth, int Color_type);
std::array<unsigned char, 4> intToByteArray(int number);

int main() {
    std::string name = "test";
    creat_header_png(name);
    create_IHDR(name, 32, 32, 82, 33);
}

void creat_header_png(std::string name) {
    std::ofstream file(name + ".png", std::ios::binary); 
    unsigned char png_header[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    file.write(reinterpret_cast<char*>(png_header), sizeof(png_header)); 
    file.close();
}

 /*
       Немного о create_IHDR
       -----------------------
       name - название файла png
       Length и Width длина и ширена файла
       bit_depth - глубина цвана
       1, 2, 4, 8, 16 для Greyscale 	Color type = 0
       8, 16 для Truecolor              Color type =  2
       1, 2, 4, 8 для Indexed-color     Color type =  3
       8, 16 для Greyscale with alpha   Color type =  4
       8, 16 для Truecolor with alpha   Color type =  6
       -----------------------*/

void create_IHDR(std::string name, int Length, int Width, int Bit_depth, int Color_type) {
    std::ofstream file(name + ".png", std::ios::binary | std::ios::app); 

    unsigned char png_IHDRsize[] = {0x00, 0x00, 0x00, 0x0D};
    unsigned char png_IHDR[] = {0x49, 0x48, 0x44, 0x52}; 

    auto hexLength = intToByteArray(Length);
    auto hexWidth = intToByteArray(Width);  

    file.write(reinterpret_cast<char*>(png_IHDRsize), sizeof(png_IHDRsize));
    file.write(reinterpret_cast<char*>(png_IHDR), sizeof(png_IHDR));
    file.write(reinterpret_cast<const char*>(hexLength.data()), hexLength.size()); 
    file.write(reinterpret_cast<const char*>(hexWidth.data()), hexWidth.size()); 
    
    switch (Color_type) {
        case 0: {
            switch (Bit_depth) {
                case 1: file.put(0x01); break;
                case 2: file.put(0x02); break;
                case 4: file.put(0x04); break;
                case 8: file.put(0x08); break;
                case 16: file.put(0x10); break;
                default: file.put(0x01);
            }
            file.put(0x00);
            break;
        }
        case 2: {
            switch (Bit_depth) {
                case 8: file.put(0x08); break;
                case 16: file.put(0x10); break;
                default: file.put(0x08);
            }
            file.put(0x02);
            break;
        }
        case 3: {
            switch (Bit_depth) {
                case 1: file.put(0x01); break;
                case 2: file.put(0x02); break;
                case 4: file.put(0x04); break;
                case 8: file.put(0x08); break;
                default: file.put(0x01);
            }
            file.put(0x03);
            break;
        }
        case 4: {
            switch (Bit_depth) {
                case 8: file.put(0x08); break;
                case 16: file.put(0x10); break;
                default: file.put(0x08);
            }
            file.put(0x04);
            break;
        }
        case 6: {
            switch (Bit_depth) {
                case 8: file.put(0x08); break;
                case 16: file.put(0x10); break;
                default: file.put(0x08);
            }
            file.put(0x06);
            break;
        }
        default: {
            file.put(0x08);
            file.put(0x06);
            break;
        }
    }

    file.close();
}

std::array<unsigned char, 4> intToByteArray(int number) {
    return {
        static_cast<unsigned char>((number >> 24) & 0xFF),
        static_cast<unsigned char>((number >> 16) & 0xFF),
        static_cast<unsigned char>((number >> 8) & 0xFF),
        static_cast<unsigned char>(number & 0xFF)
    };
}
