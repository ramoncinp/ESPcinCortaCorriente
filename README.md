# ESPcinCortaCorriente

Algoritmo!<br/>
1.- Inicialización de pines<br/>
2.- 10 segundos de retardo<br/>
3.- Se lee el estado actual del sensor,<br/>
  si NO es 0, activa la bandera para contar<br/>
  si ES 0, desactiva la bandera para contar<br/>
4.- Si esta activa la bandera para contar, cuenta cada segundo.<br/> 
  4.1- Si llega a 45 segunods desde que se activó la bandera, corta corriente (IN1 desactivado)<br/>
5.- Si cambió el estado del sensor y paso el tiempo de debounce, evaluar:<br/>
  5.1- Si cambió a 0, se reiniciar el contador para cortar corriente y se desactiva la bandera<br/>
  5.2- Si cambió a 1, se activa la bandera para contar (empezaría otra vez a contar desde 0)<br/>
