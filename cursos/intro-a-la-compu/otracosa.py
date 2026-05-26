if __name__ == "__main__":
    try:
        n = int(input("¿Cuántas iteraciones quieres? "))
    except ValueError:
        print("Por favor ingresa un número entero.")
        exit(1)

    nombre_archivo = input("Nombre del archivo (sin .txt, Enter para solo imprimir): ").strip()

    lineas = []
    for a in range(1, n + 1):
        for b in range(1, n + 1):
            c = a + b
            lineas.append("     Si")
            lineas.append(f"        numero1 = {a} Y numero2 = {b} Entonces")
            lineas.append(f'            Escribir "{a} + {b} = {c}"')
            lineas.append("")

    resultado = "\n".join(lineas)
    print("\n" + resultado)

    if nombre_archivo:
        with open(f"{nombre_archivo}.txt", "w", encoding="utf-8") as f:
            f.write(resultado)
        print(f'\nArchivo guardado como "{nombre_archivo}.txt"')