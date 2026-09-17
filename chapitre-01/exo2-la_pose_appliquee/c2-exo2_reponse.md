# Chapitre 2 — Exercice 2 : La pose appliquée

## Énoncé
Écrire la structure `Pose`, avec une position et un quaternion, et la fonction qui
applique une pose à un point : **rotation puis translation**. Le quaternion est donné par
ses quatre composantes, déjà normalisé. Le programme lit une pose et un point, et affiche
le point transformé.

## Structure et fonction
```cpp
struct Vec3 { double x, y, z; };
struct Quat { double x, y, z, w; };            // deja normalise
struct Pose { Vec3 position; Quat orientation; };

// rotation d'un vecteur par un quaternion normalise :
//   v' = v + 2w (u x v) + 2 u x (u x v)   avec u = (qx, qy, qz)
// puis translation par la position :
//   applique_pose(p, point) = rotate(p.orientation, point) + p.position
```
L'ordre est **rotation d'abord, translation ensuite** : on tourne le point autour de
l'origine, puis on l'amène à la position de la pose. L'inverse donnerait un point au
mauvais endroit.

## Entrée / sortie
- **Entrée** : 10 réels — `position (px py pz)`, `quaternion (qx qy qz qw)`, `point (x y z)`.
- **Sortie** : le point transformé, `x y z`, 4 décimales.

```
g++ -std=c++17 -O2 la_pose_appliquee.cpp -o pose
echo "0 0 0  0 0.7071067811865476 0 0.7071067811865476  1 0 0" | ./pose
```

## Exemples d'exécution (vérifiés)

| Entrée (pos | quat | point) | Effet | Sortie |
|-------------------------------|-------|--------|
| `0 0 0 \| 0 0.70711 0 0.70711 \| 1 0 0` | rotation 90° autour de Y | `0.0000 0.0000 -1.0000` |
| `10 20 30 \| 0 0 0 1 \| 1 2 3` | identité + translation | `11.0000 22.0000 33.0000` |
| `5 0 0 \| 0 0.70711 0 0.70711 \| 1 0 0` | rotation 90°/Y puis translation | `5.0000 0.0000 -1.0000` |

La rotation de 90° autour de Y envoie bien `+X` sur `-Z`, ce qui confirme l'ordre et le
sens de la rotation.

## Conclusion
Une pose = position + quaternion. L'appliquer à un point, c'est le **tourner** (par le
quaternion, supposé normalisé) **puis le translater** (par la position). La formule de
rotation par quaternion évite de passer par une matrice et reste exacte tant que le
quaternion est normalisé.

> Convention d'entrée du quaternion : ordre `(x, y, z, w)`. Si le chapitre attend
> `(w, x, y, z)`, il suffit d'inverser l'ordre de lecture des quatre composantes.
