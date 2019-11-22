# ESPcinCortaCorriente

Algoritmo!
1.- Inicialización de pines
2.- 10 segundos de retardo
3.- Se lee el estado actual del sensor,
  si NO es 0, activa la bandera para contar
  si ES 0, desactiva la bandera para contar
4.- Si esta activa la bandera para contar, cuenta cada segundo. 
  4.1- Si llega a 45 segunods desde que se activó la bandera, corta corriente (IN1 desactivado)
5.- Si cambió el estado del sensor y paso el tiempo de debounce, evaluar:
  5.1- Si cambió a 0, se reiniciar el contador para cortar corriente y se desactiva la bandera
  5.2- Si cambió a 1, se activa la bandera para contar (empezaría otra vez a contar desde 0)
