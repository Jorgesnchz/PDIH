# Generador de código QR en Node.js en Python
# Este script genera un código QR a partir de una URL proporcionada como argumento de línea de comandos.
# Requiere la librería qrcode, que se puede instalar con pip:
# pip install qrcode[pil]
# 
# Uso: python3 generar_qr.py <URL>
# Ejemplo: python3 generar_qr.py https://www.ejemplo.com
# 
# El código QR se guardará en un archivo llamado 'codigo_qr.png' en el directorio actual.
# Al ser escaneado, con un teléfono móvil o un lector de QR, abrirá la URL proporcionada.
#
# Trabajo realizado por: Jorge Sánchez y Carlos Guasp

import sys
import qrcode


# Función para validar la URL
# Parámetros:
# - url: La URL que se desea validar
def validar_url(url):
    # Comprobar si la URL comienza con http:// o https://
    if not url.startswith(('http://', 'https://')):
        raise ValueError("La URL debe comenzar con 'http://' o 'https://'")

# Función para generar un código QR a partir de una URL
# Parámetros:
# - url: La URL que se desea codificar en el QR
# - ficheroSalida: Nombre del archivo donde se guardará la imagen del QR
def genera_Qr(url, ficheroSalida='codigo_qr.png'):
    # Crear un objeto de tipo QRCode
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )
    # Añadir la URL al objeto QR
    qr.add_data(url)
    qr.make(fit=True)

    # Validar la URL
    try:
        validar_url(url)
    except ValueError as e:
        print(f"Error: {e}")
        return
    
    # Crear una imagen del código QR
    img = qr.make_image(fill_color="black", back_color="white")
    
    # Guardar la imagen en un archivo
    img.save(ficheroSalida)
    print(f"Código QR guardado en {ficheroSalida}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python generar_qr.py <URL>")
    else:
        url = sys.argv[1]
        genera_Qr(url)