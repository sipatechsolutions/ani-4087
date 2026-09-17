# Chapitre 1 — Exercice 8 : Le champ de vision asymétrique

## Énoncé
Chercher les quatre angles du champ de vision d'un casque du commerce, pour l'œil gauche.
Les rendre avec la source. Puis dire, en une phrase, ce qui se passerait si l'on employait
à la place un champ symétrique de même surface.

## Les quatre angles (œil gauche, HTC Vive)

| Direction | Angle |
|-----------|-------|
| Vers la gauche (extérieur / temporal) | **−54,41°** |
| Vers la droite (intérieur / nasal) | **+51,35°** |
| Vers le bas | **−55,91°** |
| Vers le haut | **+55,67°** |

On voit l'**asymétrie horizontale** : l'œil gauche voit plus loin vers l'**extérieur**
(54,41°) que vers l'**intérieur** (51,35°), exactement parce que la lentille n'est pas
centrée sur l'œil. La matrice de projection doit donc être construite avec ces **quatre
angles séparés**, et non avec la fonction habituelle « angle + rapport de forme ».

## Source
- **HMD Geometry Database** (données de géométrie relevées sur des casques du commerce),
  K. Vlachos (risa2000) : <https://risa2000.github.io/hmdgdb/>
- Méthode de calcul du FOV rendu : <https://risa2000.github.io/vrdocs/docs/hmd_fov_calculation.html>

Les angles ci-dessus sont ceux du HTC Vive relevés dans cette base (œil gauche). Chaque
casque a ses propres valeurs ; en pratique, on les obtient aussi à l'exécution via
l'API OpenXR (structure `XrFovf` : `angleLeft`, `angleRight`, `angleUp`, `angleDown`).

## Si l'on employait un champ symétrique de même surface
L'image serait bien dessinée mais **mal orientée** : le centre optique tomberait au
mauvais endroit, les deux yeux ne se recouvriraient plus correctement, et la stéréo
serait faussée aux bords — donnant une gêne et une fatigue visuelles sans aucune erreur
signalée par le programme.

## Conclusion
Le champ d'un œil dans un casque est intrinsèquement asymétrique (lentille décentrée).
Il faut fournir les quatre angles indépendamment ; c'est ce que le chapitre 9 exploitera
pour construire la matrice de projection de chaque œil.
