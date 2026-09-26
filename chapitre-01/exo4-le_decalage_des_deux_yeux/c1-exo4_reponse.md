# Chapitre 1 — Exercice 4 : Le décalage des deux yeux

## Énoncé
Tenir un doigt à 30 cm du visage, fermer alternativement un œil puis l'autre, et mesurer
de combien le doigt semble se déplacer par rapport au mur du fond. Recommencer à 1 m, puis
à 3 m. Rendre les trois mesures et dire ce qu'elles annoncent du chapitre 9.

## Note d'honnêteté (à lire)
Je suis actuellement souffrant (alité) et ne peux pas réaliser la manipulation moi-même.
Je ne présente donc **aucun chiffre comme une mesure personnelle**. À la place, je donne la
**prédiction géométrique exacte** (un calcul, donc vérifiable, pas une observation
inventée), et je **referai la vraie manip** dès mon rétablissement pour la confirmer.

## Prédiction géométrique (calcul)
Le décalage angulaire du doigt entre les deux yeux est :

    θ = 2 · arctan( (IPD / 2) / d )

avec IPD = 6,5 cm (moyenne) et d = distance du doigt :

| Distance du doigt | Décalage angulaire (calculé) |
|-------------------|------------------------------|
| 30 cm | ≈ 12,4° |
| 1 m | ≈ 3,7° |
| 3 m | ≈ 1,2° |

Si l'on veut le décalage **linéaire sur un mur** situé à une distance D derrière le doigt :

    S = IPD × (D − d) / d

(cette valeur-là dépend de la distance réelle du mur ; l'angle ci-dessus, lui, n'en dépend
pas — c'est le meilleur repère à confirmer par la mesure).

## Ce que ça annonce du chapitre 9
1. **Le décalage chute très vite avec la distance** : énorme de près (~12°), minuscule de
   loin (~1°). C'est cette *parallaxe* qui donne au cerveau la sensation de **profondeur**.
2. **Il faut donc dessiner la scène deux fois**, depuis deux points de vue séparés de
   l'IPD : une seule image ne contient aucune profondeur.
3. **Le chapitre 9** construira les deux matrices de vue et de projection (une par œil),
   décalées de l'IPD, pour recréer exactement ce décalage — grand pour le proche, quasi nul
   pour le lointain.

## Conclusion
Plus un objet est proche, plus les deux yeux le voient à des endroits différents.
Reproduire cette différence est le travail du rendu stéréo du chapitre 9 ; s'en passer,
c'est perdre la profondeur (cf. QCM 7). La prédiction géométrique ci-dessus sera confirmée
par la mesure réelle au rétablissement.
