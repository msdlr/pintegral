package main

import (
	"fmt"     // Print
	"os"      // Arguments passed to the program
	"strconv" // Atoi
)

var nRect uint32 = 0
var nRutinas uint32 = 0
var anchRect float64 = 0

func f(x float64) (y float64) {
	return 4.0 / (1.0 + x*x)
}

// Tarea que cada goroutine tiene que realizar
func calculaArea(nRutina int, nAreas uint32) {
	fmt.Printf("Rutina %d: %d areas\n", nRutina+1, nAreas)

}

func main() {
	// Comprobar número de parámetros
	if len(os.Args) < 3 {
		fmt.Println("Uso: pintegral-go <nº de rectangulos> <nº de hilos>")
		os.Exit(1)
	}

	// Parsear parámetros
	nRect, _ := strconv.Atoi(os.Args[1])
	nRutinas, _ := strconv.Atoi(os.Args[2])

	if nRect == 0 || nRutinas == 0 {
		fmt.Println("Los parámetros deben ser mayores de 0")
	}

	// Calcular anchura del intervalo
	anchRect = 1.0 / float64(nRect)

	// Array de áreas parciales
	//var areasParciales [nRect]float64
	areasParciales := make([]float64, nRect)
	// Array de rectángulos por cada goroutine
	//var tareas [nRutinas]uint32
	tareas := make([]uint32, nRutinas)

	// Rellenar el array de areas parciales (si no se usa no compila)
	for i := 0; i < nRect; i++ {
		areasParciales[i] = float64(0)
	}

	// Resto de dividir el número de rectángulos entre el de goroutines
	restoRect := nRect % nRutinas
	// Calcular el número de rectángulos que tocan a cada goroutine
	for i := 0; i < nRutinas; i++ {
		tareas[i] = uint32(nRect / nRutinas)
		// Si quedan tareas por repartir van a las primeras goroutines
		if restoRect > 0 {
			tareas[i]++
			restoRect--
		}
	}

	fmt.Printf("Integral de %d rectángulos, anchura %f (%d goroutines)\n", nRect, anchRect, nRutinas)

	// Llamada a cada tarea y creación de las goroutines
	for i := 0; i < nRutinas; i++ {
		calculaArea(i, tareas[i])
	}

	os.Exit(0)
}
