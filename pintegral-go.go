package main

import (
	"fmt"     // Print
	"os"      // Arguments passed to the program
	"strconv" // Atoi
	"time"
)

var nRect uint32 = 0
var nRutinas uint32 = 0
var anchRect float64 = 0
var areaTotal float64 = 0

func f(x float64) (y float64) {
	return 4.0 / (1.0 + x*x)
}

// Tarea que cada goroutine tiene que realizar
func calculaArea(nRutina int, nAreas uint32, rectInicio uint32, ptr *float64) {
	var devolver float64 = 0

	for i := rectInicio; i <= rectInicio+nAreas; i++ {
		devolver = devolver + f(anchRect*(float64(i)+0.5))
	}

	fmt.Printf("Rutina %d, %f (%d áreas[%d-%d])\n", nRutina+1, devolver, nAreas, rectInicio, rectInicio+nAreas-1)
	*ptr = devolver
}

func main() {
	// Comprobar número de parámetros
	if len(os.Args) < 3 {
		fmt.Println("Uso: pintegral-go <nº de rectangulos> <nº de hilos>")
		os.Exit(1)
	}

	inicio := time.Now()

	// Parsear parámetros
	nRect, _ := strconv.Atoi(os.Args[1])
	nRutinas, _ := strconv.Atoi(os.Args[2])

	if nRect == 0 || nRutinas == 0 {
		fmt.Println("Los parámetros deben ser mayores de 0")
	}

	// Calcular anchura del intervalo
	anchRect = 1.0 / float64(nRect)
	// Array de áreas parciales
	//var areasParciales [nRutinas]float64
	areasParciales := make([]float64, nRutinas)
	// Array de rectángulos por cada goroutine
	//var tareas [nRutinas]uint32
	tareas := make([]uint32, nRutinas)

	// Rellenar el array de areas parciales (si no se usa no compila)
	for i := 0; i < nRutinas; i++ {
		areasParciales[i] = float64(-1.0)
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

	var rectInicio uint32 = 0
	// Llamada a cada tarea y creación de las goroutines
	for i := 0; i < nRutinas; i++ {
		go calculaArea(i, tareas[i], rectInicio, &areasParciales[i])
		// El siguiente tendrá su primer rectángulo
		rectInicio += tareas[i]
	}

	for i := 0; i < nRutinas; i++ {
		// Recorremos las áreas parciales para ver si están calculadas y si no, nos quedamos ahí
		if areasParciales[i] == -1.0 {
			i--
		} else {
			areaTotal += areasParciales[i]
		}
	}

	areaTotal *= anchRect

	fin := time.Since(inicio)
	fmt.Printf("π = %f (%v)\n", areaTotal, fin)

	os.Exit(0)
}
