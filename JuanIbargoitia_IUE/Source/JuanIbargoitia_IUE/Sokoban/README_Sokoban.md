# Sokoban (mínimo viable)

## Qué hay implementado en C++
- `ASokobanPawn`: movimiento en grid con WASD/flechas (1 casilla por input).
- `ASokobanCrate`: caja empujable (1 casilla).
- `ASokobanGoal`: objetivo.
- `ASokobanGameMode`: contadores, UI, victoria.
- `USokobanUI`: interfaz UMG (BlueprintImplementableEvent).

## Wiring rápido en el editor
1) Crea `WBP_MainMenu`, `WBP_SokobanHUD` (deriva de `SokobanUI`), `WBP_Victory` si quieres separado.
2) Crea `BP_SokobanGameMode` (deriva de `SokobanGameMode`) y asigna `UIWidgetClass = WBP_SokobanHUD`.
3) En `LVL_Sokoban`, en World Settings asigna `GameMode Override = BP_SokobanGameMode`.
4) Coloca actores `SokobanCrate` y `SokobanGoal` y edita su `GridPos`.
5) Define celdas bloqueadas desde `BP_SokobanGameMode` (array `BlockedCells`).

## Input
Este código espera acciones legacy en Project Settings > Input:
- `Sokoban_Up`: W, Up
- `Sokoban_Down`: S, Down
- `Sokoban_Left`: A, Left
- `Sokoban_Right`: D, Right

(Se eligió legacy para ir más rápido en 6h.)
