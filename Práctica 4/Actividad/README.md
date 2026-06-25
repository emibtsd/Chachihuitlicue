# Práctica 4: Actividad

Este apartado contiene el desarrollo de la **Actividad de la Práctica 4**, donde se diseñó un contador manual de dos dígitos (00 a 99) controlado por el usuario mediante botones y visualizado en displays de 7 segmentos.

## Contenido de la carpeta
* **`practica44.X.production.hex`**: Archivo binario compilado listo para cargar en el microcontrolador.
* **`practica44.pdsprj`**: Simulación del circuito interactivo en Proteus.
* **`Actividad 4.png`**: Captura del circuito y la distribución de los componentes.

## Funcionamiento del Sistema

El circuito consta de una interfaz de control basada en tres botones (pulsadores) que modifican el valor del conteo:
1. **Botón de Incremento (+1):** Suma una unidad al contador cada vez que se presiona, avanzando del 00 al 99.
2. **Botón de Decremento (-1):** Resta una unidad al contador, permitiendo regresar en el conteo.
3. **Botón de Reset:** Reinicia instantáneamente el valor del contador a cero (`00`).

### Lógica de Visualización (Multiplexación)
Para mostrar las decenas y las unidades de forma independiente utilizando un número reducido de pines del microcontrolador, se implementó la técnica de **multiplexación por división de tiempo**. 

El programa alterna el encendido del display de decenas y de unidades a una frecuencia muy alta. Debido a la persistencia de la visión humana, el ojo percibe ambos displays encendidos en todo momento mostrando el número correcto, mientras el código escanea constantemente el estado de los tres botones.

## Evidencia de la simulación
A continuación se muestra el esquema del circuito desarrollado con los displays y la botonera en Proteus:

![Evidencia del circuito](Actividad%204.png)
