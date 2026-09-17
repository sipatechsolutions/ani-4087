# Chapitre 1 — Démo 4 : Le retard réglable

## Énoncé
Faire essayer le programme à retard réglable à trois personnes de la classe, devant tout le
monde, en montant le retard par paliers. Noter au tableau le seuil de chacune. Conclure
sur ce que cela implique pour le budget d'une image.

## Matériel
Le programme de l'**exercice 12** (`le_retard_reglable.cpp`) : un curseur qui suit la
souris avec un retard réglable de 0 à 200 ms (touches + / −).

## Déroulé de la démo
1. **Trois volontaires**, un à la fois, devant la classe, bougent la souris en cercles.
2. **Monter le retard par paliers de 10 ms**, sans annoncer la valeur à la personne.
3. **Noter au tableau** le retard à partir duquel chacune dit « là, ça traîne ».
4. Comparer les trois seuils à la vue de tous.

## Exemple de relevé au tableau

| Volontaire | Seuil ressenti |
|------------|----------------|
| Volontaire 1 | 70 ms |
| Volontaire 2 | 100 ms |
| Volontaire 3 | 50 ms |

(Seuils sur écran typiquement ~50 à 100 ms ; à relever réellement le jour de la démo.)

## Ce qu'il faut conclure sur le budget d'une image
- Sur écran, il faut **plusieurs dizaines de ms** de retard avant que qui que ce soit ne
  « sente » quelque chose. En casque, le seuil tombe à **~20 ms**.
- Pourquoi si bas ? Parce qu'en casque le retard ne trompe pas seulement l'œil : il
  **contredit l'oreille interne**, qui a déjà mesuré le mouvement de la tête et attend une
  confirmation immédiate. D'où un budget « mouvement → photon » très serré.
- Conséquence directe : le budget d'**une image** doit être tenu à **chaque** fois, sans
  dépassement, parce que le moindre retard perceptible en casque est bien plus faible que
  ce que la classe tolère sur écran.

## Réaction attendue
Les élèves constatent qu'ils tolèrent facilement 50–100 ms sur écran, puis réalisent que
le casque en exige moins de 20 : le « déclic » est de comprendre pourquoi le budget est si
dur à tenir. C'est la version « devant la classe » de l'exercice 12.
