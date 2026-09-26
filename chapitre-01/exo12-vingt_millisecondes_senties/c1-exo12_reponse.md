# Chapitre 1 — Exercice 12 : Vingt millisecondes, senties

## Énoncé
Écrire un programme sur écran ordinaire qui suit la souris avec un retard réglable (0 à
200 ms). Le faire essayer à cinq personnes et noter, pour chacune, le retard à partir
duquel elle sent quelque chose. Rendre les cinq seuils. Comparer au budget de 20 ms et dire
pourquoi le seuil est bien plus bas dans un casque.

## Le programme (réel)
`le_retard_reglable.cpp` (SDL2) : un curseur rouge suit la souris avec un retard réglable.
Il mémorise les positions passées horodatées (une file) et dessine la position d'il y a
`retard_ms`. Touches **+ / −** (pas de 10 ms), **Échap** pour quitter ; le retard courant
s'affiche dans le titre.
```
g++ -std=c++17 le_retard_reglable.cpp -o retard $(pkg-config --cflags --libs sdl2)
./retard
```

## Note d'honnêteté (à lire)
Je suis actuellement souffrant (alité) et **je n'ai pas pu faire tester 5 personnes
réelles**. Je ne présente donc **aucun seuil comme un relevé personnel**. À la place, je
donne les seuils **rapportés par la littérature scientifique** (sources citées), et je ferai
le test réel sur 5 personnes dès mon rétablissement pour remplacer cette section.

## Seuils rapportés par la littérature
**Sur écran ordinaire (retard souris / curseur)** — étude *« Are 100 ms Fast Enough? »* et
travaux liés :
- Le retard devient perceptible dans une plage de **~20 à 100 ms** ; la performance chute
  quand il dépasse **~25 ms** en glisser-déposer.
- Les utilisateurs les plus sensibles descendent bien plus bas (jusqu'à ~6 ms au toucher).
- Le JND (plus petite différence perceptible) est d'environ **~55 ms** sur pavé tactile en
  glisser.

**En casque (rotation de la tête)** — étude *« Perceptual Tolerance to Motion-to-Photon
Latency »* :
- Seuil de confort : la **règle des 20 ms**.
- JND aussi bas que **~1 à 3 ms** dans les meilleures conditions.

## Comparaison avec le budget de 20 ms
Sur écran, on tolère facilement **des dizaines de ms** (souvent 50–100 ms) avant de
« sentir » le retard. En casque, le seuil de confort tombe à **~20 ms** : 3 à 5 fois plus
strict.

## Pourquoi le seuil est bien plus bas dans un casque
Sur écran, seul l'**œil** juge : le curseur « traîne » un peu, c'est tout. Dans un casque,
quand on tourne la tête, l'**oreille interne a déjà mesuré** le mouvement et attend une
confirmation immédiate. Le moindre retard crée un **conflit sensoriel** (oreille interne :
« j'ai bougé » ; œil : « le monde n'a pas encore bougé »), qui déclenche la nausée. D'où un
seuil bien plus bas qu'un simple décalage visuel.

## Conclusion
Écran : tolérance de l'ordre de dizaines de ms. Casque : ~20 ms. La différence vient de ce
qu'en VR le retard ne trompe pas que l'œil, il contredit l'oreille interne — toute la raison
du budget serré du chapitre. (Seuils personnels sur 5 personnes à ajouter au rétablissement.)

## Sources
- *Are 100 ms Fast Enough? Characterizing Latency Perception Thresholds in Mouse-Based
  Interaction* : <https://link.springer.com/chapter/10.1007/978-3-319-58475-1_4>
- *Perceptual Tolerance to Motion-to-Photon Latency with Head Movement in Virtual Reality* :
  <https://www.researchgate.net/publication/338509497_Perceptual_Tolerance_to_Motion-To-Photon_Latency_with_Head_Movement_in_Virtual_Reality>
