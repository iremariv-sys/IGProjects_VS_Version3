# Copilot Instructions

## General Guidelines
- No usar `auto` en el código C++; preferir tipos explícitos.
- No usar `dynamic_cast` en el código C++; preferir alternativas sin RTTI cuando sea posible.
- Reutilizar el código y las clases ya existentes en lugar de volver a implementar funcionalidades desde cero.

## Project-Specific Rules
- Mantener el método `setColor` en `ColorMaterialEntity` durante la migración a material, en lugar de eliminarlo o reemplazarlo por una API distinta.
- Al agregar iluminación al proyecto, no modificar las escenas, las formas ni la lógica de normales; solo realizar los cambios estrictamente necesarios para las luces.
- Aclarar si una pregunta sobre «malla de revolución» se refiere a `ADNStructure` o al proyecto en general; `ADNStructure` usa cajas, mientras que objetos como `Cone`/`Disk` usan mallas por revolución. Si hay ambigüedad, pedir aclaración.