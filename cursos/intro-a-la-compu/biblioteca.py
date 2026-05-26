def main():
    # Declaración de variables
    codLibro = 101
    tituloLibro = "Cálculo Diferencial"
    categoriaLibro = "Matemáticas"
    estadoLibro = "disponible"
    nombreEstudiante = ""
    opcion = 0

    # Bucle principal
    while opcion != 4:
        print("--------------------------------")
        print("1. Prestar libro")
        print("2. Devolución del libro")
        print("3. Consultar disponibilidad")
        print("4. Salir")
        
        try:
            print("Seleccione una opción:")
            opcion = int(input())
        except ValueError:
            print("Error: Por favor ingrese un número válido.")
            opcion = 0  # Reiniciar opción para evitar bucles infinitos
            continue

        if opcion == 1:
            print("Ingrese código del libro (1-1000):")
            codIngresado = int(input())
            
            if (codIngresado < 1) or (codIngresado > 1000):
                print("Error: Código fuera de rango.")
            else:
                if codIngresado == codLibro:
                    if estadoLibro == "disponible":
                        print("Ingrese nombre del estudiante:")
                        nombreEstudiante = input()
                        estadoLibro = "prestado"
                        print("Libro ", tituloLibro, " prestado con éxito a ", nombreEstudiante)
                    else:
                        print("Error: El libro ya está prestado.")
                else:
                    print("Error: El libro no existe.")

        elif opcion == 2:
            print("Ingrese código del libro a devolver:")
            codIngresado = int(input())
            
            if codIngresado == codLibro:
                if estadoLibro == "prestado":
                    print("Ingrese días que duró el préstamo:")
                    diasPrestamo = int(input())
                    
                    estadoLibro = "disponible"
                    nombreEstudiante = ""
                    print("Libro ", tituloLibro, " liberado (disponible nuevamente).")
                    
                    if diasPrestamo > 5:
                        multa = (diasPrestamo - 5) * 1000.0
                        diasSuspension = 15
                        print("Multa: $", multa)
                        print("Suspensión: ", diasSuspension, " días.")
                    else:
                        print("Devolución dentro del plazo. Sin multa.")
                else:
                    print("Error: El libro no estaba prestado.")
            else:
                print("Error: Código incorrecto.")

        elif opcion == 3:
            print("Ingrese código del libro a consultar:")
            codIngresado = int(input())
            
            if codIngresado == codLibro:
                print("Título: ", tituloLibro)
                print("Categoría: ", categoriaLibro)
                print("Estado: ", estadoLibro)
            else:
                print("Error: Libro no encontrado.")

        elif opcion == 4:
            print("Sistema cerrado. ¡Hasta luego!")

        else:
            print("Opción inválida. Intente nuevamente.")

if __name__ == "__main__":
    main()