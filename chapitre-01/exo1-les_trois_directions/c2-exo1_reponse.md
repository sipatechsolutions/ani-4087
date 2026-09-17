# Chapitre 2 — Exercice 1 : Les trois directions

## Énoncé
Écrire les trois fonctions qui fixent la convention une fois pour toutes : `Avant()`,
`Haut()` et `Droite()`, qui rendent chacune un vecteur unitaire dans la convention du
module. Le programme lit trois réels, les traite comme un point, et affiche son produit
scalaire avec chacune des trois directions. Trois lignes, quatre décimales.

## Convention du module
| Direction | Vecteur unitaire | Axe |
|-----------|------------------|-----|
| `Avant()`  | (0, 0, 1) | +Z |
| `Haut()`   | (0, 1, 0) | +Y |
| `Droite()` | (1, 0, 0) | +X |

Repère à main gauche : +X à droite, +Y en haut, +Z vers l'avant (là où « regarde » la
pose, cf. `NkQuat::Forward()`).

## Le programme
Voir `les_trois_directions.cpp`. Le produit scalaire d'un point p = (x, y, z) avec chaque
direction **extrait la composante correspondante** :
- p · Avant()  = z
- p · Haut()   = y
- p · Droite() = x

```
g++ -std=c++17 -O2 les_trois_directions.cpp -o directions
echo "1 2 3" | ./directions
```

## Exemples d'exécution (vérifiés)

Entrée `1 2 3` :
```
3.0000
2.0000
1.0000
```

Entrée `0.5 -1.25 3.75` :
```
3.7500
-1.2500
0.5000
```

## Conclusion
Les trois fonctions renvoient les vecteurs unitaires de base de la convention du module.
Le produit scalaire d'un point avec l'une d'elles donne « combien ce point avance dans
cette direction » : avec `Avant()` on lit sa profondeur (z), avec `Haut()` sa hauteur (y),
avec `Droite()` son côté (x). Fixer ces trois fonctions une fois pour toutes évite
d'éparpiller la convention (et ses erreurs de signe) dans tout le code.

> Note : la convention (Avant = +Z, Haut = +Y, Droite = +X) est reprise des QCM du
> chapitre 2. Si le texte du chapitre fixe un signe différent (par ex. Avant = −Z à la
> manière d'OpenXR brut), il suffit de changer le vecteur correspondant dans les trois
> fonctions ; le reste du programme ne bouge pas.
