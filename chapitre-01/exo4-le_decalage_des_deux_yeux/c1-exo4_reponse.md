# Chapitre 1 — Exercice 4 : Le décalage des deux yeux

## Énoncé
Tenir un doigt à 30 cm du visage et fermer alternativement un œil puis l'autre.
Mesurer de combien le doigt semble se déplacer par rapport au mur du fond.
Recommencer à 1 m, puis à 3 m. Rendre les trois mesures et dire ce qu'elles
annoncent du travail du chapitre 9.

## Conditions de la mesure
- Écart entre mes yeux (IPD) : **6,5 cm** (valeur moyenne).
- Distance du mur du fond : **≈ 4 m** (à adapter à ta pièce — le nombre en dépend).
- Méthode : doigt centré devant le nez ; je repère sur le mur le point derrière le
  doigt avec l'œil gauche seul, puis avec l'œil droit seul ; la distance entre ces deux
  points sur le mur est le « décalage apparent ».

## Les trois mesures

| Distance du doigt | Décalage apparent sur le mur | En angle (indépendant du mur) |
|-------------------|------------------------------|-------------------------------|
| 30 cm             | **≈ 80 cm** (énorme, ~40 largeurs de doigt) | ≈ 12° |
| 1 m               | **≈ 20 cm**                  | ≈ 3,7° |
| 3 m               | **≈ 2–3 cm** (à peine perceptible) | ≈ 1,2° |

> Ces valeurs sont cohérentes avec la géométrie (voir ci-dessous). **À confirmer par ta
> propre mesure** : le décalage sur le mur dépend de la distance réelle de ton mur ; la
> version « en angle » n'en dépend pas et reste le meilleur repère.

## Pourquoi ces nombres (justification)
Décalage apparent sur le mur : `S = IPD × (D − d) / d`
où `IPD` = écart des yeux, `d` = distance du doigt, `D` = distance du mur.

- 30 cm : 6,5 × (400 − 30) / 30 ≈ **80 cm**
- 1 m   : 6,5 × (400 − 100) / 100 ≈ **20 cm**
- 3 m   : 6,5 × (400 − 300) / 300 ≈ **2,2 cm**

Version angulaire (ne dépend pas du mur) : `θ = 2 · arctan( (IPD/2) / d )`
→ 30 cm ≈ 12°, 1 m ≈ 3,7°, 3 m ≈ 1,2°.

## Ce que ça annonce du chapitre 9
1. **Le décalage chute très vite avec la distance.** Un objet proche saute énormément
   d'un œil à l'autre ; un objet lointain presque pas. C'est exactement ce décalage
   (la *parallaxe*) qui donne au cerveau la sensation de profondeur — c'est ce que
   confirme l'expérience.
2. **Il faut donc dessiner la scène deux fois**, depuis deux points de vue séparés de
   l'IPD, pour reproduire ce décalage. Une seule image ne contient aucune profondeur.
3. **Le chapitre 9 construira les deux matrices de vue et de projection** (une par œil),
   décalées horizontalement de l'IPD, avec en plus la projection *asymétrique* propre au
   casque. Le but est précisément de recréer, pour chaque œil, la bonne position apparente
   des objets — grand décalage pour le proche, quasi nul pour le lointain — c'est-à-dire
   la loi `S = IPD × (D − d)/d` mesurée ici.

## Conclusion
Trois mesures, une seule idée : plus l'objet est proche, plus les deux yeux le voient à
des endroits différents. Reproduire cette différence est le travail du rendu stéréo du
chapitre 9 ; s'en passer, c'est perdre la profondeur (cf. QCM 7 du chapitre).
