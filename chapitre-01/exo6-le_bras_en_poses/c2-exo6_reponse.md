# Chapitre 2 — Exercice 6 : Le bras en poses

## Énoncé
Construire un bras articulé à trois segments : une épaule à l'origine, un coude à un bras
de distance, une main à un avant-bras du coude. Chaque articulation porte sa pose dans le
repère de la précédente ; la pose d'une articulation dans le monde s'obtient en composant
celle de son parent avec la sienne. Afficher la position du coude et de la main dans le
monde. Faire tourner l'épaule et vérifier que la main suit.

## Construction
Chaque articulation a une **pose locale** (dans le repère de son parent) :
- épaule : à l'origine (c'est la racine), orientation réglable ;
- coude : translation `(bras, 0, 0)` dans le repère de l'épaule (`bras = 0,30 m`) ;
- main : translation `(avant_bras, 0, 0)` dans le repère du coude (`avant_bras = 0,25 m`).

La **pose monde** d'une articulation = composition de la pose monde de son parent avec sa
pose locale :
```cpp
coude_monde = composer(coude_local, epaule);   // parent = epaule
main_monde  = composer(main_local,  coude);    // parent = coude
```
où `composer(a, b)` = « appliquer a puis b » (le parent `b` s'applique à l'extérieur).
Ainsi la rotation de l'épaule se propage au coude, et celle du coude à la main.

## Résultats — on fait tourner l'épaule autour de Z
```
g++ -std=c++17 -O2 le_bras_en_poses.cpp -o bras
./bras
```
```
Epaule tournee de   0.0 deg autour de Z :
   coude (monde) : 0.3000 0.0000 0.0000
   main  (monde) : 0.5500 0.0000 0.0000  (|main| = 0.5500)
Epaule tournee de  45.0 deg autour de Z :
   coude (monde) : 0.2121 0.2121 0.0000
   main  (monde) : 0.3889 0.3889 0.0000  (|main| = 0.5500)
Epaule tournee de  90.0 deg autour de Z :
   coude (monde) : 0.0000 0.3000 0.0000
   main  (monde) : 0.0000 0.5500 0.0000  (|main| = 0.5500)
```

## Vérification : la main suit
- À 0°, la main est en `(0.55, 0, 0)` ; à 90° elle est en `(0, 0.55, 0)` : elle a tourné
  avec l'épaule, sans qu'on ait touché à sa pose locale.
- La distance `|main|` à l'origine reste **0,55 m** (= bras + avant-bras) pour tous les
  angles : le bras est rigide, seule l'orientation de l'épaule le fait pivoter.
- Le coude suit aussi (`0.30 m` de l'origine à tout angle).

C'est la preuve que la chaîne de composition fonctionne : bouger le parent (l'épaule)
entraîne tous ses enfants (coude, puis main).

## Conclusion
Un bras articulé se modélise comme une **chaîne de poses locales** ; la pose monde de
chaque articulation est la composition de celle de son parent avec la sienne. Faire
tourner l'épaule propage automatiquement le mouvement jusqu'à la main — c'est le principe
de toute hiérarchie de squelette (et, plus tard, de la main tenue en VR).
