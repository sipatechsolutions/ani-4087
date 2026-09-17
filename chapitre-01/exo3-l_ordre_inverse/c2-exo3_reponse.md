# Chapitre 2 — Exercice 3 : L'ordre inverse

## Énoncé
Reprendre l'exercice précédent et écrire une seconde fonction qui applique la translation
d'abord et la rotation ensuite. Afficher les deux résultats pour le même point. Puis
trouver une pose et un point pour lesquels les deux coïncident, et dire pourquoi.

## Les deux ordres
```cpp
// RT : rotation PUIS translation (l'ordre correct d'une pose)
applique_RT(p, point) = rotate(q, point) + t          // = R*p + t

// TR : translation PUIS rotation (l'ordre inverse)
applique_TR(p, point) = rotate(q, point + t)          // = R*(p + t) = R*p + R*t
```

## Affichage des deux résultats (cas général)
Pose : translation `(5, 0, 0)`, rotation 90° autour de Y ; point `(1, 0, 0)`.
```
Rotation puis translation : 5.0000 0.0000 -1.0000
Translation puis rotation : -0.0000 0.0000 -6.0000
```
Les deux **diffèrent** : l'ordre compte.

## Une pose et un point où les deux coïncident
Pose : translation `(0, 5, 0)` (**le long de l'axe Y**), rotation 90° autour de Y ;
point `(1, 0, 0)`.
```
Rotation puis translation : 0.0000 5.0000 -1.0000
Translation puis rotation : 0.0000 5.0000 -1.0000
```
Les deux donnent le même résultat.

## Pourquoi
La différence entre les deux ordres est :
```
RT - TR = (R*p + t) - (R*p + R*t) = t - R*t
```
Les deux coïncident donc **si et seulement si `R*t = t`**, c'est-à-dire quand la
translation `t` est **inchangée par la rotation**. Cela arrive dans trois cas :
1. `t` est **alignée sur l'axe de rotation** (ici la translation `(0,5,0)` est sur l'axe Y,
   et une rotation autour de Y laisse l'axe Y fixe) — c'est l'exemple ci-dessus ;
2. la translation est nulle (`t = 0`) ;
3. la rotation est l'identité (`R = I`).

Dans tous les autres cas, tourner puis déplacer n'est pas la même chose que déplacer puis
tourner, parce que la rotation agit aussi sur le vecteur de translation.

## Conclusion
Une pose s'applique **rotation d'abord, translation ensuite**. L'ordre inverse ne donne le
même point que dans le cas particulier où la translation est invariante par la rotation
(alignée sur l'axe, ou translation/rotation nulle).
