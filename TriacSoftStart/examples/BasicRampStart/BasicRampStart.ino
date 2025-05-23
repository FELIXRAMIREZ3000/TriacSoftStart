// Incluimos la biblioteca que creamos: TriacSoftStart
// Esta biblioteca contiene toda la lógica para manejar el arranque suave del motor
#include <TriacSoftStart.h>

// Creamos un objeto llamado "bomba" usando la clase TriacSoftStart
// Los parámetros son los pines que usaremos:
// (pin de entrada desde el detector de cruce por cero, salida hacia el MOC3021, pin de control, pin del LED)
TriacSoftStart bomba(2, 5, 4, 13);

void setup() {
  // Inicializamos el sistema de arranque suave
  // Esto configura los pines y establece los valores iniciales de la rampa
  bomba.begin();

  // Conectamos una interrupción al pin 2 (entrada de cruce por cero)
  // Cada vez que cambia el estado (subida o bajada), se ejecuta la función zeroCrossISR()
  // Esto es necesario para sincronizar el encendido del TRIAC con la red eléctrica
  attachInterrupt(digitalPinToInterrupt(2), zeroCrossISR, CHANGE);
}

void loop() {
  // Esta función debe llamarse en cada vuelta del loop
  // Se encarga de:
  // - Verificar si el botón de control está presionado
  // - Cambiar el parpadeo del LED (rápido si está arrancando, lento si ya está en operación normal)
  // - Reiniciar la rampa si hubo un flanco de subida en el pin de control
  bomba.update();
}

// Esta es la función que se llama cada vez que el pin 2 detecta un cambio
// Se ejecuta desde la interrupción, y le dice a la biblioteca que hubo un cruce por cero
// En base a esto, la biblioteca decidirá si dispara el TRIAC (y cuándo)
void zeroCrossISR() {
  bomba.onZeroCross();
}
