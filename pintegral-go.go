package main

import (
	"fmt"     // Print
	"os"      // Arguments passed to the program
	"strconv" // Atoi
)

var nRect uint32 = 0
var nRutinas uint32 = 0

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

	fmt.Printf("Integral de %d rectángulos (%d goroutines)\n", nRect, nRutinas)

	os.Exit(0)
}
