## Puntos Generales 
- Representacion de voxeles para representar geometria compleja en gpu
- Presentando una estructura de datos compacta para almacenar los voxeles
- Algoritmo eficiente para realizar raycast en la estructura
- Se añade nueva informacion (Contornos) para aumentar la resolucion geometrica, permite una codificación más compacta de superficies suaves, y acelera la proyección de rayos
- Se emplea tambien un metodo de compresion para los vectores normales(Normals) de alta precision
- se aplica una tecnica de filtrado de postprocesado de radio variable
- y finalmente se demuestra la competitivida de la extructura frente a una representacion de triangulos
