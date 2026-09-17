# Chapitre 2 — Exercice 7 : La matrice de vue (deux inverses)

## Énoncé
Écrire les deux versions : celle qui inverse la matrice de la pose par une inversion
générale, et celle qui construit directement le conjugué et la translation opposée.
Comparer les seize coefficients. Puis passer une pose dégénérée à la première et regarder
ce qu'elle rend.

## Les deux versions
- **Version A — inversion générale** : on construit la matrice 4×4 de la pose (rotation du
  quaternion + translation), puis on l'inverse par **Gauss-Jordan** (algorithme général,
  qui ne sait rien du fait que c'est une pose). Si la matrice est singulière, cette
  version **rend l'identité en silence** au lieu d'échouer.
- **Version B — analytique** : on sait qu'une pose est une rotation + une translation.
  L'inverse est donc `Rᵀ` (rotation transposée = conjugué du quaternion) et `-Rᵀ t`
  (translation opposée, tournée). Aucune inversion générale.

## Comparaison des 16 coefficients (pose valide)
Pose : translation (5, −2, 3), quaternion normalisé (0.1, 0.2, 0.3, 0.9273618).
```
Version A (inversion generale) :
   0.7400  0.5964 -0.3109 -1.5743
  -0.5164  0.8000  0.3055  3.2657
   0.4309 -0.0655  0.9000 -4.9857
   0.0000  0.0000  0.0000  1.0000
Version B (conjugue + translation opposee) :
   0.7400  0.5964 -0.3109 -1.5743
  -0.5164  0.8000  0.3055  3.2657
   0.4309 -0.0655  0.9000 -4.9857
   0.0000  0.0000  0.0000  1.0000
Ecart max sur les 16 coefficients : 7.99e-15
```
Les deux matrices sont **identiques** aux arrondis près (écart max ~10⁻¹⁵).

## La pose dégénérée passée à la version A
Pose dégénérée : quaternion **nul** `(0,0,0,0)`. Le bloc rotation devient nul, donc la
matrice 4×4 est **singulière** (non inversible) :
```
Matrice de la pose degeneree (singuliere) :
   0.0000  0.0000  0.0000  5.0000
   0.0000  0.0000  0.0000 -2.0000
   0.0000  0.0000  0.0000  3.0000
   0.0000  0.0000  0.0000  1.0000
Version A appliquee a la pose degeneree -> rend :
   1.0000  0.0000  0.0000  0.0000
   0.0000  1.0000  0.0000  0.0000
   0.0000  0.0000  1.0000  0.0000
   0.0000  0.0000  0.0000  1.0000
```
L'inversion générale **rend silencieusement l'identité** : aucune erreur, aucun message,
une matrice fausse. En VR, on aurait une matrice de vue entièrement fausse « qui ne
plante pas » — exactement le genre de faute qui se **sent** au lieu de se voir.

## Conclusion
Sur une pose valide, les deux méthodes donnent la même matrice. Mais l'inversion générale
cache un piège : sur une entrée dégénérée, elle retourne l'identité sans rien signaler.
C'est pourquoi le module écrit l'inverse **à la main** (conjugué + translation opposée) :
cette forme est non seulement plus rapide, mais elle ne peut pas se tromper en silence —
elle reflète exactement ce qu'est une pose.
