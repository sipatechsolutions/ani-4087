# Chapitre 1 — Exercice 6 : La pire image

## Énoncé
Écrire un programme qui dessine en boucle (ici : qui « efface l'écran »). Sur mille
images, mesurer non pas la cadence moyenne mais la durée de la **plus longue image**, et
le **nombre d'images qui dépassent 11 ms**. Rendre les deux chiffres et dire si le
programme tiendrait dans un casque.

## Le programme
Le fichier `la_pire_image.cpp` simule un « effacement d'écran » : à chaque image, il
remplit un framebuffer 1920×1080 (~8,3 Mo) d'une couleur unie. Il chronomètre chaque
image avec `std::chrono::steady_clock`, garde la durée maximale et compte les images
> 11 ms.

```
g++ -std=c++17 -O2 la_pire_image.cpp -o pire_image
./pire_image
```

## Environnement de mesure
- CPU : Intel Xeon @ 2.10 GHz (4 cœurs), Linux.
- Compilateur : g++ `-std=c++17 -O2`.
- Mesure : durée de calcul par image (pas de v-sync, pas de GPU — c'est un programme qui
  ne fait qu'effacer l'écran, comme autorisé par l'énoncé).

## Résultats (2 exécutions)

| Mesure | Exécution 1 | Exécution 2 |
|--------|-------------|-------------|
| Durée moyenne | 0,452 ms | 0,377 ms |
| **Pire image** | **1,622 ms** | **1,226 ms** |
| **Images > 11 ms** | **0 / 1000** | **0 / 1000** |

### Les deux chiffres à rendre
- **Pire image : ≈ 1,6 ms** (maximum observé).
- **Images > 11 ms : 0 sur 1000.**

## Est-ce que ça tiendrait dans un casque ?
**Oui.** Le critère du chapitre est que *chaque* image tienne dans le budget (~11 ms à
90 Hz), pas seulement la moyenne. Ici la pire image (~1,6 ms) reste très en dessous de
11 ms, et **aucune** des 1000 images ne dépasse le seuil : le programme respecte donc
l'échéance à chaque rendez-vous.

## Nuances honnêtes
- Ce résultat est attendu : un programme qui **ne fait qu'effacer l'écran** est très
  léger. Il laisse presque tout le budget libre. Le vrai test viendra quand on ajoutera
  une scène à dessiner **deux fois** (un œil par rendu, cf. exercice 7).
- La mesure ne comprend pas la v-sync ni le coût GPU réel ; sur une vraie boucle de rendu
  avec présentation à l'écran, la pire image serait plus élevée. La méthode, elle, reste
  la même : c'est **le maximum et le nombre de dépassements** qui comptent, pas la moyenne.
- Sur une autre machine, les chiffres exacts différeront : relancer `./pire_image` pour
  obtenir les valeurs de sa propre configuration.

## Conclusion
Sur 1000 images, pire image ≈ 1,6 ms et 0 dépassement de 11 ms : ce programme d'effacement
tiendrait dans un casque. Mais c'est un plancher — il reste à vérifier une fois la scène
réelle rendue deux fois.
