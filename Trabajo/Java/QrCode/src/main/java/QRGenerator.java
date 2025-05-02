// Generador de código QR en Java
// Este programa genera un código QR a partir de una URL proporcionada como argumento de línea de comandos.
// Requiere la biblioteca ZXing para la generación de códigos QR.
//
// Para compilar y ejecutar este programa es recomendable usar un IDE como IntelliJ IDEA ya que facilita la
// compilación y ejecución del proyecto de Maven.
//
// Uso (IteliJ IDEA):
// 1. Selecciona el archivo QRGenerator.java en el panel de la izquierda.
// 2. Haz clic derecho y selecciona "Run 'QRGenerator.main()'".
// 3. En la ventana de ejecución, proporciona la URL que deseas codificar en el código QR como parametro.
// 4. El código QR se generará y se guardará como "codigo_qr.png" en el directorio de trabajo actual.
// 
// Trabajo realizado por: Jorge Sánchez y Carlos Guasp


import com.google.zxing.BarcodeFormat;
import com.google.zxing.WriterException;
import com.google.zxing.qrcode.QRCodeWriter;
import com.google.zxing.common.BitMatrix;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * Clase QRGenerator
 * Esta clase genera un código QR a partir de una URL proporcionada como argumento de línea de comandos.
 * El código QR se guarda como una imagen PNG en el directorio de trabajo actual.
 */
public class QRGenerator {
    // Este método recibe una URL como argumento y genera un código QR a partir de ella.
    public static void main(String[] args) {
        // Verifica que se haya proporcionado un argumento
        if (args.length != 1) {
            System.out.println("Uso: java QRGenerator <URL>");
            return;
        }

        // Obtiene la URL del argumento y la verifica
        String url = args[0];
        
        if (!url.startsWith("http://") && !url.startsWith("https://")) {
            System.out.println("La URL debe comenzar con 'http://' o 'https://'");
            return;
        }
        
        // Fichero de salida
        String ficheroSalida = "codigo_qr.png";

        // Genera el código QR y lo guarda en el fichero de salida
        try {
            genera_Qr(url, 350, ficheroSalida);
            System.out.println("Código QR guardado en " + ficheroSalida);
        } catch (WriterException | IOException e) {
            System.out.println("Error al generar el código QR: " + e.getMessage());
        }
    }

    /**
     * Genera un código QR a partir de una cadena de texto y lo guarda como una imagen PNG.
     *
     * @param Data La cadena de texto que se codificará en el código QR.
     * @param tam El tamaño del código QR.
     * @param ficheroSalida La ruta del archivo donde se guardará la imagen del código QR.
     * @throws WriterException Si ocurre un error al generar el código QR.
     * @throws IOException Si ocurre un error al guardar la imagen.
     */
    private static void genera_Qr(String Data, int tam, String ficheroSalida)
            throws WriterException, IOException {
        QRCodeWriter qrCodeWriter = new QRCodeWriter();

        BitMatrix bitMatrix = qrCodeWriter.encode(Data, BarcodeFormat.QR_CODE, tam, tam);

        BufferedImage bufferedImage = new BufferedImage(tam, tam, BufferedImage.TYPE_INT_RGB);
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                // Establece el color del píxel en blanco o negro
                int color = (bitMatrix.get(i, j)) ? 0xFF000000 : 0xFFFFFFFF;
                bufferedImage.setRGB(i, j, color);
            }
        }
        
        // Guarda la imagen como un archivo PNG
        ImageIO.write(bufferedImage, "png", new File(ficheroSalida));
    }
}