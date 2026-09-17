# Chapitre 2 — Exercice 5 : La composition de deux poses

## Énoncé
Écrire la composition de deux poses, puis vérifier sur un cas que **composer puis
appliquer** donne le même résultat qu'**appliquer l'une après l'autre**. Afficher les deux
points obtenus et leur écart.

## La composition
Appliquer `p1` puis `p2` à un point :
```
p'  = R1*p + t1
p'' = R2*p' + t2 = (R2*R1)*p + (R2*t1 + t2)
```
La pose composée (« p1 puis p2 ») est donc :
```cpp
Pose composer(const Pose& p1, const Pose& p2){
    Quat q = quat_mul(p2.orientation, p1.orientation);              // R2 * R1
    Vec3 t = add(rotate(p2.orientation, p1.position), p2.position); // R2*t1 + t2
    return { t, q };
}
```
- **orientation** = produit des quaternions `q2 * q1` (dans cet ordre : la 2e rotation
  agit après la 1re) ;
- **position** = translation de `p1` **tournée par la rotation de p2**, plus la translation
  de `p2`.

Le produit de quaternions utilisé est le produit de Hamilton (`quat_mul`).

## Vérification
On compare, pour un même point :
- **Chemin 1** : appliquer `p1`, puis appliquer `p2` au résultat ;
- **Chemin 2** : composer `p1` et `p2`, puis appliquer la pose composée.

```
g++ -std=c++17 -O2 la_composition.cpp -o compo
```
Entrée : `pos1(3) quat1(4) pos2(3) quat2(4) point(3)`.

**Cas 1** — p1 = pos(1,2,3)+rot 90°/Z, p2 = pos(5,0,−2)+rot 90°/Y, point (1,1,1) :
```
Applique p1 puis p2 : 9.0000 3.0000 -2.0000
Compose puis applique: 9.0000 3.0000 -2.0000
Ecart                : 0.0000 0.0000 0.0000  (norme 8.88e-16)
```

**Cas 2** — quaternions quelconques normalisés :
```
Applique p1 puis p2 : -0.3832 3.4616 2.7161
Compose puis applique: -0.3832 3.4616 2.7161
Ecart                : 0.0000 0.0000 0.0000  (norme 1.40e-15)
```

Dans les deux cas l'écart est de l'ordre de **10⁻¹⁵** : les deux chemins coïncident aux
arrondis près.

## Conclusion
Composer deux poses revient à multiplier leurs quaternions (`q2 * q1`) et à combiner
leurs translations (`R2*t1 + t2`). Appliquer la pose composée à un point donne exactement
le même résultat que d'appliquer les deux poses l'une après l'autre — ce qui permet, en
pratique, de précalculer une seule pose au lieu d'enchaîner les transformations.

> L'ordre compte : `composer(p1, p2)` signifie « p1 d'abord, puis p2 ». Inverser les
> arguments donnerait la composition dans l'autre sens.
