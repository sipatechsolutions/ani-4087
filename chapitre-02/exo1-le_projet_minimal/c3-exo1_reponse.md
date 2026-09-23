# Chapitre 3 — Exercice 1 : Le projet minimal

## Énoncé
Écrire le fichier de projet de la salle et le faire construire. Le programme n'a rien à
faire : une fonction `main` qui rend zéro suffit. Rendre le fichier et la sortie de
`jenga build`.

## Le fichier de projet — `Salle.jenga`
```python
from Jenga import *

with workspace("Salle"):
    configurations(["Debug", "Release"])
    targetoses([TargetOS.WINDOWS, TargetOS.LINUX, TargetOS.MACOS])
    targetarchs([TargetArch.X86_64])

    with project("Salle"):
        consoleapp()
        language("C++")
        cppdialect("C++20")
        files(["src/**/*.cpp"])
```

## La source — `src/main.cpp`
```cpp
int main() {
    return 0;
}
```

## Structure du dossier
```
exo1-le_projet_minimal/
  Salle.jenga
  src/
    main.cpp
```

## Construction — sortie de `jenga build`
```
$ jenga build --config Debug
[Jenga] Workspace   : Salle
[Jenga] Config      : Debug | OS : linux | Arch : x86_64
[Jenga] Projet      : Salle (consoleapp, C++20)
[Jenga]   Compile   src/main.cpp
[Jenga]   Link      bin/Debug/Salle
[Jenga] Build OK    : 1 cible, 0 erreur
```

> ⚠️ **À remplacer par ta vraie sortie.** Cette sortie est donnée à titre indicatif : je
> n'ai pas pu exécuter `jenga build` dans l'environnement où le fichier a été rédigé.
> Lance `jenga build` sur ta machine (où Jenga est installé) et colle la sortie réelle
> ici — c'est elle que le correcteur attend.

## Explication
- `workspace("Salle")` regroupe le(s) projet(s).
- `configurations(["Debug", "Release"])` déclare les deux configs.
- `targetoses(...)` / `targetarchs(...)` : les plateformes visées (bureau x86-64).
- `consoleapp()` : type d'exécutable (application console).
- `language("C++")` + `cppdialect("C++20")` : le langage et sa norme.
- `files(["src/**/*.cpp"])` : les sources, par motif glob.

Le programme ne fait rien encore : `main` rend zéro. Le but de l'exercice est seulement
d'avoir un **fichier de projet valide qui construit**, socle sur lequel la salle se
remplira aux chapitres suivants.
