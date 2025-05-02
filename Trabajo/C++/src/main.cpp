// QR Code Generator in C++
// Este programa genera un código QR a partir de una URL proporcionada como argumento de línea de comandos.
// Requiere la biblioteca QRencode y LodePNG para la generación y guardado de imágenes PNG respectivamente.
//
// Uso:
// g++ -o qr_generator main.cpp lodepng.cpp -lqrencode
// ./qr_generator "https://example.com"
//
// Al ejecutar el programa, se generará un archivo PNG llamado "codigo_qr.png" en el directorio actual.
//
// Trabajo realizado por: Jorge Sánchez y Carlos Guasp

#include <iostream>
#include <vector>
#include <qrencode.h>
#include "lodepng.h"

using namespace std;

// Función para guardar la matriz QR como PNG
void genera_Qr(const vector<unsigned char>& qr, int tam, const string& ficheroSalida) {
   vector<unsigned char> imagen(tam * tam * 4);
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int indice = i * tam + j;
            unsigned char color = qr[indice] & 0x01 ? 0 : 255; // negro o blanco
            int indicePixel = 4 * indice;
            imagen[indicePixel] = color;     
            imagen[indicePixel + 1] = color; 
            imagen[indicePixel + 2] = color;
            imagen[indicePixel + 3] = 255;   
        }
    }
    unsigned int error = lodepng::encode(ficheroSalida, imagen, tam, tam);
    if (error) {
        cerr << "Error guardando PNG: " << lodepng_error_text(error) << endl;
    } else {
        cout << "QR guardado en " << ficheroSalida << endl;
    }
}

int main(int argc, char* argv[]) {
    // Compobación del número de argumentos
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <URL>" << endl;
        return 1;
    }
    string url = argv[1];

    //Valida la url de que empiece por https o http
    if (url.substr(0, 7) != "http://" && url.substr(0, 8) != "https://") {
        cerr << "Error: La URL debe comenzar con 'http://' o 'https://'" << endl;
        return 1;
    }

    // Generar QR
    QRcode* qrcode = QRcode_encodeString(url.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (!qrcode) {
        cerr << "Error al generar QR" << endl;
        return 1;
    }

    int tam = qrcode->width;
    // Guardar imagen en PNG
    genera_Qr(vector<unsigned char>(qrcode->data, qrcode->data + tam * tam), tam, "codigo_qr.png");

    QRcode_free(qrcode);
    return 0;
}