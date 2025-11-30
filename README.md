# Administración de salas de cine - Programacion II

## Informacion del grupo
- **Número de grupo:** 40  
- **Integrantes activos:** Christian Fernando Medina, Martina Rebeca Garcia Vior, Diego Graus, Diego Esteban Paz
- **Tipo de proyecto:** Gestión  

## Descripción del projecto
Nuestro programa se orienta a la administracion, funcionamiento y facilitacion general de salas de cine, pero el objetivo principal del programa es la venta de entradas.
Este permite registrar y administrar películas, salas, clientes y ventas de entradas, además de controlar la disponibilidad de butacas para cada función.  

## Funcionalidades adicionales
- Menú principal con acceso a todos los módulos.  
- Alta, baja y modificación lógica de registros.  
- Sistema de backup y restauración de archivos.  
- Validaciones de datos en las operaciones principales.  

## Archivos de datos utilizados
- `Clientes.dat`-`Cliente` | Guarda diversos datos correspondientes a cada cliente registrado en el sistema.
- `Pelicula.dat`-`Pelicula` | Contiene la información tecnica de las películas registradas en el sistema - (nombre, director, género, clasificación, etc.).
- `Salas.dat`-`Sala` | Registra las salas del cine con su capacidad y tipo.
- `SalaOcupacion.dat`-`SalaOcupacion` | Controla la disponibilidad de butacas por sala y fecha. 
- `Ventas.dat`-`Venta` | Registra cada venta de entradas con su respectiva película, sala, cliente y fecha.

## Clases principales
- `Cliente` | dni, nombre, apellido, email, estado, numero de telefono | Representa a un cliente del cine. 
- `Pelicula` | idPelicula, nombre, director, género, clasificación, fechaEstreno, estado | Define las películas que se proyectan.
- `Sala` | idSala, nombreSala, tipoSala, capacidadSala, estado | Contiene la información de las salas del cine. 
- `SalaOcupacion` | idSala, fechaFuncion, butacasDisponibles, estado | Maneja la ocupación y disponibilidad de butacas por función.
- `Venta` | idVenta, idPelicula, idSala, fechaProyeccion, dniComprador, cantidadEntradas, importeTotal, estado | Representa una venta realizada en el sistema.
- `Fecha` | dia, mes, año | Clase auxiliar para manejar fechas dentro del sistema.

## Reportes e informes
- Recaudación total por fecha.  
- Recaudación total por año.  
- Listado de películas activas e inactivas.  
- Listado de clientes activos o dados de baja.  
- Reporte de disponibilidad de salas según la función.  
- Listado general de ventas registradas.  
