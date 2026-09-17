# Chapitre 1 — Démo 1 : Le budget au tableau

## Énoncé
Dessiner au tableau les vingt millisecondes comme une barre, et faire placer par la classe
les cinq étapes à leur échelle. Faire remarquer ce qui reste pour le code, et faire
réagir.

## Déroulé de la démo
1. **Tracer la barre.** Au tableau, une barre horizontale = **20 ms** (« mouvement →
   photon »). On choisit une échelle simple, par ex. **1 cm = 1 ms** → barre de 20 cm.
   Graduer 0, 5, 10, 15, 20.
2. **Distribuer les cinq étapes.** Donner à la classe les cinq étiquettes (capteurs,
   transmission, code, compositeur, affichage) et leur demander de venir les placer et
   les dimensionner à l'échelle sur la barre.
3. **Corriger ensemble** avec des valeurs représentatives (dans les fourchettes du
   chapitre) qui totalisent 20 ms :

| Étape | Durée (représentative) | Fourchette du chapitre |
|-------|------------------------|------------------------|
| Capteurs mesurent | 1,5 ms | 1–2 ms |
| Transmission | 2 ms | 1–3 ms |
| **Votre code (décide + dessine)** | **12 ms** | 5–11 ms (ici on prend le haut) |
| Compositeur assemble | 1,5 ms | 1–2 ms |
| Affichage de la ligne | 3 ms | 2–5 ms |
| **Total** | **20 ms** | — |

> Le schéma à l'échelle est dans le fichier **`budget.svg`** (rendu par GitHub).

## Ce qu'il faut faire remarquer
- Le **matériel** (capteurs + transmission + compositeur + affichage) prend déjà **~8 ms**
  sur les 20 : ce temps-là, on ne le récupère pas.
- Il reste donc **~une dizaine de ms** (ici 12) pour **tout** le code.
- Et dans cette tranche, il faut **dessiner deux fois** (un rendu par œil), **à chaque
  image**, sans jamais dépasser.

## Faire réagir (questions à poser à la classe)
- « Le code a la plus grosse tranche : c'est confortable, non ? » → amener la classe à
  voir que non : cette tranche doit contenir **deux rendus** et tenir à **chaque** image,
  pas en moyenne.
- « Que se passe-t-il si le code déborde d'1 ms ? » → on rate l'échéance, le compositeur
  réaffiche l'image précédente déformée → saccade ressentie.
- « Et si on passe de 90 à 120 Hz ? » → la barre rétrécit (8,3 ms au lieu de 11,1) alors
  que le matériel ne bouge presque pas → la tranche du code fond (cf. exercice 1).

## Réaction attendue de la classe
La surprise habituelle : on croit que « le rendu, c'est tout le temps disponible », et on
découvre qu'en réalité le code n'a qu'une dizaine de ms, partagée entre deux yeux et due à
chaque image. C'est le « déclic » de la démo : la VR est un problème d'échéance, pas de
graphisme.

## Conclusion
La barre au tableau rend visible, d'un coup d'œil, là où part le temps : ~8 ms de
matériel incompressible, ~12 ms pour le code, à doubler et à tenir à chaque image. C'est
le point de départ de tout le chapitre.
