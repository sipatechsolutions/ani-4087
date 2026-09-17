# Chapitre 1 — Exercice 1 : Les trois cadences

## Énoncé
Calculer la durée d'une image à 72, 90 et 120 hertz, au dixième de milliseconde.
Pour chacune, soustraire les 8 ms que prennent les capteurs, la transmission, la
composition et l'affichage, et dire ce qu'il reste au code.

## Méthode
- Durée d'une image = `1000 ÷ fréquence` (en ms).
- Budget du code = durée de l'image − 8 ms (temps du matériel).

## Résultats

| Fréquence | Durée d'une image | − 8 ms → reste au code |
|-----------|-------------------|------------------------|
| 72 Hz     | 13,9 ms           | **5,9 ms**             |
| 90 Hz     | 11,1 ms           | **3,1 ms**             |
| 120 Hz    | 8,3 ms            | **0,3 ms**             |

### Les trois nombres à rendre
**5,9 ms · 3,1 ms · 0,3 ms**

## Conclusion
Plus la cadence monte, plus la marge laissée au code s'effondre. À 120 Hz il ne
reste qu'environ 0,3 ms : autrement dit, à cette fréquence, presque tout le budget
« mouvement → photon » est déjà consommé par le matériel, et le code doit être
extrêmement économe. Ces trois nombres seront réutilisés au chapitre 10.

## Programme
Le fichier `les_trois_cadences.cpp` calcule et affiche ce tableau.

```
g++ -std=c++17 -O2 les_trois_cadences.cpp -o cadences
./cadences
```

Sortie :

```
Frequence | Image (ms) | Reste au code (ms)
----------+------------+-------------------
     72 Hz |       13.9 |                5.9
     90 Hz |       11.1 |                3.1
    120 Hz |        8.3 |                0.3
```
