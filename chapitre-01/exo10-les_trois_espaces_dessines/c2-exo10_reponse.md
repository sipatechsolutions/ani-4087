# Chapitre 2 — Exercice 10 : Les trois espaces dessines

## Énoncé
Sans écrire de code, dessiner sur une même feuille une pièce vue de côté, avec un
utilisateur debout, et placer les origines des trois espaces. Puis placer une table à
quatre-vingts centimètres dans chacun des trois, et montrer où elle se retrouve.

## Le dessin
Voir le fichier **`dessin.svg`** (rendu directement par GitHub). Schéma de côté, échelle
100 px = 1 m.

```
 2,4 m |==[VIEW]==      ==[table LOCAL]==      <- 0,8 m AU-DESSUS des yeux
       |    :  (suit la tete)                    => flotte a 2,4 m
 1,6 m |  (O)  <- O VIEW (oeil) / O LOCAL (yeux au recentrage)
       |  /|
       |   |                 ____________
 0,8 m |- - - - - - - - - - -|  table    |- - -   <- 0,8 m REEL (vraie table)
       |  / \               |  STAGE OK |
 0 m   |_[O]________________|___________|______   <- O STAGE (au sol)
         sol (plancher)
```

## Les trois origines
| Espace | Origine | y = 0 est… |
|--------|---------|------------|
| **STAGE** | au **sol**, au centre de la zone de jeu | le **plancher** |
| **LOCAL** | à hauteur des **yeux au moment du recentrage** (~1,6 m) | la hauteur des yeux de départ |
| **VIEW** | à l'**œil**, et **suit la tête** | l'œil (mobile) |

## Une table à 0,80 m dans chacun — où se retrouve-t-elle ?
- **STAGE** : `y = 0,8` → **0,8 m au-dessus du sol** → hauteur d'une **vraie table**. ✅
- **LOCAL** : `y = 0,8` → 0,8 m au-dessus de l'origine « yeux » (~1,6 m) → **2,4 m**, la table
  **flotte près du plafond**. ❌
- **VIEW** : `y = 0,8` → 0,8 m au-dessus de l'œil **et accrochée à la tête** → elle flotte
  devant/au-dessus du visage et **bouge dès qu'on tourne la tête**. ❌

## Conclusion
Le même nombre « 0,80 m » désigne **trois endroits différents** selon l'espace choisi. Seul
**STAGE** place la table à la bonne hauteur réelle (0,8 m du sol), parce que c'est le seul
espace où `y = 0` désigne le plancher. C'est pourquoi une table (ou tout objet du décor
posé au sol) se décrit dans **STAGE**, pas dans LOCAL ni VIEW.
