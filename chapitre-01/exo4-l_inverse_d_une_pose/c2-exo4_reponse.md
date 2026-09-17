# Chapitre 2 — Exercice 4 : L'inverse d'une pose

## Énoncé
Écrire `Inverser(pose)` à la main : conjugué du quaternion, et position opposée tournée
par ce conjugué. La vérifier : appliquer la pose à un point, puis l'inverse au résultat, et
afficher l'écart au point de départ. Il doit être nul aux arrondis près.

## L'inverse, écrit à la main
Une pose applique `p' = R*p + t`. Son inverse doit défaire cela :
`p = R⁻¹*(p' - t) = R⁻¹*p' + R⁻¹*(-t)`.

Pour un quaternion **unitaire**, `R⁻¹` correspond au **conjugué** `q* = (-x, -y, -z, w)`.
Donc :
```cpp
Pose inverser(const Pose& p){
    Quat conj = { -p.orientation.x, -p.orientation.y, -p.orientation.z, p.orientation.w };
    Vec3 inv_pos = rotate(conj, { -p.position.x, -p.position.y, -p.position.z });
    return { inv_pos, conj };
}
```
- **orientation inverse** = conjugué du quaternion ;
- **position inverse** = ce conjugué appliqué à la position **opposée**.

## Vérification (aller-retour)
On applique la pose à un point, puis l'inverse au résultat, et on mesure l'écart au
point de départ.

```
g++ -std=c++17 -O2 l_inverse_d_une_pose.cpp -o inverse
echo "5 -2 3  0 0.7071067811865476 0 0.7071067811865476  1 2 3" | ./inverse
```

**Cas 1** — rotation 90°/Y, translation (5,−2,3), point (1,2,3) :
```
Point de depart : 1.0000 2.0000 3.0000
Apres pose      : 8.0000 0.0000 2.0000
Apres inverse   : 1.0000 2.0000 3.0000
Ecart           : 0.0000 0.0000 0.0000  (norme 1.83e-15)
```

**Cas 2** — quaternion quelconque normalisé (0.1,0.2,0.3,0.9273618), mêmes translation et
point :
```
Point de depart : 1.0000 2.0000 3.0000
Apres pose      : 6.0000 0.0000 6.0000
Apres inverse   : 1.0000 2.0000 3.0000
Ecart           : 0.0000 0.0000 0.0000  (norme 1.79e-15)
```

Dans les deux cas, l'écart est de l'ordre de **10⁻¹⁵** : nul aux arrondis près (c'est la
précision d'un `double`).

## Conclusion
L'inverse d'une pose se calcule à la main sans inversion générale de matrice : conjugué du
quaternion pour la rotation, et position opposée tournée par ce conjugué pour la
translation. La vérification aller-retour ramène exactement au point de départ, ce qui
confirme la formule.

> L'entree du quaternion est en ordre (x, y, z, w) ; le quaternion est suppose normalise,
> ce qui rend le conjugue egal a l'inverse.
