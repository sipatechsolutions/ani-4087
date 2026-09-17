# Chapitre 1 — Exercice 7 : Le coût du doublement

## Énoncé
Reprendre le même programme et mesurer le temps que prend son **rendu seul**, sans la
logique. Puis estimer ce que coûterait ce rendu **fait deux fois**, et ce qu'il resterait
pour le reste. Rendre la mesure, l'estimation et la conclusion sur ce qu'il faudrait
réduire.

## Méthode
Le programme `le_cout_du_doublement.cpp` reprend l'effacement d'écran de l'exercice 6 et
sépare deux phases chronométrées séparément :
- **Logique** : mise à jour de 200 000 objets — faite **une seule fois** par image (elle
  ne se double pas en VR).
- **Rendu** : remplissage du framebuffer 1920×1080 — c'est **lui** qu'il faut faire
  **deux fois** en VR (un rendu par œil).

On mesure le rendu seul, puis on estime `rendu × 2`, et on le compare au budget d'une
image à 90 Hz.

```
g++ -std=c++17 -O2 le_cout_du_doublement.cpp -o cout
./cout
```

## Environnement de mesure
- CPU : Intel Xeon @ 2.10 GHz (4 cœurs), Linux. Compilateur g++ `-std=c++17 -O2`.
- Mesure du temps de calcul CPU (pas de v-sync ni de GPU réel).

## Résultats (moyenne sur 1000 images, 2 exécutions)

| Mesure | Exécution 1 | Exécution 2 |
|--------|-------------|-------------|
| **Rendu seul (1×)** | **0,401 ms** | **0,411 ms** |
| Logique (1×) | 0,061 ms | 0,066 ms |
| **Rendu double (2×)** — estimation | **0,802 ms** | **0,822 ms** |
| Rendu 2× + logique | 0,864 ms | 0,888 ms |

## Le budget et ce qu'il reste
- Budget d'une image à 90 Hz : **11,1 ms**.
- Moins les ~8 ms du matériel (capteurs + transmission + composition + affichage) :
  il reste **~3,1 ms** pour tout le code.
- Coût estimé en VR (rendu 2× + logique 1×) : **~0,87 ms**.
- **Reste après le rendu doublé : ~2,2 ms** de marge dans le budget code.

## Conclusion : que faudrait-il réduire ?
- Ici, doubler le rendu coûte **~0,4 ms de plus** (0,4 → 0,8 ms) : c'est indolore, parce
  que le « rendu » n'est qu'un effacement d'écran très léger. La logique, elle, est
  négligeable (~0,06 ms) et **ne se double pas** : ce n'est pas elle le problème.
- Le point clé : **c'est le rendu qui double**, donc c'est lui le poste sous pression. Sur
  une vraie scène (géométrie, textures, éclairage), le rendu prendrait plusieurs
  millisecondes ; le doubler ferait vite exploser les ~3,1 ms disponibles.
- Ce qu'il faudrait alors réduire, **côté rendu** en priorité :
  1. la **résolution des cibles de rendu** (le coût de remplissage est proportionnel au
     nombre de pixels) ;
  2. le **nombre de polygones / la complexité des shaders** dessinés par œil ;
  3. **partager entre les deux yeux** ce qui peut l'être (culling, ombres, calculs de
     visibilité) au lieu de tout refaire deux fois.
- La logique et la physique, elles, restent à **un seul exemplaire** : inutile d'y toucher
  pour tenir le budget VR. C'est la « colonne de droite » (ce qu'on ne double pas) qui est
  notre marge, comme l'annonce le chapitre 16.

## Résumé
- Mesure : rendu seul ≈ **0,4 ms**.
- Estimation : rendu ×2 ≈ **0,8 ms**, laissant **~2,2 ms** de marge sur les ~3,1 ms du code.
- À réduire en priorité : **le coût du rendu par œil** (résolution, polygones, calculs
  partagés), car c'est la seule partie qui double.
