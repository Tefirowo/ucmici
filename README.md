<div align="center">
<table width="100%" cellpadding="10" cellspacing="0" border="1" bgcolor="#c0c0c0">
<tr>
<td>

# Ignacia Stephanie C.

**Repositorio académico de Ingeniería Civil Informática**

`UCM · Talca · Chile`

[GitHub](https://github.com/Tefirowo) |
[Correo](mailto:ignacia.carrera@alumnos.ucm.cl) |
[novahosting.cl](https://novahosting.cl)

</td>
</tr>
</table>
</div>

<table width="100%" cellpadding="8" cellspacing="0" border="1">
<tr>
<td width="180" valign="top" bgcolor="#d9e8ff">

**Navegación**

- [Inicio](#inicio)
- [Actividades](#actividades)
- [Tarea 1.2 U3](#tarea-12-u3)
- [Archivos](#estructura-de-archivos)
- [Tecnologías](#tecnologias)
- [Git](#git)
- [Contacto](#contacto)

</td>
<td valign="top">

<a name="inicio"></a>

## Inicio

Este repositorio reúne tareas, ejercicios y proyectos desarrollados durante
la carrera de Ingeniería Civil Informática. Su propósito es conservar el
trabajo académico, documentar avances y practicar control de versiones con
Git y GitHub.

Estudiante: **Ignacia Stephanie C.**<br>
Universidad: **Universidad Católica del Maule**<br>
Ciudad: **Talca, Chile**

</td>
</tr>
</table>

---

<a name="actividades"></a>

## Actividades

| Curso | Actividad | Estado | Archivos |
|---|---|:---:|---|
| Taller de programación | Tarea 1.2 - Unidad 3 | Completa | [Código](./cursos/Programación/TallerFormativo%20Framework/Pruebas%20unitarias2/test_funciones.c) · [PDF](./cursos/Programación/TallerFormativo%20Framework/Pruebas%20unitarias2/documento_entrega.pdf) · [Ejecutable](./cursos/Programación/TallerFormativo%20Framework/Pruebas%20unitarias2/test_funciones.exe) |
| Taller de programación | Tarea 1.1 - Unidad 3 | Disponible | [Carpeta](./cursos/Programación/TallerFormativo%20Framework/) |
| Taller de programación | Ejercicios anteriores | Disponible | [Código](./cursos/Programación/) |

---

<a name="tarea-12-u3"></a>

## Tarea 1.2 U3 - Pruebas unitarias en ANSI C

**Actividad:** Diseño e implementación de pruebas para una función pura y dos
funciones con efectos secundarios.

### Entregables

| Archivo | Contenido |
|---|---|
| [test_funciones.c](./cursos/Programación/TallerFormativo%20Framework/Pruebas%20unitarias2/test_funciones.c) | Código corregido y harness de pruebas |
| [documento_entrega.pdf](./cursos/Programación/TallerFormativo%20Framework/Pruebas%20unitarias2/documento_entrega.pdf) | Tabla de casos, justificación y reflexión |
| [test_funciones.exe](./cursos/Programación/TallerFormativo%20Framework/Pruebas%20unitarias2/test_funciones.exe) | Programa compilado para Windows |

### Funciones probadas

| Función | Clasificación | Verificación |
|---|---|---|
| `maximo_tres` | Función pura | Valor de retorno |
| `intercambiar` | Efecto secundario | Estado de ambas variables |
| `invertir_arreglo` | Efecto secundario | Estado completo del arreglo |

### Casos de prueba

Los casos cubren valores normales, cero, valores iguales, números negativos,
tamaños cero y uno, números extremos y arreglos de distintas longitudes.

```text
Pruebas pasadas: 19
Pruebas fallidas: 0
Estado: APROBADO
```

### Compilación

```bash
cd "cursos/Programación/TallerFormativo Framework/Pruebas unitarias2"

gcc -Wall -Wextra -std=c89 -o test_funciones test_funciones.c
test_funciones.exe
```

---

<a name="estructura-de-archivos"></a>

## Estructura de archivos

```text
ucmiciceo/
|
|-- README.md
|-- uceeme.png
|-- .gitignore
|
|-- cursos/
|   `-- Programación/
|       |-- TallerFormativo Framework/
|       |   `-- Pruebas unitarias2/
|       |       |-- test_funciones.c
|       |       |-- test_funciones.exe
|       |       `-- documento_entrega.pdf
|       |
|       |-- BACKTRACKRatoncio.c
|       |-- Tarea 1.3-U2  .pdf
|       |-- Tarea vector4.c
|       `-- ...
|
|-- Proyectos/
|   |-- musical.strudel
|   |-- programacion-competitiva
|   |-- test.c
|   `-- test1/
|
|-- .vscode/
`-- .venv/
```

**`cursos/`** contiene trabajos y apuntes organizados por asignatura.<br>
**`Proyectos/`** contiene ejercicios y proyectos independientes.<br>
**`.vscode/`** contiene configuración del editor.<br>
**`.venv/`** contiene el entorno virtual local.

---

<a name="tecnologias"></a>

## Tecnologías

| Área | Herramientas |
|---|---|
| Programación | ANSI C, GCC |
| Sistemas | Git, GitHub, Visual Studio Code |
| Hardware | Arduino y electrónica |
| Desarrollo web | HTML, CSS |
| Entorno | Windows, Visual Studio Code |

---

<a name="git"></a>

## Git

```bash
git clone https://github.com/Tefirowo/ucmiciceo.git
git status
git add .
git commit -m "Actualiza el repositorio"
git push origin main
git pull
```

---

<a name="contacto"></a>

## Contacto

- GitHub: [github.com/Tefirowo](https://github.com/Tefirowo)
- Correo: [ignacia.carrera@alumnos.ucm.cl](mailto:ignacia.carrera@alumnos.ucm.cl)
- Proyecto personal: [novahosting.cl](https://novahosting.cl)

---

<div align="center">
<font face="Courier New, monospace" size="2">
FIN DEL DOCUMENTO · UCM · TALCA
</font>
</div>
