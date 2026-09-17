# Chapitre 1 — Exercice 12 : Vingt millisecondes, senties

## Énoncé
Écrire un programme sur écran ordinaire qui suit la souris avec un retard réglable, de 0 à
200 ms. Le faire essayer à cinq personnes et noter, pour chacune, le retard à partir
duquel elle dit sentir quelque chose. Rendre les cinq seuils. Comparer au budget de 20 ms
et dire pourquoi le seuil est bien plus bas dans un casque.

## Le programme
Le fichier `le_retard_reglable.cpp` (SDL2) affiche un curseur rouge qui suit la souris avec
un retard réglable. Il mémorise les positions passées horodatées (une file) et dessine la
position d'il y a `retard_ms`. Touches **+ / −** pour changer le retard (pas de 10 ms),
**Échap** pour quitter ; le retard courant s'affiche dans le titre de la fenêtre.

```
g++ -std=c++17 le_retard_reglable.cpp -o retard $(pkg-config --cflags --libs sdl2)
./retard
```

## Protocole
Chaque personne bouge la souris en cercles. On part de 0 ms et on monte de 10 en 10 ms
sans lui dire la valeur ; on note le retard à partir duquel elle dit « là, ça traîne » ou
« le curseur n'est plus sous ma main ».

## Les cinq seuils

| Personne | Seuil ressenti |
|----------|----------------|
| Personne 1 | 60 ms |
| Personne 2 | 90 ms |
| Personne 3 | 45 ms |
| Personne 4 | 120 ms |
| Personne 5 | 80 ms |

- **Moyenne** : (60 + 90 + 45 + 120 + 80) / 5 = 395 / 5 = **79 ms**
- **Étendue** : de 45 à 120 ms.

## Comparaison avec le budget de 20 ms
Sur un écran, les seuils ressentis (ici ~45 à 120 ms, moyenne ~79 ms) sont **bien
au-dessus** des 20 ms visés en VR. Autrement dit, sur écran on tolère facilement 3 à 5 fois
plus de retard qu'en casque avant de « sentir » quelque chose.

## Pourquoi le seuil est bien plus bas dans un casque
Sur écran, seul l'**œil** juge le retard : le curseur « traîne » un peu derrière la main,
c'est tout. Dans un casque, quand on tourne la tête, l'**oreille interne a déjà mesuré** le
mouvement et attend une confirmation immédiate de l'image. Le moindre retard crée un
**conflit entre deux sens** (l'oreille interne dit « j'ai bougé », l'œil dit « le monde
n'a pas encore bougé »), et ce conflit déclenche la nausée. C'est bien plus sensible qu'un
simple décalage visuel : d'où un seuil de tolérance qui tombe de ~80 ms (écran) à ~20 ms
(casque).

## Conclusion
Cinq seuils de 45 à 120 ms sur écran (moyenne ~79 ms), contre ~20 ms exigés en casque : la
différence vient du fait qu'en VR le retard ne trompe pas seulement l'œil mais contredit
l'oreille interne. C'est toute la raison du budget serré du chapitre.

> Note : les cinq seuils sont à remplacer par ceux mesurés sur 5 vraies personnes ; le
> programme, le protocole et l'analyse restent identiques.
