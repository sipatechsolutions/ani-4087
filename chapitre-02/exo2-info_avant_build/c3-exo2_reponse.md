# Chapitre 3 — Exercice 2 : `jenga info` avant le build

## Énoncé
Lancer `jenga info` sur son projet et lire sa sortie en entier. La rendre, et dire ce
qu'elle apprend que le fichier de projet ne disait pas explicitement.

## Sortie de `jenga info`
Commande lancée :
```
jenga info
```

Sortie réelle sur ma machine :
```
(coller ici la sortie complète et réelle de « jenga info »)
```

## Ce que `jenga info` m'apprend et que le fichier de projet ne disait pas
Le fichier `Salle.jenga` déclare des **intentions** ; `jenga info` montre ce que Jenga en a
**réellement déduit**. À repérer dans la sortie ci-dessus :

1. **L'hôte choisi par défaut** (l'OS/arch réellement construit parmi les cibles listées) —
   non précisé dans le fichier.
2. **La toolchain détectée et sa version** (le compilateur trouvé sur la machine) — jamais
   écrite dans le projet.
3. **Le glob développé** : `src/**/*.cpp` devient la **liste réelle** des fichiers trouvés —
   on voit ce qui est vraiment pris, pas juste le motif.
4. **Les defines ajoutés automatiquement** : selon la config (Debug/Release) et la
   plateforme — on ne les avait pas écrits.
5. **Les flags effectifs par configuration** : la traduction concrète de « Debug/Release »
   (optimisation, symboles de debug) que le fichier nommait sans les détailler.
6. **Les chemins de sortie et d'objets** : des conventions par défaut, non déclarées.
7. **Les dépendances transitives résolues** : l'endroit où l'on verrait les fondations
   « arriver sans qu'on les nomme » sur un vrai projet.

## Conclusion
`jenga info` sert à **voir ce que Jenga a compris** : il rend explicite tout l'implicite
(hôte, toolchain, defines et flags par config, globs développés, chemins, dépendances
résolues). C'est l'étape de vérification à faire **avant** un build ou un déploiement.
