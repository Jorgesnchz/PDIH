// Generador de código QR en Node.js en JavaScript
// Este script genera un código QR a partir de una URL proporcionada como argumento de línea de comandos.
// Requiere la biblioteca 'qrcode' que se puede instalar con 'npm install qrcode'
//
// Uso: node generar_qr.js <URL>
// Ejemplo: node generar_qr.js https://www.ejemplo.com
//
// Al ejecutar el script, se generará un archivo PNG con el código QR en el directorio actual.
// Escaneando el código QR, se abrirá la URL proporcionada en un navegador web.
//
// Trabajo realizado por: Jorge Sánchez y Carlos Guasp


// Importa la biblioteca 'qrcode' para generar códigos QR
const QRCode = require('qrcode');

const url = process.argv[2];

// Verifica si hay un argumento de tipo URL
if (!url) {
  console.log('Uso: node generar_qr.js <URL>');
  process.exit(1);
}

// Archivo de salida donde se guardará el código QR generado
const ficheroSalida = 'codigo_qr.png';

// Genera el código QR y lo guarda en un archivo PNG
QRCode.toFile(ficheroSalida, url, {
  width: 350,
  errorCorrectionLevel: 'H',
}, function (err) {
  if (err) throw err;
  console.log(`Código QR guardado en ${ficheroSalida}`);
});