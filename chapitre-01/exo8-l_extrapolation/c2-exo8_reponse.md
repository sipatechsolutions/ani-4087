# Chapitre 2 — Exercice 8 : L'extrapolation

## Énoncé
Écrire la fonction qui avance une pose de `dt` secondes à vitesses constantes, linéaire
et angulaire. Le programme lit une pose, ses deux vitesses et une durée, et affiche la
pose extrapolée. Traiter le cas d'une vitesse angulaire nulle sans diviser par zéro.

## La fonction
```cpp
Pose avancer(const Pose& p, Vec3 v_lin, Vec3 w, double dt);
```
- **Position** : intégration linéaire simple — `p + v_lin * dt`.
- **Orientation** : on tourne d'un `delta` correspondant à la vitesse angulaire `w`
  (vecteur axe × rad/s) pendant `dt` :
  - `|w|` = norme de la vitesse angulaire (rad/s) ;
  - angle total = `|w| * dt`, axe = `w / |w|` ;
  - `delta = ( axe * sin(angle/2), cos(angle/2) )`, puis `q_new = delta * q`.

## Le cas de la vitesse angulaire nulle (pas de division par zéro)
Si `|w|` est ~0, l'axe `w/|w|` n'existe pas — diviser donnerait `0/0`. On teste donc `|w|`
avant :
```cpp
if (vitesse < 1e-12) delta = {0,0,0,1};      // identite : aucune rotation, aucun /0
else { double s = sin(angle/2) / vitesse;    // sin(angle/2) * (1/|w|) : axe normalise
       delta = { w.x*s, w.y*s, w.z*s, cos(angle/2) }; }
```
Astuce : en factorisant `sin(angle/2)/|w|`, on multiplie ensuite par les composantes
brutes de `w`, ce qui normalise l'axe sans jamais calculer `w/|w|` séparément.

## Tests (vérifiés)
Entrée : `px py pz  qx qy qz qw  vx vy vz  wx wy wz  dt`.
```
g++ -std=c++17 -O2 l_extrapolation.cpp -o extrapo
```

| Cas | Entrée | Sortie |
|-----|--------|--------|
| 90°/s autour de Z, v=(1,0,0), dt=1 | `0 0 0  0 0 0 1  1 0 0  0 0 1.5708  1` | pos `1.0000 0.0000 0.0000` · quat `0 0 0.7071 0.7071` |
| **vitesse angulaire nulle**, v=(1,0,0), dt=2 | `0 0 0  0 0 0 1  1 0 0  0 0 0  2` | pos `2.0000 0.0000 0.0000` · quat `0 0 0 1` |
| 90°/s autour de Z pendant 2 s (= 180°) | `0 0 0  0 0 0 1  0 0 0  0 0 1.5708  2` | pos `0 0 0` · quat `0 0 1.0000 0.0000` |

Le cas à vitesse angulaire nulle renvoie bien le quaternion identité, sans division par
zéro.

## Conclusion
Avancer une pose à vitesses constantes = translation linéaire pour la position, et
rotation d'axe `w/|w|` et d'angle `|w|*dt` pour l'orientation. Le seul point délicat est
la vitesse angulaire nulle : on le traite en renvoyant l'identité, ce qui évite le `0/0`.
C'est le modèle à vitesses constantes utilisé pour la prédiction — valable sur un court
horizon (cf. la borne des ~100 ms au-delà de laquelle il « ment plus qu'il n'aide »).
