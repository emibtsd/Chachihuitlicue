# Práctica 4 - Clase

Este apartado contiene los archivos desarrollados durante la sesión de clase, enfocada en la configuración básica de pines como entradas digitales y el uso seguro de pulsadores.

## Contenido de la carpeta
* **`practica4.X.production.hex`**: Archivo compilado con el código del ejercicio desarrollado en clase.
* **`practica4.pdsprj`**: Simulación del circuito base en Proteus.
* **`Clase 4.png`**: Captura de pantalla del circuito funcionando en el simulador.

## Descripción del Ejercicio de Clase
El objetivo principal de esta actividad fue aprender a leer señales externas (entradas digitales) mediante el uso de botones y controlar actuadores simples (LEDs), optimizando las conexiones de hardware.

### Funcionamiento del Circuito
* **Entradas:** Se configuraron 3 botones conectados de forma independiente a tres pines del **Puerto B** (PORTB).
* **Salidas:** Se configuraron 3 LEDs conectados en otro puerto del microcontrolador.
* **Lógica:** Al presionar cada uno de los botones individuales, el microcontrolador detecta el cambio de estado y enciende o apaga el LED correspondiente asignado en el código.

### Uso de Resistencias de Pull-up Internas
Una parte crucial de la clase fue habilitar por software las **resistencias de Pull-up internas** del Puerto B. 
* Esto evita la necesidad de conectar físicamente resistencias externas en la simulación para mantener un estado lógico estable (`1` lógico) cuando los botones no están presionados.
* Al presionar un botón, el pin se conecta directamente a tierra (GND), cambiando el estado a un `0` lógico, el cual es interpretado por el programa para accionar el LED correspondiente.

## Evidencia del circuito de clase
A continuación se muestra el diseño del circuito con los 3 botones al Puerto B y sus respectivos LEDs:

![Evidencia del circuito de clase](Clase%204.png)
